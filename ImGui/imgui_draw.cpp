// dear imgui, v1.51 WIP
// (drawing and font code)

// Contains implementation for
// - ImDrawList
// - ImDrawData
// - ImFontAtlas
// - ImFont
// - Default font data

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui_internal.h"
#include "../CaviarDreams.h"
#include <stdio.h>      // vsnprintf, sscanf, printf
#if !defined(alloca)
#ifdef _WIN32
#include <malloc.h>     // alloca
#elif (defined(__FreeBSD__) || defined(FreeBSD_kernel) || defined(__DragonFly__)) && !defined(__GLIBC__)
#include <stdlib.h>     // alloca. FreeBSD uses stdlib.h unless GLIBC
#else
#include <alloca.h>     // alloca
#endif
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed (stb stuff)
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wfloat-equal"            // warning : comparing floating point with == or != is unsafe   // storing and comparing against same constants ok.
#pragma clang diagnostic ignored "-Wglobal-constructors"    // warning : declaration requires a global destructor           // similar to above, not sure what the exact difference it.
#pragma clang diagnostic ignored "-Wsign-conversion"        // warning : implicit conversion changes signedness             //
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"      // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"          // warning: 'xxxx' defined but not used
#pragma GCC diagnostic ignored "-Wdouble-promotion"         // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"               // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wcast-qual"                // warning: cast from type 'xxxx' to type 'xxxx' casts away qualifiers
#endif

//-------------------------------------------------------------------------
// STB libraries implementation
//-------------------------------------------------------------------------

//#define IMGUI_STB_NAMESPACE     ImGuiStb
//#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION
//#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION


#ifdef IMGUI_STB_NAMESPACE
namespace IMGUI_STB_NAMESPACE
{
#endif

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4456)                             // declaration of 'xx' hides previous local declaration
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"              // warning: comparison is always true due to limited range of data type [-Wtype-limits]
#endif

#define STBRP_ASSERT(x)    IM_ASSERT(x)
#ifndef IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION
#define STBRP_STATIC
#define STB_RECT_PACK_IMPLEMENTATION
#endif
#include "stb_rect_pack.h"

#define STBTT_malloc(x,u)  ((void)(u), ImGui::MemAlloc(x))
#define STBTT_free(x,u)    ((void)(u), ImGui::MemFree(x))
#define STBTT_assert(x)    IM_ASSERT(x)
#ifndef IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#else
#define STBTT_DEF extern
#endif
#include "stb_truetype.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#ifdef IMGUI_STB_NAMESPACE
} // namespace ImGuiStb
using namespace IMGUI_STB_NAMESPACE;
#endif

//-----------------------------------------------------------------------------
// ImDrawList
//-----------------------------------------------------------------------------

static const ImVec4 GNullClipRect(-8192.0f, -8192.0f, +8192.0f, +8192.0f); // Large values that are easy to encode in a few bits+shift

void ImDrawList::Clear()
{
	CmdBuffer.resize(0);
	IdxBuffer.resize(0);
	VtxBuffer.resize(0);
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.resize(0);
	_TextureIdStack.resize(0);
	_Path.resize(0);
	_ChannelsCurrent = 0;
	_ChannelsCount = 1;
	// NB: Do not clear channels so our allocations are re-used after the first frame.
}

void ImDrawList::ClearFreeMemory()
{
	CmdBuffer.clear();
	IdxBuffer.clear();
	VtxBuffer.clear();
	_VtxCurrentIdx = 0;
	_VtxWritePtr = NULL;
	_IdxWritePtr = NULL;
	_ClipRectStack.clear();
	_TextureIdStack.clear();
	_Path.clear();
	_ChannelsCurrent = 0;
	_ChannelsCount = 1;
	for (int i = 0; i < _Channels.Size; i++)
	{
		if (i == 0) memset(&_Channels[0], 0, sizeof(_Channels[0]));  // channel 0 is a copy of CmdBuffer/IdxBuffer, don't destruct again
		_Channels[i].CmdBuffer.clear();
		_Channels[i].IdxBuffer.clear();
	}
	_Channels.clear();
}

// Use macros because C++ is a terrible language, we want guaranteed inline, no code in header, and no overhead in Debug mode
#define GetCurrentClipRect()    (_ClipRectStack.Size ? _ClipRectStack.Data[_ClipRectStack.Size-1]  : GNullClipRect)
#define GetCurrentTextureId()   (_TextureIdStack.Size ? _TextureIdStack.Data[_TextureIdStack.Size-1] : NULL)

void ImDrawList::AddDrawCmd()
{
	ImDrawCmd draw_cmd;
	draw_cmd.ClipRect = GetCurrentClipRect();
	draw_cmd.TextureId = GetCurrentTextureId();

	IM_ASSERT(draw_cmd.ClipRect.x <= draw_cmd.ClipRect.z && draw_cmd.ClipRect.y <= draw_cmd.ClipRect.w);
	CmdBuffer.push_back(draw_cmd);
}

void ImDrawList::AddCallback(ImDrawCallback callback, void* callback_data)
{
	ImDrawCmd* current_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!current_cmd || current_cmd->ElemCount != 0 || current_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		current_cmd = &CmdBuffer.back();
	}
	current_cmd->UserCallback = callback;
	current_cmd->UserCallbackData = callback_data;

	AddDrawCmd(); // Force a new command after us (see comment below)
}

// Our scheme may appears a bit unusual, basically we want the most-common calls AddLine AddRect etc. to not have to perform any check so we always have a command ready in the stack.
// The cost of figuring out if a new command has to be added or if we can merge is paid in those Update** functions only.
void ImDrawList::UpdateClipRect()
{
	// If current command is used with different settings we need to add a new command
	const ImVec4 curr_clip_rect = GetCurrentClipRect();
	ImDrawCmd* curr_cmd = CmdBuffer.Size > 0 ? &CmdBuffer.Data[CmdBuffer.Size - 1] : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && memcmp(&curr_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) != 0) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (curr_cmd->ElemCount == 0 && prev_cmd && memcmp(&prev_cmd->ClipRect, &curr_clip_rect, sizeof(ImVec4)) == 0 && prev_cmd->TextureId == GetCurrentTextureId() && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->ClipRect = curr_clip_rect;
}

void ImDrawList::UpdateTextureID()
{
	// If current command is used with different settings we need to add a new command
	const ImTextureID curr_texture_id = GetCurrentTextureId();
	ImDrawCmd* curr_cmd = CmdBuffer.Size ? &CmdBuffer.back() : NULL;
	if (!curr_cmd || (curr_cmd->ElemCount != 0 && curr_cmd->TextureId != curr_texture_id) || curr_cmd->UserCallback != NULL)
	{
		AddDrawCmd();
		return;
	}

	// Try to merge with previous command if it matches, else use current command
	ImDrawCmd* prev_cmd = CmdBuffer.Size > 1 ? curr_cmd - 1 : NULL;
	if (prev_cmd && prev_cmd->TextureId == curr_texture_id && memcmp(&prev_cmd->ClipRect, &GetCurrentClipRect(), sizeof(ImVec4)) == 0 && prev_cmd->UserCallback == NULL)
		CmdBuffer.pop_back();
	else
		curr_cmd->TextureId = curr_texture_id;
}

#undef GetCurrentClipRect
#undef GetCurrentTextureId

// Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
void ImDrawList::PushClipRect(ImVec2 cr_min, ImVec2 cr_max, bool intersect_with_current_clip_rect)
{
	ImVec4 cr(cr_min.x, cr_min.y, cr_max.x, cr_max.y);
	if (intersect_with_current_clip_rect && _ClipRectStack.Size)
	{
		ImVec4 current = _ClipRectStack.Data[_ClipRectStack.Size - 1];
		if (cr.x < current.x) cr.x = current.x;
		if (cr.y < current.y) cr.y = current.y;
		if (cr.z > current.z) cr.z = current.z;
		if (cr.w > current.w) cr.w = current.w;
	}
	cr.z = ImMax(cr.x, cr.z);
	cr.w = ImMax(cr.y, cr.w);

	_ClipRectStack.push_back(cr);
	UpdateClipRect();
}

void ImDrawList::PushClipRectFullScreen()
{
	PushClipRect(ImVec2(GNullClipRect.x, GNullClipRect.y), ImVec2(GNullClipRect.z, GNullClipRect.w));
	//PushClipRect(GetVisibleRect());   // FIXME-OPT: This would be more correct but we're not supposed to access ImGuiContext from here?
}

void ImDrawList::PopClipRect()
{
	IM_ASSERT(_ClipRectStack.Size > 0);
	_ClipRectStack.pop_back();
	UpdateClipRect();
}

void ImDrawList::PushTextureID(const ImTextureID& texture_id)
{
	_TextureIdStack.push_back(texture_id);
	UpdateTextureID();
}

void ImDrawList::PopTextureID()
{
	IM_ASSERT(_TextureIdStack.Size > 0);
	_TextureIdStack.pop_back();
	UpdateTextureID();
}

void ImDrawList::ChannelsSplit(int channels_count)
{
	IM_ASSERT(_ChannelsCurrent == 0 && _ChannelsCount == 1);
	int old_channels_count = _Channels.Size;
	if (old_channels_count < channels_count)
		_Channels.resize(channels_count);
	_ChannelsCount = channels_count;

	// _Channels[] (24 bytes each) hold storage that we'll swap with this->_CmdBuffer/_IdxBuffer
	// The content of _Channels[0] at this point doesn't matter. We clear it to make state tidy in a debugger but we don't strictly need to.
	// When we switch to the next channel, we'll copy _CmdBuffer/_IdxBuffer into _Channels[0] and then _Channels[1] into _CmdBuffer/_IdxBuffer
	memset(&_Channels[0], 0, sizeof(ImDrawChannel));
	for (int i = 1; i < channels_count; i++)
	{
		if (i >= old_channels_count)
		{
			IM_PLACEMENT_NEW(&_Channels[i]) ImDrawChannel();
		}
		else
		{
			_Channels[i].CmdBuffer.resize(0);
			_Channels[i].IdxBuffer.resize(0);
		}
		if (_Channels[i].CmdBuffer.Size == 0)
		{
			ImDrawCmd draw_cmd;
			draw_cmd.ClipRect = _ClipRectStack.back();
			draw_cmd.TextureId = _TextureIdStack.back();
			_Channels[i].CmdBuffer.push_back(draw_cmd);
		}
	}
}

void ImDrawList::ChannelsMerge()
{
	// Note that we never use or rely on channels.Size because it is merely a buffer that we never shrink back to 0 to keep all sub-buffers ready for use.
	if (_ChannelsCount <= 1)
		return;

	ChannelsSetCurrent(0);
	if (CmdBuffer.Size && CmdBuffer.back().ElemCount == 0)
		CmdBuffer.pop_back();

	int new_cmd_buffer_count = 0, new_idx_buffer_count = 0;
	for (int i = 1; i < _ChannelsCount; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (ch.CmdBuffer.Size && ch.CmdBuffer.back().ElemCount == 0)
			ch.CmdBuffer.pop_back();
		new_cmd_buffer_count += ch.CmdBuffer.Size;
		new_idx_buffer_count += ch.IdxBuffer.Size;
	}
	CmdBuffer.resize(CmdBuffer.Size + new_cmd_buffer_count);
	IdxBuffer.resize(IdxBuffer.Size + new_idx_buffer_count);

	ImDrawCmd* cmd_write = CmdBuffer.Data + CmdBuffer.Size - new_cmd_buffer_count;
	_IdxWritePtr = IdxBuffer.Data + IdxBuffer.Size - new_idx_buffer_count;
	for (int i = 1; i < _ChannelsCount; i++)
	{
		ImDrawChannel& ch = _Channels[i];
		if (int sz = ch.CmdBuffer.Size) { memcpy(cmd_write, ch.CmdBuffer.Data, sz * sizeof(ImDrawCmd)); cmd_write += sz; }
		if (int sz = ch.IdxBuffer.Size) { memcpy(_IdxWritePtr, ch.IdxBuffer.Data, sz * sizeof(ImDrawIdx)); _IdxWritePtr += sz; }
	}
	AddDrawCmd();
	_ChannelsCount = 1;
}

void ImDrawList::ChannelsSetCurrent(int idx)
{
	IM_ASSERT(idx < _ChannelsCount);
	if (_ChannelsCurrent == idx) return;
	memcpy(&_Channels.Data[_ChannelsCurrent].CmdBuffer, &CmdBuffer, sizeof(CmdBuffer)); // copy 12 bytes, four times
	memcpy(&_Channels.Data[_ChannelsCurrent].IdxBuffer, &IdxBuffer, sizeof(IdxBuffer));
	_ChannelsCurrent = idx;
	memcpy(&CmdBuffer, &_Channels.Data[_ChannelsCurrent].CmdBuffer, sizeof(CmdBuffer));
	memcpy(&IdxBuffer, &_Channels.Data[_ChannelsCurrent].IdxBuffer, sizeof(IdxBuffer));
	_IdxWritePtr = IdxBuffer.Data + IdxBuffer.Size;
}

// NB: this can be called with negative count for removing primitives (as long as the result does not underflow)
void ImDrawList::PrimReserve(int idx_count, int vtx_count)
{
	ImDrawCmd& draw_cmd = CmdBuffer.Data[CmdBuffer.Size - 1];
	draw_cmd.ElemCount += idx_count;

	int vtx_buffer_old_size = VtxBuffer.Size;
	VtxBuffer.resize(vtx_buffer_old_size + vtx_count);
	_VtxWritePtr = VtxBuffer.Data + vtx_buffer_old_size;

	int idx_buffer_old_size = IdxBuffer.Size;
	IdxBuffer.resize(idx_buffer_old_size + idx_count);
	_IdxWritePtr = IdxBuffer.Data + idx_buffer_old_size;
}

// Fully unrolled with inline call to keep our debug builds decently fast.
void ImDrawList::PrimRect(const ImVec2& a, const ImVec2& c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv(GImGui->FontTexUvWhitePixel);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimRectUV(const ImVec2& a, const ImVec2& c, const ImVec2& uv_a, const ImVec2& uv_c, ImU32 col)
{
	ImVec2 b(c.x, a.y), d(a.x, c.y), uv_b(uv_c.x, uv_a.y), uv_d(uv_a.x, uv_c.y);
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

void ImDrawList::PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col)
{
	ImDrawIdx idx = (ImDrawIdx)_VtxCurrentIdx;
	_IdxWritePtr[0] = idx; _IdxWritePtr[1] = (ImDrawIdx)(idx + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx + 2);
	_IdxWritePtr[3] = idx; _IdxWritePtr[4] = (ImDrawIdx)(idx + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx + 3);
	_VtxWritePtr[0].pos = a; _VtxWritePtr[0].uv = uv_a; _VtxWritePtr[0].col = col;
	_VtxWritePtr[1].pos = b; _VtxWritePtr[1].uv = uv_b; _VtxWritePtr[1].col = col;
	_VtxWritePtr[2].pos = c; _VtxWritePtr[2].uv = uv_c; _VtxWritePtr[2].col = col;
	_VtxWritePtr[3].pos = d; _VtxWritePtr[3].uv = uv_d; _VtxWritePtr[3].col = col;
	_VtxWritePtr += 4;
	_VtxCurrentIdx += 4;
	_IdxWritePtr += 6;
}

// TODO: Thickness anti-aliased lines cap are missing their AA fringe.
void ImDrawList::AddPolyline(const ImVec2* points, const int points_count, ImU32 col, bool closed, float thickness, bool anti_aliased)
{
	if (points_count < 2)
		return;

	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	anti_aliased &= GImGui->Style.AntiAliasedLines;
	//if (ImGui::GetIO().KeyCtrl) anti_aliased = false; // Debug

	int count = points_count;
	if (!closed)
		count = points_count - 1;

	const bool thick_line = thickness > 1.0f;
	if (anti_aliased)
	{
		// Anti-aliased stroke
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & IM_COL32(255, 255, 255, 0);

		const int idx_count = thick_line ? count * 18 : count * 12;
		const int vtx_count = thick_line ? points_count * 4 : points_count * 3;
		PrimReserve(idx_count, vtx_count);

		// Temporary buffer
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * (thick_line ? 5 : 3) * sizeof(ImVec2));
		ImVec2* temp_points = temp_normals + points_count;

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			ImVec2 diff = points[i2] - points[i1];
			diff *= ImInvLength(diff, 1.0f);
			temp_normals[i1].x = diff.y;
			temp_normals[i1].y = -diff.x;
		}
		if (!closed)
			temp_normals[points_count - 1] = temp_normals[points_count - 2];

		if (!thick_line)
		{
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * AA_SIZE;
				temp_points[1] = points[0] - temp_normals[0] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * AA_SIZE;
				temp_points[(points_count - 1) * 2 + 1] = points[points_count - 1] - temp_normals[points_count - 1] * AA_SIZE;
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 3;

				// Average normals
				ImVec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
				float dmr2 = dm.x*dm.x + dm.y*dm.y;
				if (dmr2 > 0.000001f)
				{
					float scale = 1.0f / dmr2;
					if (scale > 100.0f) scale = 100.0f;
					dm *= scale;
				}
				dm *= AA_SIZE;
				temp_points[i2 * 2 + 0] = points[i2] + dm;
				temp_points[i2 * 2 + 1] = points[i2] - dm;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 0);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr += 12;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = points[i];          _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
				_VtxWritePtr[1].pos = temp_points[i * 2 + 0]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans;
				_VtxWritePtr[2].pos = temp_points[i * 2 + 1]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col_trans;
				_VtxWritePtr += 3;
			}
		}
		else
		{
			const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
			if (!closed)
			{
				temp_points[0] = points[0] + temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[1] = points[0] + temp_normals[0] * (half_inner_thickness);
				temp_points[2] = points[0] - temp_normals[0] * (half_inner_thickness);
				temp_points[3] = points[0] - temp_normals[0] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 0] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
				temp_points[(points_count - 1) * 4 + 1] = points[points_count - 1] + temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 2] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness);
				temp_points[(points_count - 1) * 4 + 3] = points[points_count - 1] - temp_normals[points_count - 1] * (half_inner_thickness + AA_SIZE);
			}

			// FIXME-OPT: Merge the different loops, possibly remove the temporary buffer.
			unsigned int idx1 = _VtxCurrentIdx;
			for (int i1 = 0; i1 < count; i1++)
			{
				const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
				unsigned int idx2 = (i1 + 1) == points_count ? _VtxCurrentIdx : idx1 + 4;

				// Average normals
				ImVec2 dm = (temp_normals[i1] + temp_normals[i2]) * 0.5f;
				float dmr2 = dm.x*dm.x + dm.y*dm.y;
				if (dmr2 > 0.000001f)
				{
					float scale = 1.0f / dmr2;
					if (scale > 100.0f) scale = 100.0f;
					dm *= scale;
				}
				ImVec2 dm_out = dm * (half_inner_thickness + AA_SIZE);
				ImVec2 dm_in = dm * half_inner_thickness;
				temp_points[i2 * 4 + 0] = points[i2] + dm_out;
				temp_points[i2 * 4 + 1] = points[i2] + dm_in;
				temp_points[i2 * 4 + 2] = points[i2] - dm_in;
				temp_points[i2 * 4 + 3] = points[i2] - dm_out;

				// Add indexes
				_IdxWritePtr[0] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[1] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[2] = (ImDrawIdx)(idx1 + 2);
				_IdxWritePtr[3] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[4] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[5] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[6] = (ImDrawIdx)(idx2 + 1); _IdxWritePtr[7] = (ImDrawIdx)(idx1 + 1); _IdxWritePtr[8] = (ImDrawIdx)(idx1 + 0);
				_IdxWritePtr[9] = (ImDrawIdx)(idx1 + 0); _IdxWritePtr[10] = (ImDrawIdx)(idx2 + 0); _IdxWritePtr[11] = (ImDrawIdx)(idx2 + 1);
				_IdxWritePtr[12] = (ImDrawIdx)(idx2 + 2); _IdxWritePtr[13] = (ImDrawIdx)(idx1 + 2); _IdxWritePtr[14] = (ImDrawIdx)(idx1 + 3);
				_IdxWritePtr[15] = (ImDrawIdx)(idx1 + 3); _IdxWritePtr[16] = (ImDrawIdx)(idx2 + 3); _IdxWritePtr[17] = (ImDrawIdx)(idx2 + 2);
				_IdxWritePtr += 18;

				idx1 = idx2;
			}

			// Add vertexes
			for (int i = 0; i < points_count; i++)
			{
				_VtxWritePtr[0].pos = temp_points[i * 4 + 0]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col_trans;
				_VtxWritePtr[1].pos = temp_points[i * 4 + 1]; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
				_VtxWritePtr[2].pos = temp_points[i * 4 + 2]; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
				_VtxWritePtr[3].pos = temp_points[i * 4 + 3]; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col_trans;
				_VtxWritePtr += 4;
			}
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Stroke
		const int idx_count = count * 6;
		const int vtx_count = count * 4;      // FIXME-OPT: Not sharing edges
		PrimReserve(idx_count, vtx_count);

		for (int i1 = 0; i1 < count; i1++)
		{
			const int i2 = (i1 + 1) == points_count ? 0 : i1 + 1;
			const ImVec2& p1 = points[i1];
			const ImVec2& p2 = points[i2];
			ImVec2 diff = p2 - p1;
			diff *= ImInvLength(diff, 1.0f);

			const float dx = diff.x * (thickness * 0.5f);
			const float dy = diff.y * (thickness * 0.5f);
			_VtxWritePtr[0].pos.x = p1.x + dy; _VtxWritePtr[0].pos.y = p1.y - dx; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr[1].pos.x = p2.x + dy; _VtxWritePtr[1].pos.y = p2.y - dx; _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col;
			_VtxWritePtr[2].pos.x = p2.x - dy; _VtxWritePtr[2].pos.y = p2.y + dx; _VtxWritePtr[2].uv = uv; _VtxWritePtr[2].col = col;
			_VtxWritePtr[3].pos.x = p1.x - dy; _VtxWritePtr[3].pos.y = p1.y + dx; _VtxWritePtr[3].uv = uv; _VtxWritePtr[3].col = col;
			_VtxWritePtr += 4;

			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + 2);
			_IdxWritePtr[3] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[4] = (ImDrawIdx)(_VtxCurrentIdx + 2); _IdxWritePtr[5] = (ImDrawIdx)(_VtxCurrentIdx + 3);
			_IdxWritePtr += 6;
			_VtxCurrentIdx += 4;
		}
	}
}

void ImDrawList::AddConvexPolyFilled(const ImVec2* points, const int points_count, ImU32 col, bool anti_aliased)
{
	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	anti_aliased &= GImGui->Style.AntiAliasedShapes;
	//if (ImGui::GetIO().KeyCtrl) anti_aliased = false; // Debug

	if (anti_aliased)
	{
		// Anti-aliased Fill
		const float AA_SIZE = 1.0f;
		const ImU32 col_trans = col & IM_COL32(255, 255, 255, 0);
		const int idx_count = (points_count - 2) * 3 + points_count * 6;
		const int vtx_count = (points_count * 2);
		PrimReserve(idx_count, vtx_count);

		// Add indexes for fill
		unsigned int vtx_inner_idx = _VtxCurrentIdx;
		unsigned int vtx_outer_idx = _VtxCurrentIdx + 1;
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + ((i - 1) << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_inner_idx + (i << 1));
			_IdxWritePtr += 3;
		}

		// Compute normals
		ImVec2* temp_normals = (ImVec2*)alloca(points_count * sizeof(ImVec2));
		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			const ImVec2& p0 = points[i0];
			const ImVec2& p1 = points[i1];
			ImVec2 diff = p1 - p0;
			diff *= ImInvLength(diff, 1.0f);
			temp_normals[i0].x = diff.y;
			temp_normals[i0].y = -diff.x;
		}

		for (int i0 = points_count - 1, i1 = 0; i1 < points_count; i0 = i1++)
		{
			// Average normals
			const ImVec2& n0 = temp_normals[i0];
			const ImVec2& n1 = temp_normals[i1];
			ImVec2 dm = (n0 + n1) * 0.5f;
			float dmr2 = dm.x*dm.x + dm.y*dm.y;
			if (dmr2 > 0.000001f)
			{
				float scale = 1.0f / dmr2;
				if (scale > 100.0f) scale = 100.0f;
				dm *= scale;
			}
			dm *= AA_SIZE * 0.5f;

			// Add vertices
			_VtxWritePtr[0].pos = (points[i1] - dm); _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;        // Inner
			_VtxWritePtr[1].pos = (points[i1] + dm); _VtxWritePtr[1].uv = uv; _VtxWritePtr[1].col = col_trans;  // Outer
			_VtxWritePtr += 2;

			// Add indexes for fringes
			_IdxWritePtr[0] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1)); _IdxWritePtr[1] = (ImDrawIdx)(vtx_inner_idx + (i0 << 1)); _IdxWritePtr[2] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1));
			_IdxWritePtr[3] = (ImDrawIdx)(vtx_outer_idx + (i0 << 1)); _IdxWritePtr[4] = (ImDrawIdx)(vtx_outer_idx + (i1 << 1)); _IdxWritePtr[5] = (ImDrawIdx)(vtx_inner_idx + (i1 << 1));
			_IdxWritePtr += 6;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
	else
	{
		// Non Anti-aliased Fill
		const int idx_count = (points_count - 2) * 3;
		const int vtx_count = points_count;
		PrimReserve(idx_count, vtx_count);
		for (int i = 0; i < vtx_count; i++)
		{
			_VtxWritePtr[0].pos = points[i]; _VtxWritePtr[0].uv = uv; _VtxWritePtr[0].col = col;
			_VtxWritePtr++;
		}
		for (int i = 2; i < points_count; i++)
		{
			_IdxWritePtr[0] = (ImDrawIdx)(_VtxCurrentIdx); _IdxWritePtr[1] = (ImDrawIdx)(_VtxCurrentIdx + i - 1); _IdxWritePtr[2] = (ImDrawIdx)(_VtxCurrentIdx + i);
			_IdxWritePtr += 3;
		}
		_VtxCurrentIdx += (ImDrawIdx)vtx_count;
	}
}

void ImDrawList::PathArcToFast(const ImVec2& centre, float radius, int amin, int amax)
{
	static ImVec2 circle_vtx[12];
	static bool circle_vtx_builds = false;
	const int circle_vtx_count = IM_ARRAYSIZE(circle_vtx);
	if (!circle_vtx_builds)
	{
		for (int i = 0; i < circle_vtx_count; i++)
		{
			const float a = ((float)i / (float)circle_vtx_count) * 2 * IM_PI;
			circle_vtx[i].x = cosf(a);
			circle_vtx[i].y = sinf(a);
		}
		circle_vtx_builds = true;
	}

	if (amin > amax) return;
	if (radius == 0.0f)
	{
		_Path.push_back(centre);
	}
	else
	{
		_Path.reserve(_Path.Size + (amax - amin + 1));
		for (int a = amin; a <= amax; a++)
		{
			const ImVec2& c = circle_vtx[a % circle_vtx_count];
			_Path.push_back(ImVec2(centre.x + c.x * radius, centre.y + c.y * radius));
		}
	}
}

void ImDrawList::PathArcTo(const ImVec2& centre, float radius, float amin, float amax, int num_segments)
{
	if (radius == 0.0f)
		_Path.push_back(centre);
	_Path.reserve(_Path.Size + (num_segments + 1));
	for (int i = 0; i <= num_segments; i++)
	{
		const float a = amin + ((float)i / (float)num_segments) * (amax - amin);
		_Path.push_back(ImVec2(centre.x + cosf(a) * radius, centre.y + sinf(a) * radius));
	}
}

static void PathBezierToCasteljau(ImVector<ImVec2>* path, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tess_tol, int level)
{
	float dx = x4 - x1;
	float dy = y4 - y1;
	float d2 = ((x2 - x4) * dy - (y2 - y4) * dx);
	float d3 = ((x3 - x4) * dy - (y3 - y4) * dx);
	d2 = (d2 >= 0) ? d2 : -d2;
	d3 = (d3 >= 0) ? d3 : -d3;
	if ((d2 + d3) * (d2 + d3) < tess_tol * (dx*dx + dy*dy))
	{
		path->push_back(ImVec2(x4, y4));
	}
	else if (level < 10)
	{
		float x12 = (x1 + x2)*0.5f, y12 = (y1 + y2)*0.5f;
		float x23 = (x2 + x3)*0.5f, y23 = (y2 + y3)*0.5f;
		float x34 = (x3 + x4)*0.5f, y34 = (y3 + y4)*0.5f;
		float x123 = (x12 + x23)*0.5f, y123 = (y12 + y23)*0.5f;
		float x234 = (x23 + x34)*0.5f, y234 = (y23 + y34)*0.5f;
		float x1234 = (x123 + x234)*0.5f, y1234 = (y123 + y234)*0.5f;

		PathBezierToCasteljau(path, x1, y1, x12, y12, x123, y123, x1234, y1234, tess_tol, level + 1);
		PathBezierToCasteljau(path, x1234, y1234, x234, y234, x34, y34, x4, y4, tess_tol, level + 1);
	}
}

void ImDrawList::PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments)
{
	ImVec2 p1 = _Path.back();
	if (num_segments == 0)
	{
		// Auto-tessellated
		PathBezierToCasteljau(&_Path, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, GImGui->Style.CurveTessellationTol, 0);
	}
	else
	{
		float t_step = 1.0f / (float)num_segments;
		for (int i_step = 1; i_step <= num_segments; i_step++)
		{
			float t = t_step * i_step;
			float u = 1.0f - t;
			float w1 = u*u*u;
			float w2 = 3 * u*u*t;
			float w3 = 3 * u*t*t;
			float w4 = t*t*t;
			_Path.push_back(ImVec2(w1*p1.x + w2*p2.x + w3*p3.x + w4*p4.x, w1*p1.y + w2*p2.y + w3*p3.y + w4*p4.y));
		}
	}
}

void ImDrawList::PathRect(const ImVec2& a, const ImVec2& b, float rounding, int rounding_corners)
{
	float r = rounding;
	r = ImMin(r, fabsf(b.x - a.x) * (((rounding_corners&(1 | 2)) == (1 | 2)) || ((rounding_corners&(4 | 8)) == (4 | 8)) ? 0.5f : 1.0f) - 1.0f);
	r = ImMin(r, fabsf(b.y - a.y) * (((rounding_corners&(1 | 8)) == (1 | 8)) || ((rounding_corners&(2 | 4)) == (2 | 4)) ? 0.5f : 1.0f) - 1.0f);

	if (r <= 0.0f || rounding_corners == 0)
	{
		PathLineTo(a);
		PathLineTo(ImVec2(b.x, a.y));
		PathLineTo(b);
		PathLineTo(ImVec2(a.x, b.y));
	}
	else
	{
		const float r0 = (rounding_corners & 1) ? r : 0.0f;
		const float r1 = (rounding_corners & 2) ? r : 0.0f;
		const float r2 = (rounding_corners & 4) ? r : 0.0f;
		const float r3 = (rounding_corners & 8) ? r : 0.0f;
		PathArcToFast(ImVec2(a.x + r0, a.y + r0), r0, 6, 9);
		PathArcToFast(ImVec2(b.x - r1, a.y + r1), r1, 9, 12);
		PathArcToFast(ImVec2(b.x - r2, b.y - r2), r2, 0, 3);
		PathArcToFast(ImVec2(a.x + r3, b.y - r3), r3, 3, 6);
	}
}

void ImDrawList::AddLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	PathLineTo(a + ImVec2(0.5f, 0.5f));
	PathLineTo(b + ImVec2(0.5f, 0.5f));
	PathStroke(col, false, thickness);
}

// a: upper-left, b: lower-right. we don't render 1 px sized rectangles properly.
void ImDrawList::AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding, int rounding_corners_flags, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	PathRect(a + ImVec2(0.5f, 0.5f), b - ImVec2(0.5f, 0.5f), rounding, rounding_corners_flags);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddRectFilled(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding, int rounding_corners_flags)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;
	if (rounding > 0.0f)
	{
		PathRect(a, b, rounding, rounding_corners_flags);
		PathFillConvex(col);
	}
	else
	{
		PrimReserve(6, 4);
		PrimRect(a, b, col);
	}
}

void ImDrawList::AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left)
{
	if (((col_upr_left | col_upr_right | col_bot_right | col_bot_left) & IM_COL32_A_MASK) == 0)
		return;

	const ImVec2 uv = GImGui->FontTexUvWhitePixel;
	PrimReserve(6, 4);
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 1)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2));
	PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 2)); PrimWriteIdx((ImDrawIdx)(_VtxCurrentIdx + 3));
	PrimWriteVtx(a, uv, col_upr_left);
	PrimWriteVtx(ImVec2(c.x, a.y), uv, col_upr_right);
	PrimWriteVtx(c, uv, col_bot_right);
	PrimWriteVtx(ImVec2(a.x, c.y), uv, col_bot_left);
}

void ImDrawList::AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathLineTo(d);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathLineTo(d);
	PathFillConvex(col);
}

void ImDrawList::AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(a);
	PathLineTo(b);
	PathLineTo(c);
	PathFillConvex(col);
}

void ImDrawList::AddCircle(const ImVec2& centre, float radius, ImU32 col, int num_segments, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const float a_max = IM_PI*2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(centre, radius - 0.5f, 0.0f, a_max, num_segments);
	PathStroke(col, true, thickness);
}

void ImDrawList::AddCircleFilled(const ImVec2& centre, float radius, ImU32 col, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const float a_max = IM_PI*2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	PathArcTo(centre, radius, 0.0f, a_max, num_segments);
	PathFillConvex(col);
}

void ImDrawList::AddBezierCurve(const ImVec2& pos0, const ImVec2& cp0, const ImVec2& cp1, const ImVec2& pos1, ImU32 col, float thickness, int num_segments)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	PathLineTo(pos0);
	PathBezierCurveTo(cp0, cp1, pos1, num_segments);
	PathStroke(col, false, thickness);
}

void ImDrawList::AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	if (text_end == NULL)
		text_end = text_begin + strlen(text_begin);
	if (text_begin == text_end)
		return;

	// IMPORTANT: This is one of the few instance of breaking the encapsulation of ImDrawList, as we pull this from ImGui state, but it is just SO useful.
	// Might just move Font/FontSize to ImDrawList?
	if (font == NULL)
		font = GImGui->Font;
	if (font_size == 0.0f)
		font_size = GImGui->FontSize;

	IM_ASSERT(font->ContainerAtlas->TexID == _TextureIdStack.back());  // Use high-level ImGui::PushFont() or low-level ImDrawList::PushTextureId() to change font.

	ImVec4 clip_rect = _ClipRectStack.back();
	if (cpu_fine_clip_rect)
	{
		clip_rect.x = ImMax(clip_rect.x, cpu_fine_clip_rect->x);
		clip_rect.y = ImMax(clip_rect.y, cpu_fine_clip_rect->y);
		clip_rect.z = ImMin(clip_rect.z, cpu_fine_clip_rect->z);
		clip_rect.w = ImMin(clip_rect.w, cpu_fine_clip_rect->w);
	}
	font->RenderText(this, font_size, pos, col, clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip_rect != NULL);
}

void ImDrawList::AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end)
{
	AddText(NULL, 0.0f, pos, col, text_begin, text_end);
}

void ImDrawList::AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	// FIXME-OPT: This is wasting draw calls.
	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimRectUV(a, b, uv_a, uv_b, col);

	if (push_texture_id)
		PopTextureID();
}

void ImDrawList::AddImageQuad(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	const bool push_texture_id = _TextureIdStack.empty() || user_texture_id != _TextureIdStack.back();
	if (push_texture_id)
		PushTextureID(user_texture_id);

	PrimReserve(6, 4);
	PrimQuadUV(a, b, c, d, uv_a, uv_b, uv_c, uv_d, col);

	if (push_texture_id)
		PopTextureID();
}

//-----------------------------------------------------------------------------
// ImDrawData
//-----------------------------------------------------------------------------

// For backward compatibility: convert all buffers from indexed to de-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
void ImDrawData::DeIndexAllBuffers()
{
	ImVector<ImDrawVert> new_vtx_buffer;
	TotalVtxCount = TotalIdxCount = 0;
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		if (cmd_list->IdxBuffer.empty())
			continue;
		new_vtx_buffer.resize(cmd_list->IdxBuffer.Size);
		for (int j = 0; j < cmd_list->IdxBuffer.Size; j++)
			new_vtx_buffer[j] = cmd_list->VtxBuffer[cmd_list->IdxBuffer[j]];
		cmd_list->VtxBuffer.swap(new_vtx_buffer);
		cmd_list->IdxBuffer.resize(0);
		TotalVtxCount += cmd_list->VtxBuffer.Size;
	}
}

// Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
void ImDrawData::ScaleClipRects(const ImVec2& scale)
{
	for (int i = 0; i < CmdListsCount; i++)
	{
		ImDrawList* cmd_list = CmdLists[i];
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			ImDrawCmd* cmd = &cmd_list->CmdBuffer[cmd_i];
			cmd->ClipRect = ImVec4(cmd->ClipRect.x * scale.x, cmd->ClipRect.y * scale.y, cmd->ClipRect.z * scale.x, cmd->ClipRect.w * scale.y);
		}
	}
}

//-----------------------------------------------------------------------------
// ImFontAtlas
//-----------------------------------------------------------------------------

ImFontConfig::ImFontConfig()
{
	FontData = NULL;
	FontDataSize = 0;
	FontDataOwnedByAtlas = true;
	FontNo = 0;
	SizePixels = 0.0f;
	OversampleH = 3;
	OversampleV = 1;
	PixelSnapH = false;
	GlyphExtraSpacing = ImVec2(0.0f, 0.0f);
	GlyphOffset = ImVec2(0.0f, 0.0f);
	GlyphRanges = NULL;
	MergeMode = false;
	DstFont = NULL;
	memset(Name, 0, sizeof(Name));
}

ImFontAtlas::ImFontAtlas()
{
	TexID = NULL;
	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
	TexWidth = TexHeight = TexDesiredWidth = 0;
	TexUvWhitePixel = ImVec2(0, 0);
}

ImFontAtlas::~ImFontAtlas()
{
	Clear();
}

void    ImFontAtlas::ClearInputData()
{
	for (int i = 0; i < ConfigData.Size; i++)
		if (ConfigData[i].FontData && ConfigData[i].FontDataOwnedByAtlas)
		{
			ImGui::MemFree(ConfigData[i].FontData);
			ConfigData[i].FontData = NULL;
		}

	// When clearing this we lose access to the font name and other information used to build the font.
	for (int i = 0; i < Fonts.Size; i++)
		if (Fonts[i]->ConfigData >= ConfigData.Data && Fonts[i]->ConfigData < ConfigData.Data + ConfigData.Size)
		{
			Fonts[i]->ConfigData = NULL;
			Fonts[i]->ConfigDataCount = 0;
		}
	ConfigData.clear();
}

void    ImFontAtlas::ClearTexData()
{
	if (TexPixelsAlpha8)
		ImGui::MemFree(TexPixelsAlpha8);
	if (TexPixelsRGBA32)
		ImGui::MemFree(TexPixelsRGBA32);
	TexPixelsAlpha8 = NULL;
	TexPixelsRGBA32 = NULL;
}

void    ImFontAtlas::ClearFonts()
{
	for (int i = 0; i < Fonts.Size; i++)
	{
		Fonts[i]->~ImFont();
		ImGui::MemFree(Fonts[i]);
	}
	Fonts.clear();
}

void    ImFontAtlas::Clear()
{
	ClearInputData();
	ClearTexData();
	ClearFonts();
}

void    ImFontAtlas::GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Build atlas on demand
	if (TexPixelsAlpha8 == NULL)
	{
		if (ConfigData.empty())
			AddFontDefault();
		Build();
	}

	*out_pixels = TexPixelsAlpha8;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 1;
}

void    ImFontAtlas::GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	// Convert to RGBA32 format on demand
	// Although it is likely to be the most commonly used format, our font rendering is 1 channel / 8 bpp
	if (!TexPixelsRGBA32)
	{
		unsigned char* pixels;
		GetTexDataAsAlpha8(&pixels, NULL, NULL);
		TexPixelsRGBA32 = (unsigned int*)ImGui::MemAlloc((size_t)(TexWidth * TexHeight * 4));
		const unsigned char* src = pixels;
		unsigned int* dst = TexPixelsRGBA32;
		for (int n = TexWidth * TexHeight; n > 0; n--)
			*dst++ = IM_COL32(255, 255, 255, (unsigned int)(*src++));
	}

	*out_pixels = (unsigned char*)TexPixelsRGBA32;
	if (out_width) *out_width = TexWidth;
	if (out_height) *out_height = TexHeight;
	if (out_bytes_per_pixel) *out_bytes_per_pixel = 4;
}

ImFont* ImFontAtlas::AddFont(const ImFontConfig* font_cfg)
{
	IM_ASSERT(font_cfg->FontData != NULL && font_cfg->FontDataSize > 0);
	IM_ASSERT(font_cfg->SizePixels > 0.0f);

	// Create new font
	if (!font_cfg->MergeMode)
	{
		ImFont* font = (ImFont*)ImGui::MemAlloc(sizeof(ImFont));
		IM_PLACEMENT_NEW(font) ImFont();
		Fonts.push_back(font);
	}
	else
	{
		IM_ASSERT(!Fonts.empty()); // When using MergeMode make sure that a font has already been added before. You can use ImGui::GetIO().Fonts->AddFontDefault() to add the default imgui font.
	}

	ConfigData.push_back(*font_cfg);
	ImFontConfig& new_font_cfg = ConfigData.back();
	if (!new_font_cfg.DstFont)
		new_font_cfg.DstFont = Fonts.back();
	if (!new_font_cfg.FontDataOwnedByAtlas)
	{
		new_font_cfg.FontData = ImGui::MemAlloc(new_font_cfg.FontDataSize);
		new_font_cfg.FontDataOwnedByAtlas = true;
		memcpy(new_font_cfg.FontData, font_cfg->FontData, (size_t)new_font_cfg.FontDataSize);
	}

	// Invalidate texture
	ClearTexData();
	return new_font_cfg.DstFont;
}

// Default font TTF is compressed with stb_compress then base85 encoded (see extra_fonts/binary_to_compressed_c.cpp for encoder)
static unsigned int stb_decompress_length(unsigned char *input);
static unsigned int stb_decompress(unsigned char *output, unsigned char *i, unsigned int length);
static const char*  GetDefaultCompressedFontDataTTFBase85();
static unsigned int Decode85Byte(char c) { return c >= '\\' ? c - 36 : c - 35; }
static void         Decode85(const unsigned char* src, unsigned char* dst)
{
	while (*src)
	{
		unsigned int tmp = Decode85Byte(src[0]) + 85 * (Decode85Byte(src[1]) + 85 * (Decode85Byte(src[2]) + 85 * (Decode85Byte(src[3]) + 85 * Decode85Byte(src[4]))));
		dst[0] = ((tmp >> 0) & 0xFF); dst[1] = ((tmp >> 8) & 0xFF); dst[2] = ((tmp >> 16) & 0xFF); dst[3] = ((tmp >> 24) & 0xFF);   // We can't assume little-endianness.
		src += 5;
		dst += 4;
	}
}

// Load embedded ProggyClean.ttf at size 13, disable oversampling
ImFont* ImFontAtlas::AddFontDefault(const ImFontConfig* font_cfg_template)
{
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	if (!font_cfg_template)
	{
		font_cfg.OversampleH = font_cfg.OversampleV = 1;
		font_cfg.PixelSnapH = true;
	}
	if (font_cfg.Name[0] == '\0') strcpy(font_cfg.Name, "ProggyClean.ttf, 1px");

	const char* ttf_compressed_base85 = GetDefaultCompressedFontDataTTFBase85();
	ImFont* font = AddFontFromMemoryCompressedBase85TTF(ttf_compressed_base85, 13.0f, &font_cfg, GetGlyphRangesDefault());
	return font;
}

ImFont* ImFontAtlas::AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	int data_size = 0;
	void* data = ImFileLoadToMemory(filename, "rb", &data_size, 0);
	if (!data)
	{
		IM_ASSERT(0); // Could not load file.
		return NULL;
	}
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	if (font_cfg.Name[0] == '\0')
	{
		// Store a short copy of filename into into the font name for convenience
		const char* p;
		for (p = filename + strlen(filename); p > filename && p[-1] != '/' && p[-1] != '\\'; p--) {}
		snprintf(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), "%s, %.0fpx", p, size_pixels);
	}
	return AddFontFromMemoryTTF(data, data_size, size_pixels, &font_cfg, glyph_ranges);
}

// NBM Transfer ownership of 'ttf_data' to ImFontAtlas, unless font_cfg_template->FontDataOwnedByAtlas == false. Owned TTF buffer will be deleted after Build().
ImFont* ImFontAtlas::AddFontFromMemoryTTF(void* ttf_data, int ttf_size, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	IM_ASSERT(font_cfg.FontData == NULL);
	font_cfg.FontData = ttf_data;
	font_cfg.FontDataSize = ttf_size;
	font_cfg.SizePixels = size_pixels;
	if (glyph_ranges)
		font_cfg.GlyphRanges = glyph_ranges;
	return AddFont(&font_cfg);
}

ImFont* ImFontAtlas::AddFontFromMemoryCompressedTTF(const void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, const ImFontConfig* font_cfg_template, const ImWchar* glyph_ranges)
{
	const unsigned int buf_decompressed_size = stb_decompress_length((unsigned char*)compressed_ttf_data);
	unsigned char* buf_decompressed_data = (unsigned char *)ImGui::MemAlloc(buf_decompressed_size);
	stb_decompress(buf_decompressed_data, (unsigned char*)compressed_ttf_data, (unsigned int)compressed_ttf_size);

	ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
	IM_ASSERT(font_cfg.FontData == NULL);
	font_cfg.FontDataOwnedByAtlas = true;
	return AddFontFromMemoryTTF(buf_decompressed_data, (int)buf_decompressed_size, size_pixels, &font_cfg, glyph_ranges);
}

ImFont* ImFontAtlas::AddFontFromMemoryCompressedBase85TTF(const char* compressed_ttf_data_base85, float size_pixels, const ImFontConfig* font_cfg, const ImWchar* glyph_ranges)
{
	int compressed_ttf_size = (((int)strlen(compressed_ttf_data_base85) + 4) / 5) * 4;
	void* compressed_ttf = ImGui::MemAlloc((size_t)compressed_ttf_size);
	Decode85((const unsigned char*)compressed_ttf_data_base85, (unsigned char*)compressed_ttf);
	ImFont* font = AddFontFromMemoryCompressedTTF(compressed_ttf, compressed_ttf_size, size_pixels, font_cfg, glyph_ranges);
	ImGui::MemFree(compressed_ttf);
	return font;
}


bool    ImFontAtlas::Build()
{
	IM_ASSERT(ConfigData.Size > 0);

	TexID = NULL;
	TexWidth = TexHeight = 0;
	TexUvWhitePixel = ImVec2(0, 0);
	ClearTexData();

	struct ImFontTempBuildData
	{
		stbtt_fontinfo      FontInfo;
		stbrp_rect*         Rects;
		stbtt_pack_range*   Ranges;
		int                 RangesCount;
	};
	ImFontTempBuildData* tmp_array = (ImFontTempBuildData*)ImGui::MemAlloc((size_t)ConfigData.Size * sizeof(ImFontTempBuildData));

	// Initialize font information early (so we can error without any cleanup) + count glyphs
	int total_glyph_count = 0;
	int total_glyph_range_count = 0;
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];

		IM_ASSERT(cfg.DstFont && (!cfg.DstFont->IsLoaded() || cfg.DstFont->ContainerAtlas == this));
		const int font_offset = stbtt_GetFontOffsetForIndex((unsigned char*)cfg.FontData, cfg.FontNo);
		IM_ASSERT(font_offset >= 0);
		if (!stbtt_InitFont(&tmp.FontInfo, (unsigned char*)cfg.FontData, font_offset))
			return false;

		// Count glyphs
		if (!cfg.GlyphRanges)
			cfg.GlyphRanges = GetGlyphRangesDefault();
		for (const ImWchar* in_range = cfg.GlyphRanges; in_range[0] && in_range[1]; in_range += 2)
		{
			total_glyph_count += (in_range[1] - in_range[0]) + 1;
			total_glyph_range_count++;
		}
	}

	// Start packing. We need a known width for the skyline algorithm. Using a cheap heuristic here to decide of width. User can override TexDesiredWidth if they wish.
	// After packing is done, width shouldn't matter much, but some API/GPU have texture size limitations and increasing width can decrease height.
	TexWidth = (TexDesiredWidth > 0) ? TexDesiredWidth : (total_glyph_count > 4000) ? 4096 : (total_glyph_count > 2000) ? 2048 : (total_glyph_count > 1000) ? 1024 : 512;
	TexHeight = 0;
	const int max_tex_height = 1024 * 32;
	stbtt_pack_context spc;
	stbtt_PackBegin(&spc, NULL, TexWidth, max_tex_height, 0, 1, NULL);

	// Pack our extra data rectangles first, so it will be on the upper-left corner of our texture (UV will have small values).
	ImVector<stbrp_rect> extra_rects;
	RenderCustomTexData(0, &extra_rects);
	stbtt_PackSetOversampling(&spc, 1, 1);
	stbrp_pack_rects((stbrp_context*)spc.pack_info, &extra_rects[0], extra_rects.Size);
	for (int i = 0; i < extra_rects.Size; i++)
		if (extra_rects[i].was_packed)
			TexHeight = ImMax(TexHeight, extra_rects[i].y + extra_rects[i].h);

	// Allocate packing character data and flag packed characters buffer as non-packed (x0=y0=x1=y1=0)
	int buf_packedchars_n = 0, buf_rects_n = 0, buf_ranges_n = 0;
	stbtt_packedchar* buf_packedchars = (stbtt_packedchar*)ImGui::MemAlloc(total_glyph_count * sizeof(stbtt_packedchar));
	stbrp_rect* buf_rects = (stbrp_rect*)ImGui::MemAlloc(total_glyph_count * sizeof(stbrp_rect));
	stbtt_pack_range* buf_ranges = (stbtt_pack_range*)ImGui::MemAlloc(total_glyph_range_count * sizeof(stbtt_pack_range));
	memset(buf_packedchars, 0, total_glyph_count * sizeof(stbtt_packedchar));
	memset(buf_rects, 0, total_glyph_count * sizeof(stbrp_rect));              // Unnecessary but let's clear this for the sake of sanity.
	memset(buf_ranges, 0, total_glyph_range_count * sizeof(stbtt_pack_range));

	// First font pass: pack all glyphs (no rendering at this point, we are working with rectangles in an infinitely tall texture at this point)
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];

		// Setup ranges
		int glyph_count = 0;
		int glyph_ranges_count = 0;
		for (const ImWchar* in_range = cfg.GlyphRanges; in_range[0] && in_range[1]; in_range += 2)
		{
			glyph_count += (in_range[1] - in_range[0]) + 1;
			glyph_ranges_count++;
		}
		tmp.Ranges = buf_ranges + buf_ranges_n;
		tmp.RangesCount = glyph_ranges_count;
		buf_ranges_n += glyph_ranges_count;
		for (int i = 0; i < glyph_ranges_count; i++)
		{
			const ImWchar* in_range = &cfg.GlyphRanges[i * 2];
			stbtt_pack_range& range = tmp.Ranges[i];
			range.font_size = cfg.SizePixels;
			range.first_unicode_codepoint_in_range = in_range[0];
			range.num_chars = (in_range[1] - in_range[0]) + 1;
			range.chardata_for_range = buf_packedchars + buf_packedchars_n;
			buf_packedchars_n += range.num_chars;
		}

		// Pack
		tmp.Rects = buf_rects + buf_rects_n;
		buf_rects_n += glyph_count;
		stbtt_PackSetOversampling(&spc, cfg.OversampleH, cfg.OversampleV);
		int n = stbtt_PackFontRangesGatherRects(&spc, &tmp.FontInfo, tmp.Ranges, tmp.RangesCount, tmp.Rects);
		stbrp_pack_rects((stbrp_context*)spc.pack_info, tmp.Rects, n);

		// Extend texture height
		for (int i = 0; i < n; i++)
			if (tmp.Rects[i].was_packed)
				TexHeight = ImMax(TexHeight, tmp.Rects[i].y + tmp.Rects[i].h);
	}
	IM_ASSERT(buf_rects_n == total_glyph_count);
	IM_ASSERT(buf_packedchars_n == total_glyph_count);
	IM_ASSERT(buf_ranges_n == total_glyph_range_count);

	// Create texture
	TexHeight = ImUpperPowerOfTwo(TexHeight);
	TexPixelsAlpha8 = (unsigned char*)ImGui::MemAlloc(TexWidth * TexHeight);
	memset(TexPixelsAlpha8, 0, TexWidth * TexHeight);
	spc.pixels = TexPixelsAlpha8;
	spc.height = TexHeight;

	// Second pass: render characters
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];
		stbtt_PackSetOversampling(&spc, cfg.OversampleH, cfg.OversampleV);
		stbtt_PackFontRangesRenderIntoRects(&spc, &tmp.FontInfo, tmp.Ranges, tmp.RangesCount, tmp.Rects);
		tmp.Rects = NULL;
	}

	// End packing
	stbtt_PackEnd(&spc);
	ImGui::MemFree(buf_rects);
	buf_rects = NULL;

	// Third pass: setup ImFont and glyphs for runtime
	for (int input_i = 0; input_i < ConfigData.Size; input_i++)
	{
		ImFontConfig& cfg = ConfigData[input_i];
		ImFontTempBuildData& tmp = tmp_array[input_i];
		ImFont* dst_font = cfg.DstFont; // We can have multiple input fonts writing into a same destination font (when using MergeMode=true)

		float font_scale = stbtt_ScaleForPixelHeight(&tmp.FontInfo, cfg.SizePixels);
		int unscaled_ascent, unscaled_descent, unscaled_line_gap;
		stbtt_GetFontVMetrics(&tmp.FontInfo, &unscaled_ascent, &unscaled_descent, &unscaled_line_gap);

		float ascent = unscaled_ascent * font_scale;
		float descent = unscaled_descent * font_scale;
		if (!cfg.MergeMode)
		{
			dst_font->ContainerAtlas = this;
			dst_font->ConfigData = &cfg;
			dst_font->ConfigDataCount = 0;
			dst_font->FontSize = cfg.SizePixels;
			dst_font->Ascent = ascent;
			dst_font->Descent = descent;
			dst_font->Glyphs.resize(0);
			dst_font->MetricsTotalSurface = 0;
		}
		dst_font->ConfigDataCount++;
		float off_x = cfg.GlyphOffset.x;
		float off_y = cfg.GlyphOffset.y;

		dst_font->FallbackGlyph = NULL; // Always clear fallback so FindGlyph can return NULL. It will be set again in BuildLookupTable()
		for (int i = 0; i < tmp.RangesCount; i++)
		{
			stbtt_pack_range& range = tmp.Ranges[i];
			for (int char_idx = 0; char_idx < range.num_chars; char_idx += 1)
			{
				const stbtt_packedchar& pc = range.chardata_for_range[char_idx];
				if (!pc.x0 && !pc.x1 && !pc.y0 && !pc.y1)
					continue;

				const int codepoint = range.first_unicode_codepoint_in_range + char_idx;
				if (cfg.MergeMode && dst_font->FindGlyph((unsigned short)codepoint))
					continue;

				stbtt_aligned_quad q;
				float dummy_x = 0.0f, dummy_y = 0.0f;
				stbtt_GetPackedQuad(range.chardata_for_range, TexWidth, TexHeight, char_idx, &dummy_x, &dummy_y, &q, 0);

				dst_font->Glyphs.resize(dst_font->Glyphs.Size + 1);
				ImFont::Glyph& glyph = dst_font->Glyphs.back();
				glyph.Codepoint = (ImWchar)codepoint;
				glyph.X0 = q.x0 + off_x; glyph.Y0 = q.y0 + off_y; glyph.X1 = q.x1 + off_x; glyph.Y1 = q.y1 + off_y;
				glyph.U0 = q.s0; glyph.V0 = q.t0; glyph.U1 = q.s1; glyph.V1 = q.t1;
				glyph.Y0 += (float)(int)(dst_font->Ascent + 0.5f);
				glyph.Y1 += (float)(int)(dst_font->Ascent + 0.5f);
				glyph.XAdvance = (pc.xadvance + cfg.GlyphExtraSpacing.x);  // Bake spacing into XAdvance
				if (cfg.PixelSnapH)
					glyph.XAdvance = (float)(int)(glyph.XAdvance + 0.5f);
				dst_font->MetricsTotalSurface += (int)((glyph.U1 - glyph.U0) * TexWidth + 1.99f) * (int)((glyph.V1 - glyph.V0) * TexHeight + 1.99f); // +1 to account for average padding, +0.99 to round
			}
		}
		cfg.DstFont->BuildLookupTable();
	}

	// Cleanup temporaries
	ImGui::MemFree(buf_packedchars);
	ImGui::MemFree(buf_ranges);
	ImGui::MemFree(tmp_array);

	// Render into our custom data block
	RenderCustomTexData(1, &extra_rects);

	return true;
}

void ImFontAtlas::RenderCustomTexData(int pass, void* p_rects)
{
	// A work of art lies ahead! (. = white layer, X = black layer, others are blank)
	// The white texels on the top left are the ones we'll use everywhere in ImGui to render filled shapes.
	const int TEX_DATA_W = 90;
	const int TEX_DATA_H = 27;
	const char texture_data[TEX_DATA_W*TEX_DATA_H + 1] =
	{
		"..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX"
		"..-         -X.....X-   X.X   -          X.X          -X.....X          -          X.....X"
		"---         -XXX.XXX-  X...X  -         X...X         -X....X           -           X....X"
		"X           -  X.X  - X.....X -        X.....X        -X...X            -            X...X"
		"XX          -  X.X  -X.......X-       X.......X       -X..X.X           -           X.X..X"
		"X.X         -  X.X  -XXXX.XXXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X"
		"X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X   XX"
		"X...X       -  X.X  -   X.X   -    XX    X.X    XX    -      X.X        -        X.X      "
		"X....X      -  X.X  -   X.X   -   X.X    X.X    X.X   -       X.X       -       X.X       "
		"X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X        "
		"X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -         X.X   XX-XX   X.X         "
		"X.......X   -  X.X  -   X.X   -X.....................X-          X.X X.X-X.X X.X          "
		"X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X           "
		"X.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X  -            X...X-X...X            "
		"X..........X-X.....X-   X.X   -   X.X    X.X    X.X   -           X....X-X....X           "
		"X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X          "
		"X...X..X    ---------   X.X   -          X.X          -          XXXXXXX-XXXXXXX          "
		"X..X X..X   -       -XXXX.XXXX-       XXXX.XXXX       ------------------------------------"
		"X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -           "
		"XX    X..X  -       - X.....X -        X.....X        -   X.X           X.X   -           "
		"      X..X          -  X...X  -         X...X         -  X..X           X..X  -           "
		"       XX           -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X -           "
		"------------        -    X    -           X           -X.....................X-           "
		"                    ----------------------------------- X...XXXXXXXXXXXXX...X -           "
		"                                                      -  X..X           X..X  -           "
		"                                                      -   X.X           X.X   -           "
		"                                                      -    XX           XX    -           "
	};

	ImVector<stbrp_rect>& rects = *(ImVector<stbrp_rect>*)p_rects;
	if (pass == 0)
	{
		// Request rectangles
		stbrp_rect r;
		memset(&r, 0, sizeof(r));
		r.w = (TEX_DATA_W * 2) + 1;
		r.h = TEX_DATA_H + 1;
		rects.push_back(r);
	}
	else if (pass == 1)
	{
		// Render/copy pixels
		const stbrp_rect& r = rects[0];
		for (int y = 0, n = 0; y < TEX_DATA_H; y++)
			for (int x = 0; x < TEX_DATA_W; x++, n++)
			{
				const int offset0 = (int)(r.x + x) + (int)(r.y + y) * TexWidth;
				const int offset1 = offset0 + 1 + TEX_DATA_W;
				TexPixelsAlpha8[offset0] = texture_data[n] == '.' ? 0xFF : 0x00;
				TexPixelsAlpha8[offset1] = texture_data[n] == 'X' ? 0xFF : 0x00;
			}
		const ImVec2 tex_uv_scale(1.0f / TexWidth, 1.0f / TexHeight);
		TexUvWhitePixel = ImVec2((r.x + 0.5f) * tex_uv_scale.x, (r.y + 0.5f) * tex_uv_scale.y);

		// Setup mouse cursors
		const ImVec2 cursor_datas[ImGuiMouseCursor_Count_][3] =
		{
			// Pos ........ Size ......... Offset ......
			{ ImVec2(0,3),  ImVec2(12,19), ImVec2(0, 0) }, // ImGuiMouseCursor_Arrow
			{ ImVec2(13,0), ImVec2(7,16),  ImVec2(4, 8) }, // ImGuiMouseCursor_TextInput
			{ ImVec2(31,0), ImVec2(23,23), ImVec2(11,11) }, // ImGuiMouseCursor_Move
			{ ImVec2(21,0), ImVec2(9,23), ImVec2(5,11) }, // ImGuiMouseCursor_ResizeNS
			{ ImVec2(55,18),ImVec2(23, 9), ImVec2(11, 5) }, // ImGuiMouseCursor_ResizeEW
			{ ImVec2(73,0), ImVec2(17,17), ImVec2(9, 9) }, // ImGuiMouseCursor_ResizeNESW
			{ ImVec2(55,0), ImVec2(17,17), ImVec2(9, 9) }, // ImGuiMouseCursor_ResizeNWSE
		};

		for (int type = 0; type < ImGuiMouseCursor_Count_; type++)
		{
			ImGuiMouseCursorData& cursor_data = GImGui->MouseCursorData[type];
			ImVec2 pos = cursor_datas[type][0] + ImVec2((float)r.x, (float)r.y);
			const ImVec2 size = cursor_datas[type][1];
			cursor_data.Type = type;
			cursor_data.Size = size;
			cursor_data.HotOffset = cursor_datas[type][2];
			cursor_data.TexUvMin[0] = (pos)* tex_uv_scale;
			cursor_data.TexUvMax[0] = (pos + size) * tex_uv_scale;
			pos.x += TEX_DATA_W + 1;
			cursor_data.TexUvMin[1] = (pos)* tex_uv_scale;
			cursor_data.TexUvMax[1] = (pos + size) * tex_uv_scale;
		}
	}
}

// Retrieve list of range (2 int per range, values are inclusive)
const ImWchar*   ImFontAtlas::GetGlyphRangesDefault()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesKorean()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3131, 0x3163, // Korean alphabets
		0xAC00, 0xD79D, // Korean characters
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesChinese()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0xFF00, 0xFFEF, // Half-width characters
		0x4e00, 0x9FAF, // CJK Ideograms
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesJapanese()
{
	// Store the 1946 ideograms code points as successive offsets from the initial unicode codepoint 0x4E00. Each offset has an implicit +1.
	// This encoding helps us reduce the source code size.
	static const short offsets_from_0x4E00[] =
	{
		-1,0,1,3,0,0,0,0,1,0,5,1,1,0,7,4,6,10,0,1,9,9,7,1,3,19,1,10,7,1,0,1,0,5,1,0,6,4,2,6,0,0,12,6,8,0,3,5,0,1,0,9,0,0,8,1,1,3,4,5,13,0,0,8,2,17,
		4,3,1,1,9,6,0,0,0,2,1,3,2,22,1,9,11,1,13,1,3,12,0,5,9,2,0,6,12,5,3,12,4,1,2,16,1,1,4,6,5,3,0,6,13,15,5,12,8,14,0,0,6,15,3,6,0,18,8,1,6,14,1,
		5,4,12,24,3,13,12,10,24,0,0,0,1,0,1,1,2,9,10,2,2,0,0,3,3,1,0,3,8,0,3,2,4,4,1,6,11,10,14,6,15,3,4,15,1,0,0,5,2,2,0,0,1,6,5,5,6,0,3,6,5,0,0,1,0,
		11,2,2,8,4,7,0,10,0,1,2,17,19,3,0,2,5,0,6,2,4,4,6,1,1,11,2,0,3,1,2,1,2,10,7,6,3,16,0,8,24,0,0,3,1,1,3,0,1,6,0,0,0,2,0,1,5,15,0,1,0,0,2,11,19,
		1,4,19,7,6,5,1,0,0,0,0,5,1,0,1,9,0,0,5,0,2,0,1,0,3,0,11,3,0,2,0,0,0,0,0,9,3,6,4,12,0,14,0,0,29,10,8,0,14,37,13,0,31,16,19,0,8,30,1,20,8,3,48,
		21,1,0,12,0,10,44,34,42,54,11,18,82,0,2,1,2,12,1,0,6,2,17,2,12,7,0,7,17,4,2,6,24,23,8,23,39,2,16,23,1,0,5,1,2,15,14,5,6,2,11,0,8,6,2,2,2,14,
		20,4,15,3,4,11,10,10,2,5,2,1,30,2,1,0,0,22,5,5,0,3,1,5,4,1,0,0,2,2,21,1,5,1,2,16,2,1,3,4,0,8,4,0,0,5,14,11,2,16,1,13,1,7,0,22,15,3,1,22,7,14,
		22,19,11,24,18,46,10,20,64,45,3,2,0,4,5,0,1,4,25,1,0,0,2,10,0,0,0,1,0,1,2,0,0,9,1,2,0,0,0,2,5,2,1,1,5,5,8,1,1,1,5,1,4,9,1,3,0,1,0,1,1,2,0,0,
		2,0,1,8,22,8,1,0,0,0,0,4,2,1,0,9,8,5,0,9,1,30,24,2,6,4,39,0,14,5,16,6,26,179,0,2,1,1,0,0,0,5,2,9,6,0,2,5,16,7,5,1,1,0,2,4,4,7,15,13,14,0,0,
		3,0,1,0,0,0,2,1,6,4,5,1,4,9,0,3,1,8,0,0,10,5,0,43,0,2,6,8,4,0,2,0,0,9,6,0,9,3,1,6,20,14,6,1,4,0,7,2,3,0,2,0,5,0,3,1,0,3,9,7,0,3,4,0,4,9,1,6,0,
		9,0,0,2,3,10,9,28,3,6,2,4,1,2,32,4,1,18,2,0,3,1,5,30,10,0,2,2,2,0,7,9,8,11,10,11,7,2,13,7,5,10,0,3,40,2,0,1,6,12,0,4,5,1,5,11,11,21,4,8,3,7,
		8,8,33,5,23,0,0,19,8,8,2,3,0,6,1,1,1,5,1,27,4,2,5,0,3,5,6,3,1,0,3,1,12,5,3,3,2,0,7,7,2,1,0,4,0,1,1,2,0,10,10,6,2,5,9,7,5,15,15,21,6,11,5,20,
		4,3,5,5,2,5,0,2,1,0,1,7,28,0,9,0,5,12,5,5,18,30,0,12,3,3,21,16,25,32,9,3,14,11,24,5,66,9,1,2,0,5,9,1,5,1,8,0,8,3,3,0,1,15,1,4,8,1,2,7,0,7,2,
		8,3,7,5,3,7,10,2,1,0,0,2,25,0,6,4,0,10,0,4,2,4,1,12,5,38,4,0,4,1,10,5,9,4,0,14,4,2,5,18,20,21,1,3,0,5,0,7,0,3,7,1,3,1,1,8,1,0,0,0,3,2,5,2,11,
		6,0,13,1,3,9,1,12,0,16,6,2,1,0,2,1,12,6,13,11,2,0,28,1,7,8,14,13,8,13,0,2,0,5,4,8,10,2,37,42,19,6,6,7,4,14,11,18,14,80,7,6,0,4,72,12,36,27,
		7,7,0,14,17,19,164,27,0,5,10,7,3,13,6,14,0,2,2,5,3,0,6,13,0,0,10,29,0,4,0,3,13,0,3,1,6,51,1,5,28,2,0,8,0,20,2,4,0,25,2,10,13,10,0,16,4,0,1,0,
		2,1,7,0,1,8,11,0,0,1,2,7,2,23,11,6,6,4,16,2,2,2,0,22,9,3,3,5,2,0,15,16,21,2,9,20,15,15,5,3,9,1,0,0,1,7,7,5,4,2,2,2,38,24,14,0,0,15,5,6,24,14,
		5,5,11,0,21,12,0,3,8,4,11,1,8,0,11,27,7,2,4,9,21,59,0,1,39,3,60,62,3,0,12,11,0,3,30,11,0,13,88,4,15,5,28,13,1,4,48,17,17,4,28,32,46,0,16,0,
		18,11,1,8,6,38,11,2,6,11,38,2,0,45,3,11,2,7,8,4,30,14,17,2,1,1,65,18,12,16,4,2,45,123,12,56,33,1,4,3,4,7,0,0,0,3,2,0,16,4,2,4,2,0,7,4,5,2,26,
		2,25,6,11,6,1,16,2,6,17,77,15,3,35,0,1,0,5,1,0,38,16,6,3,12,3,3,3,0,9,3,1,3,5,2,9,0,18,0,25,1,3,32,1,72,46,6,2,7,1,3,14,17,0,28,1,40,13,0,20,
		15,40,6,38,24,12,43,1,1,9,0,12,6,0,6,2,4,19,3,7,1,48,0,9,5,0,5,6,9,6,10,15,2,11,19,3,9,2,0,1,10,1,27,8,1,3,6,1,14,0,26,0,27,16,3,4,9,6,2,23,
		9,10,5,25,2,1,6,1,1,48,15,9,15,14,3,4,26,60,29,13,37,21,1,6,4,0,2,11,22,23,16,16,2,2,1,3,0,5,1,6,4,0,0,4,0,0,8,3,0,2,5,0,7,1,7,3,13,2,4,10,
		3,0,2,31,0,18,3,0,12,10,4,1,0,7,5,7,0,5,4,12,2,22,10,4,2,15,2,8,9,0,23,2,197,51,3,1,1,4,13,4,3,21,4,19,3,10,5,40,0,4,1,1,10,4,1,27,34,7,21,
		2,17,2,9,6,4,2,3,0,4,2,7,8,2,5,1,15,21,3,4,4,2,2,17,22,1,5,22,4,26,7,0,32,1,11,42,15,4,1,2,5,0,19,3,1,8,6,0,10,1,9,2,13,30,8,2,24,17,19,1,4,
		4,25,13,0,10,16,11,39,18,8,5,30,82,1,6,8,18,77,11,13,20,75,11,112,78,33,3,0,0,60,17,84,9,1,1,12,30,10,49,5,32,158,178,5,5,6,3,3,1,3,1,4,7,6,
		19,31,21,0,2,9,5,6,27,4,9,8,1,76,18,12,1,4,0,3,3,6,3,12,2,8,30,16,2,25,1,5,5,4,3,0,6,10,2,3,1,0,5,1,19,3,0,8,1,5,2,6,0,0,0,19,1,2,0,5,1,2,5,
		1,3,7,0,4,12,7,3,10,22,0,9,5,1,0,2,20,1,1,3,23,30,3,9,9,1,4,191,14,3,15,6,8,50,0,1,0,0,4,0,0,1,0,2,4,2,0,2,3,0,2,0,2,2,8,7,0,1,1,1,3,3,17,11,
		91,1,9,3,2,13,4,24,15,41,3,13,3,1,20,4,125,29,30,1,0,4,12,2,21,4,5,5,19,11,0,13,11,86,2,18,0,7,1,8,8,2,2,22,1,2,6,5,2,0,1,2,8,0,2,0,5,2,1,0,
		2,10,2,0,5,9,2,1,2,0,1,0,4,0,0,10,2,5,3,0,6,1,0,1,4,4,33,3,13,17,3,18,6,4,7,1,5,78,0,4,1,13,7,1,8,1,0,35,27,15,3,0,0,0,1,11,5,41,38,15,22,6,
		14,14,2,1,11,6,20,63,5,8,27,7,11,2,2,40,58,23,50,54,56,293,8,8,1,5,1,14,0,1,12,37,89,8,8,8,2,10,6,0,0,0,4,5,2,1,0,1,1,2,7,0,3,3,0,4,6,0,3,2,
		19,3,8,0,0,0,4,4,16,0,4,1,5,1,3,0,3,4,6,2,17,10,10,31,6,4,3,6,10,126,7,3,2,2,0,9,0,0,5,20,13,0,15,0,6,0,2,5,8,64,50,3,2,12,2,9,0,0,11,8,20,
		109,2,18,23,0,0,9,61,3,0,28,41,77,27,19,17,81,5,2,14,5,83,57,252,14,154,263,14,20,8,13,6,57,39,38,
	};
	static ImWchar base_ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0xFF00, 0xFFEF, // Half-width characters
	};
	static bool full_ranges_unpacked = false;
	static ImWchar full_ranges[IM_ARRAYSIZE(base_ranges) + IM_ARRAYSIZE(offsets_from_0x4E00) * 2 + 1];
	if (!full_ranges_unpacked)
	{
		// Unpack
		int codepoint = 0x4e00;
		memcpy(full_ranges, base_ranges, sizeof(base_ranges));
		ImWchar* dst = full_ranges + IM_ARRAYSIZE(base_ranges);;
		for (int n = 0; n < IM_ARRAYSIZE(offsets_from_0x4E00); n++, dst += 2)
			dst[0] = dst[1] = (ImWchar)(codepoint += (offsets_from_0x4E00[n] + 1));
		dst[0] = 0;
		full_ranges_unpacked = true;
	}
	return &full_ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesCyrillic()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0,
	};
	return &ranges[0];
}

const ImWchar*  ImFontAtlas::GetGlyphRangesThai()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin
		0x0E00, 0x0E7F, // Thai
		0,
	};
	return &ranges[0];
}

//-----------------------------------------------------------------------------
// ImFont
//-----------------------------------------------------------------------------

ImFont::ImFont()
{
	Scale = 1.0f;
	FallbackChar = (ImWchar)'?';
	Clear();
}

ImFont::~ImFont()
{
	// Invalidate active font so that the user gets a clear crash instead of a dangling pointer.
	// If you want to delete fonts you need to do it between Render() and NewFrame().
	// FIXME-CLEANUP
	/*
	ImGuiContext& g = *GImGui;
	if (g.Font == this)
	g.Font = NULL;
	*/
	Clear();
}

void    ImFont::Clear()
{
	FontSize = 0.0f;
	DisplayOffset = ImVec2(0.0f, 1.0f);
	Glyphs.clear();
	IndexXAdvance.clear();
	IndexLookup.clear();
	FallbackGlyph = NULL;
	FallbackXAdvance = 0.0f;
	ConfigDataCount = 0;
	ConfigData = NULL;
	ContainerAtlas = NULL;
	Ascent = Descent = 0.0f;
	MetricsTotalSurface = 0;
}

void ImFont::BuildLookupTable()
{
	int max_codepoint = 0;
	for (int i = 0; i != Glyphs.Size; i++)
		max_codepoint = ImMax(max_codepoint, (int)Glyphs[i].Codepoint);

	IM_ASSERT(Glyphs.Size < 0xFFFF); // -1 is reserved
	IndexXAdvance.clear();
	IndexLookup.clear();
	GrowIndex(max_codepoint + 1);
	for (int i = 0; i < Glyphs.Size; i++)
	{
		int codepoint = (int)Glyphs[i].Codepoint;
		IndexXAdvance[codepoint] = Glyphs[i].XAdvance;
		IndexLookup[codepoint] = (unsigned short)i;
	}

	// Create a glyph to handle TAB
	// FIXME: Needs proper TAB handling but it needs to be contextualized (or we could arbitrary say that each string starts at "column 0" ?)
	if (FindGlyph((unsigned short)' '))
	{
		if (Glyphs.back().Codepoint != '\t')   // So we can call this function multiple times
			Glyphs.resize(Glyphs.Size + 1);
		ImFont::Glyph& tab_glyph = Glyphs.back();
		tab_glyph = *FindGlyph((unsigned short)' ');
		tab_glyph.Codepoint = '\t';
		tab_glyph.XAdvance *= 4;
		IndexXAdvance[(int)tab_glyph.Codepoint] = (float)tab_glyph.XAdvance;
		IndexLookup[(int)tab_glyph.Codepoint] = (unsigned short)(Glyphs.Size - 1);
	}

	FallbackGlyph = NULL;
	FallbackGlyph = FindGlyph(FallbackChar);
	FallbackXAdvance = FallbackGlyph ? FallbackGlyph->XAdvance : 0.0f;
	for (int i = 0; i < max_codepoint + 1; i++)
		if (IndexXAdvance[i] < 0.0f)
			IndexXAdvance[i] = FallbackXAdvance;
}

void ImFont::SetFallbackChar(ImWchar c)
{
	FallbackChar = c;
	BuildLookupTable();
}

void ImFont::GrowIndex(int new_size)
{
	IM_ASSERT(IndexXAdvance.Size == IndexLookup.Size);
	int old_size = IndexLookup.Size;
	if (new_size <= old_size)
		return;
	IndexXAdvance.resize(new_size);
	IndexLookup.resize(new_size);
	for (int i = old_size; i < new_size; i++)
	{
		IndexXAdvance[i] = -1.0f;
		IndexLookup[i] = (unsigned short)-1;
	}
}

void ImFont::AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst)
{
	IM_ASSERT(IndexLookup.Size > 0);    // Currently this can only be called AFTER the font has been built, aka after calling ImFontAtlas::GetTexDataAs*() function.
	int index_size = IndexLookup.Size;

	if (dst < index_size && IndexLookup.Data[dst] == (unsigned short)-1 && !overwrite_dst) // 'dst' already exists
		return;
	if (src >= index_size && dst >= index_size) // both 'dst' and 'src' don't exist -> no-op
		return;

	GrowIndex(dst + 1);
	IndexLookup[dst] = (src < index_size) ? IndexLookup.Data[src] : (unsigned short)-1;
	IndexXAdvance[dst] = (src < index_size) ? IndexXAdvance.Data[src] : 1.0f;
}

const ImFont::Glyph* ImFont::FindGlyph(unsigned short c) const
{
	if (c < IndexLookup.Size)
	{
		const unsigned short i = IndexLookup[c];
		if (i != (unsigned short)-1)
			return &Glyphs.Data[i];
	}
	return FallbackGlyph;
}

const char* ImFont::CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const
{
	// Simple word-wrapping for English, not full-featured. Please submit failing cases!
	// FIXME: Much possible improvements (don't cut things like "word !", "word!!!" but cut within "word,,,,", more sensible support for punctuations, support for Unicode punctuations, etc.)

	// For references, possible wrap point marked with ^
	//  "aaa bbb, ccc,ddd. eee   fff. ggg!"
	//      ^    ^    ^   ^   ^__    ^    ^

	// List of hardcoded separators: .,;!?'"

	// Skip extra blanks after a line returns (that includes not counting them in width computation)
	// e.g. "Hello    world" --> "Hello" "World"

	// Cut words that cannot possibly fit within one line.
	// e.g.: "The tropical fish" with ~5 characters worth of width --> "The tr" "opical" "fish"

	float line_width = 0.0f;
	float word_width = 0.0f;
	float blank_width = 0.0f;

	const char* word_end = text;
	const char* prev_word_end = NULL;
	bool inside_word = true;

	const char* s = text;
	while (s < text_end)
	{
		unsigned int c = (unsigned int)*s;
		const char* next_s;
		if (c < 0x80)
			next_s = s + 1;
		else
			next_s = s + ImTextCharFromUtf8(&c, s, text_end);
		if (c == 0)
			break;

		if (c < 32)
		{
			if (c == '\n')
			{
				line_width = word_width = blank_width = 0.0f;
				inside_word = true;
				s = next_s;
				continue;
			}
			if (c == '\r')
			{
				s = next_s;
				continue;
			}
		}

		const float char_width = ((int)c < IndexXAdvance.Size ? IndexXAdvance[(int)c] : FallbackXAdvance) * scale;
		if (ImCharIsSpace(c))
		{
			if (inside_word)
			{
				line_width += blank_width;
				blank_width = 0.0f;
				word_end = s;
			}
			blank_width += char_width;
			inside_word = false;
		}
		else
		{
			word_width += char_width;
			if (inside_word)
			{
				word_end = next_s;
			}
			else
			{
				prev_word_end = word_end;
				line_width += word_width + blank_width;
				word_width = blank_width = 0.0f;
			}

			// Allow wrapping after punctuation.
			inside_word = !(c == '.' || c == ',' || c == ';' || c == '!' || c == '?' || c == '\"');
		}

		// We ignore blank width at the end of the line (they can be skipped)
		if (line_width + word_width >= wrap_width)
		{
			// Words that cannot possibly fit within an entire line will be cut anywhere.
			if (word_width < wrap_width)
				s = prev_word_end ? prev_word_end : word_end;
			break;
		}

		s = next_s;
	}

	return s;
}

ImVec2 ImFont::CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** remaining) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // FIXME-OPT: Need to avoid this.

	const float line_height = size;
	const float scale = size / FontSize;

	ImVec2 text_size = ImVec2(0, 0);
	float line_width = 0.0f;

	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	const char* s = text_begin;
	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - line_width);
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++;    // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				if (text_size.x < line_width)
					text_size.x = line_width;
				text_size.y += line_height;
				line_width = 0.0f;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsSpace(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		const char* prev_s = s;
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				text_size.x = ImMax(text_size.x, line_width);
				text_size.y += line_height;
				line_width = 0.0f;
				continue;
			}
			if (c == '\r')
				continue;
		}

		const float char_width = ((int)c < IndexXAdvance.Size ? IndexXAdvance[(int)c] : FallbackXAdvance) * scale;
		if (line_width + char_width >= max_width)
		{
			s = prev_s;
			break;
		}

		line_width += char_width;
	}

	if (text_size.x < line_width)
		text_size.x = line_width;

	if (line_width > 0 || text_size.y == 0.0f)
		text_size.y += line_height;

	if (remaining)
		*remaining = s;

	return text_size;
}

void ImFont::RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, unsigned short c) const
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r') // Match behavior of RenderText(), those 4 codepoints are hard-coded.
		return;
	if (const Glyph* glyph = FindGlyph(c))
	{
		float scale = (size >= 0.0f) ? (size / FontSize) : 1.0f;
		pos.x = (float)(int)pos.x + DisplayOffset.x;
		pos.y = (float)(int)pos.y + DisplayOffset.y;
		ImVec2 pos_tl(pos.x + glyph->X0 * scale, pos.y + glyph->Y0 * scale);
		ImVec2 pos_br(pos.x + glyph->X1 * scale, pos.y + glyph->Y1 * scale);
		draw_list->PrimReserve(6, 4);
		draw_list->PrimRectUV(pos_tl, pos_br, ImVec2(glyph->U0, glyph->V0), ImVec2(glyph->U1, glyph->V1), col);
	}
}

void ImFont::RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width, bool cpu_fine_clip) const
{
	if (!text_end)
		text_end = text_begin + strlen(text_begin); // ImGui functions generally already provides a valid text_end, so this is merely to handle direct calls.

													// Align to be pixel perfect
	pos.x = (float)(int)pos.x + DisplayOffset.x;
	pos.y = (float)(int)pos.y + DisplayOffset.y;
	float x = pos.x;
	float y = pos.y;
	if (y > clip_rect.w)
		return;

	const float scale = size / FontSize;
	const float line_height = FontSize * scale;
	const bool word_wrap_enabled = (wrap_width > 0.0f);
	const char* word_wrap_eol = NULL;

	// Skip non-visible lines
	const char* s = text_begin;
	if (!word_wrap_enabled && y + line_height < clip_rect.y)
		while (s < text_end && *s != '\n')  // Fast-forward to next line
			s++;

	// Reserve vertices for remaining worse case (over-reserving is useful and easily amortized)
	const int vtx_count_max = (int)(text_end - s) * 4;
	const int idx_count_max = (int)(text_end - s) * 6;
	const int idx_expected_size = draw_list->IdxBuffer.Size + idx_count_max;
	draw_list->PrimReserve(idx_count_max, vtx_count_max);

	ImDrawVert* vtx_write = draw_list->_VtxWritePtr;
	ImDrawIdx* idx_write = draw_list->_IdxWritePtr;
	unsigned int vtx_current_idx = draw_list->_VtxCurrentIdx;

	while (s < text_end)
	{
		if (word_wrap_enabled)
		{
			// Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
			if (!word_wrap_eol)
			{
				word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - (x - pos.x));
				if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
					word_wrap_eol++;    // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
			}

			if (s >= word_wrap_eol)
			{
				x = pos.x;
				y += line_height;
				word_wrap_eol = NULL;

				// Wrapping skips upcoming blanks
				while (s < text_end)
				{
					const char c = *s;
					if (ImCharIsSpace(c)) { s++; }
					else if (c == '\n') { s++; break; }
					else { break; }
				}
				continue;
			}
		}

		// Decode and advance source
		unsigned int c = (unsigned int)*s;
		if (c < 0x80)
		{
			s += 1;
		}
		else
		{
			s += ImTextCharFromUtf8(&c, s, text_end);
			if (c == 0) // Malformed UTF-8?
				break;
		}

		if (c < 32)
		{
			if (c == '\n')
			{
				x = pos.x;
				y += line_height;

				if (y > clip_rect.w)
					break;
				if (!word_wrap_enabled && y + line_height < clip_rect.y)
					while (s < text_end && *s != '\n')  // Fast-forward to next line
						s++;
				continue;
			}
			if (c == '\r')
				continue;
		}

		float char_width = 0.0f;
		if (const Glyph* glyph = FindGlyph((unsigned short)c))
		{
			char_width = glyph->XAdvance * scale;

			// Arbitrarily assume that both space and tabs are empty glyphs as an optimization
			if (c != ' ' && c != '\t')
			{
				// We don't do a second finer clipping test on the Y axis as we've already skipped anything before clip_rect.y and exit once we pass clip_rect.w
				float x1 = x + glyph->X0 * scale;
				float x2 = x + glyph->X1 * scale;
				float y1 = y + glyph->Y0 * scale;
				float y2 = y + glyph->Y1 * scale;
				if (x1 <= clip_rect.z && x2 >= clip_rect.x)
				{
					// Render a character
					float u1 = glyph->U0;
					float v1 = glyph->V0;
					float u2 = glyph->U1;
					float v2 = glyph->V1;

					// CPU side clipping used to fit text in their frame when the frame is too small. Only does clipping for axis aligned quads.
					if (cpu_fine_clip)
					{
						if (x1 < clip_rect.x)
						{
							u1 = u1 + (1.0f - (x2 - clip_rect.x) / (x2 - x1)) * (u2 - u1);
							x1 = clip_rect.x;
						}
						if (y1 < clip_rect.y)
						{
							v1 = v1 + (1.0f - (y2 - clip_rect.y) / (y2 - y1)) * (v2 - v1);
							y1 = clip_rect.y;
						}
						if (x2 > clip_rect.z)
						{
							u2 = u1 + ((clip_rect.z - x1) / (x2 - x1)) * (u2 - u1);
							x2 = clip_rect.z;
						}
						if (y2 > clip_rect.w)
						{
							v2 = v1 + ((clip_rect.w - y1) / (y2 - y1)) * (v2 - v1);
							y2 = clip_rect.w;
						}
						if (y1 >= y2)
						{
							x += char_width;
							continue;
						}
					}

					// We are NOT calling PrimRectUV() here because non-inlined causes too much overhead in a debug builds. Inlined here:
					{
						idx_write[0] = (ImDrawIdx)(vtx_current_idx); idx_write[1] = (ImDrawIdx)(vtx_current_idx + 1); idx_write[2] = (ImDrawIdx)(vtx_current_idx + 2);
						idx_write[3] = (ImDrawIdx)(vtx_current_idx); idx_write[4] = (ImDrawIdx)(vtx_current_idx + 2); idx_write[5] = (ImDrawIdx)(vtx_current_idx + 3);
						vtx_write[0].pos.x = x1; vtx_write[0].pos.y = y1; vtx_write[0].col = col; vtx_write[0].uv.x = u1; vtx_write[0].uv.y = v1;
						vtx_write[1].pos.x = x2; vtx_write[1].pos.y = y1; vtx_write[1].col = col; vtx_write[1].uv.x = u2; vtx_write[1].uv.y = v1;
						vtx_write[2].pos.x = x2; vtx_write[2].pos.y = y2; vtx_write[2].col = col; vtx_write[2].uv.x = u2; vtx_write[2].uv.y = v2;
						vtx_write[3].pos.x = x1; vtx_write[3].pos.y = y2; vtx_write[3].col = col; vtx_write[3].uv.x = u1; vtx_write[3].uv.y = v2;
						vtx_write += 4;
						vtx_current_idx += 4;
						idx_write += 6;
					}
				}
			}
		}

		x += char_width;
	}

	// Give back unused vertices
	draw_list->VtxBuffer.resize((int)(vtx_write - draw_list->VtxBuffer.Data));
	draw_list->IdxBuffer.resize((int)(idx_write - draw_list->IdxBuffer.Data));
	draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 1].ElemCount -= (idx_expected_size - draw_list->IdxBuffer.Size);
	draw_list->_VtxWritePtr = vtx_write;
	draw_list->_IdxWritePtr = idx_write;
	draw_list->_VtxCurrentIdx = (unsigned int)draw_list->VtxBuffer.Size;
}

//-----------------------------------------------------------------------------
// DEFAULT FONT DATA
//-----------------------------------------------------------------------------
// Compressed with stb_compress() then converted to a C array.
// Use the program in extra_fonts/binary_to_compressed_c.cpp to create the array from a TTF file.
// Decompression from stb.h (public domain) by Sean Barrett https://github.com/nothings/stb/blob/master/stb.h
//-----------------------------------------------------------------------------

static unsigned int stb_decompress_length(unsigned char *input)
{
	return (input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11];
}

static unsigned char *stb__barrier, *stb__barrier2, *stb__barrier3, *stb__barrier4;
static unsigned char *stb__dout;
static void stb__match(unsigned char *data, unsigned int length)
{
	// INVERSE of memmove... write each byte before copying the next...
	IM_ASSERT(stb__dout + length <= stb__barrier);
	if (stb__dout + length > stb__barrier) { stb__dout += length; return; }
	if (data < stb__barrier4) { stb__dout = stb__barrier + 1; return; }
	while (length--) *stb__dout++ = *data++;
}

static void stb__lit(unsigned char *data, unsigned int length)
{
	IM_ASSERT(stb__dout + length <= stb__barrier);
	if (stb__dout + length > stb__barrier) { stb__dout += length; return; }
	if (data < stb__barrier2) { stb__dout = stb__barrier + 1; return; }
	memcpy(stb__dout, data, length);
	stb__dout += length;
}

#define stb__in2(x)   ((i[x] << 8) + i[(x)+1])
#define stb__in3(x)   ((i[x] << 16) + stb__in2((x)+1))
#define stb__in4(x)   ((i[x] << 24) + stb__in3((x)+1))

static unsigned char *stb_decompress_token(unsigned char *i)
{
	if (*i >= 0x20) { // use fewer if's for cases that expand small
		if (*i >= 0x80)       stb__match(stb__dout - i[1] - 1, i[0] - 0x80 + 1), i += 2;
		else if (*i >= 0x40)  stb__match(stb__dout - (stb__in2(0) - 0x4000 + 1), i[2] + 1), i += 3;
		else /* *i >= 0x20 */ stb__lit(i + 1, i[0] - 0x20 + 1), i += 1 + (i[0] - 0x20 + 1);
	}
	else { // more ifs for cases that expand large, since overhead is amortized
		if (*i >= 0x18)       stb__match(stb__dout - (stb__in3(0) - 0x180000 + 1), i[3] + 1), i += 4;
		else if (*i >= 0x10)  stb__match(stb__dout - (stb__in3(0) - 0x100000 + 1), stb__in2(3) + 1), i += 5;
		else if (*i >= 0x08)  stb__lit(i + 2, stb__in2(0) - 0x0800 + 1), i += 2 + (stb__in2(0) - 0x0800 + 1);
		else if (*i == 0x07)  stb__lit(i + 3, stb__in2(1) + 1), i += 3 + (stb__in2(1) + 1);
		else if (*i == 0x06)  stb__match(stb__dout - (stb__in3(1) + 1), i[4] + 1), i += 5;
		else if (*i == 0x04)  stb__match(stb__dout - (stb__in3(1) + 1), stb__in2(4) + 1), i += 6;
	}
	return i;
}

static unsigned int stb_adler32(unsigned int adler32, unsigned char *buffer, unsigned int buflen)
{
	const unsigned long ADLER_MOD = 65521;
	unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
	unsigned long blocklen, i;

	blocklen = buflen % 5552;
	while (buflen) {
		for (i = 0; i + 7 < blocklen; i += 8) {
			s1 += buffer[0], s2 += s1;
			s1 += buffer[1], s2 += s1;
			s1 += buffer[2], s2 += s1;
			s1 += buffer[3], s2 += s1;
			s1 += buffer[4], s2 += s1;
			s1 += buffer[5], s2 += s1;
			s1 += buffer[6], s2 += s1;
			s1 += buffer[7], s2 += s1;

			buffer += 8;
		}

		for (; i < blocklen; ++i)
			s1 += *buffer++, s2 += s1;

		s1 %= ADLER_MOD, s2 %= ADLER_MOD;
		buflen -= blocklen;
		blocklen = 5552;
	}
	return (unsigned int)(s2 << 16) + (unsigned int)s1;
}

static unsigned int stb_decompress(unsigned char *output, unsigned char *i, unsigned int length)
{
	unsigned int olen;
	if (stb__in4(0) != 0x57bC0000) return 0;
	if (stb__in4(4) != 0)          return 0; // error! stream is > 4GB
	olen = stb_decompress_length(i);
	stb__barrier2 = i;
	stb__barrier3 = i + length;
	stb__barrier = output + olen;
	stb__barrier4 = output;
	i += 16;

	stb__dout = output;
	for (;;) {
		unsigned char *old_i = i;
		i = stb_decompress_token(i);
		if (i == old_i) {
			if (*i == 0x05 && i[1] == 0xfa) {
				IM_ASSERT(stb__dout == output + olen);
				if (stb__dout != output + olen) return 0;
				if (stb_adler32(1, output, olen) != (unsigned int)stb__in4(2))
					return 0;
				return olen;
			}
			else {
				IM_ASSERT(0); /* NOTREACHED */
				return 0;
			}
		}
		IM_ASSERT(stb__dout <= output + olen);
		if (stb__dout > output + olen)
			return 0;
	}
}

//-----------------------------------------------------------------------------
// ProggyClean.ttf
// Copyright (c) 2004, 2005 Tristan Grimmer
// MIT license (see License.txt in http://www.upperbounds.net/download/ProggyClean.ttf.zip)
// Download and more information at http://upperbounds.net
//-----------------------------------------------------------------------------
// File: 'ProggyClean.ttf' (41208 bytes)
// Exported using binary_to_compressed_c.cpp
//-----------------------------------------------------------------------------
// File: 'roboto-regular.ttf' (158604 bytes)
// Exported using binary_to_compressed_c.cpp
static const char Quantum_compressed_data_base85[24580 + 1] =
"7])#######u_P+>'/###xG8+>'wPP&Ql#v#2mLT9BF5Z..E&##&P(##[r0h<Wu&*3-W'##k+(##*cpe=#(Wamsj%##D.$##TuA0FQLvcuJM&##-7)##;UBUCbF0lJujSk+02q-$f'TqL"
"iu^M^3nJ_&i0s-$I3n0FP'MfR02(##)no92-d[UCvhQA+LH*##Klk--/hY=B<+S(jwiYW-nJ0I$w:]=BsBIpuBkAkFv`q92Y>BiFo[sI_]tn929Mo&#D),##B-i'#gK`,'$ie<6uR:v#"
"oZ@U.40(6-oYn20Zn*2'9vHVd3*XKlw1FcMJF-##js`8v.tfN-[F4v-t%JNM=b@fM&Ru9#tj%##d/B01%&>Y#dBP##=T_n#`)m<-^a>W-b?$RN%Zdw'Q.R2LxPWjLr/BnL%PG8.sd8f="
"6Up>-F?ARE>g:Jr6IC#$x[k&#`$5MpLX^?-%)###H?TM'Xv+F%T)YD4:b__&:GQ-HmjZR*Pi68%Ebj_&i;SY,Lwj_&XO/2'k&l_&[efi'xMl_&8l4R*Q&m_&$i`i0>Mm_&Y@35&j$o_&"
"787`&'8f+MmM?##_RFgL2pP.#sU__&R+35&5.j_&WRJM'?Lj_&1K.;6Mwj_&fp;A+4,m_&kASY,N%n_&@F(S*OBGY>#B`R*dECG)n(i_&787`&&/JfLa$>T8DX=gG&>.FHMeZ<0,Beh2"
"Qp'$Jk=Z^Ip@UeGT7Xs1^DxkEubgD49rCVC:1k(Il;Je<'0oUCc:@bH;<[rLu2([-nh,7*V'ZR*OR[q;F%@_>->hoDQ9eJ28*7L2#q`k+%uwt1)<I@-,YD5B6J/>BgTV=B;kl`F1g>5O"
"=/DP8XhdxFeBEYGIYo+DUw%;HlBel/Zl,20Z8#-3/pYc26rd'&I1He-b<Sc;R0=SI#6sc<h15^GWF1DE_p*j1nkAs7i-7L#1#,`8NMWq)sc8JCN6YMCQP'vH7Lb2CL,P`<V#3)F%HSD="
"2IK/DPui34:Zv9)6tvL>h+>XC@9DX1G*w=P%$4GNg.-D-$'5?-8ND6M*B]qLla4rLGP6LMm3CkL>h_&Oh&3E-'.FCM<hipLn-lrLD*B-#t1'C-/e&V-*(wT-3IKC-g:Ir7ABDs)q3n0#"
"$k/.$TH]881WR&,^>l'&,uX&#s9Lk+Z_b_/WJP7*FA+e=-(W(Bsu`:BGpD=8vJK+4Wu1D5pZG89&;w=AMvUv79@n8%I3TQ&Y&;k'jow-)%l#c*3UD`+?r+WB2r;A,kiP>-XM6W.i@sp/"
"#4Y313'@L2M/XI3B7lSCQC4wUHOnZ`39H:b61e_eP`FPdJrpIfk9j,g*jhBid(suLp,i2#]Vn7RPL6)Jc-AVM#&V*N'&>FH#RQC&C/QlSlc<-HZsi6:*]%##:Y;J?`]jLDtvesV]$H'^"
"H8>&_Q&$<a#Yn7Dre^o/BB(##`N(Z#38fT%lkHS7>N$)*7c3>5f@.>>T0x7ICPDcV(aNo[;oc._SZp=cv'?fhpcFuu=-PJ(p/cc2h:V]=7T)2Bm_auc43J`j<b`D+Ns9v-#j,p8'eV,*"
"EOCj(-OnMCZ?:_AK?Yc2K0DP84d7JCxhn-?'t,.?<h5Yc#=vFiw:L;$M2e`*B_lo7'Okr?S3FSIsSq-?=L)d*GE-/?.,n-?J,###kCq-$.,q-$wX4ipRS<jh&`]4f2kj'&xoqEIxIkxu"
"v=#HMMK2rZZ=`b%Qs8rG_DR(;eAB+L;43o6w5Uq)kNlQWe<x:HQCniLfr02UvOX&#Q]ce$j1hiU.aMW[ami@t';cY#(:eM07F<5&?wSM'l_JfL2a:1.4tZiL0VgV-r=@['TYYi9#1fu>"
"vgYxX#8Yf:rR2A=*rQ`<`Yp(<[aS-HF.S)#YuJ*#,uu+#qi8*#sPj)#'`R%#Se[%#Xqn%#+%),#7tI-#N_W1#]'+&#+Ja)#>Q?(#]H`,#,CV,#p9K2#,Tq/#b9v3#hE24#vPo5#6^+6#"
"$RD4#dOC7#JD17#F8u6#p^V4#Xoq7#Tc_7#PVL7#PaX.#iIe8#e=R8#a1@8#4iT%ML6B?fr_BigsUb1gi[);H+UvFi'=?fhK8@]Xq6ASI_at4Jam9PJd&UlJf2q1KiA6MKkMQiKnc2JL"
"D:TuY.m3S[s5#8Is/^rH)QRrZlCB]Ot(4VZ*Su+;*G>J:*^NcD8tv:Q3/J&#KWp?dJ,?PJ1G/2BU$XfUfRwu>w;Ad<RX@MTreH3U[b(]tf:Aip0Y;JUon8W7V)XJ:S'W`b%$$ZZ-l28I"
"(3QV[d<0,NTI.qJ>kql8>Q[o[;0hfLR=DPSa(*2K;n,>Y;$duYKL6##_;?/(nULi^(h`S.%Fg9;i@r$#xwn%#9;':#:896vw]l)M`r*'M<x3'Mtht;.*;NY5$(O;7b.*Z6(D8R*<n]f1"
"im<kFV`JV6vU;5&TRb9MK,ju5fHZY,>',/()2)J3$=QV-8t6;-ls-87D._i9o'28.<5H_&glFP8Y@Jk4/]fc)<^Z9M@`72'a-oEIi)Y-HG5wE@PnEM0bP(,2wX[`3ie$,;XVZ-?(oOY5"
"HNFJ1lIg9Da<w^]8Jq-$a#>.$]>EG)'S+87ZC18.7mBJ1D-JM0]#+##$&,##5%:kO5+%##^I?G;HV$,2+K1R3iD'F.4UfQaR0U]4B-;>,&IJ_&V0JP/b[;8%2^1R3UJJ9rR:$2937[w0"
"?2EG)iwa;2s#2;6pKT]4N@)20fxZ`3s-Ns-VkHiL-a(:#G1Z7vtG<jLgm6+#:q9'#*LqhLm+G9#sQj-$5Xv;#aqUxL)gipL[%5$MX0moL*MDpLp(j7#HlkgL?Xj7#e292#P185#K+/5#"
"oUq/#*L<1#f7i$#qib.#@SK:#-:Q;#oDK-Qv8h'#%`Pd0Ic#7v@$Q3#K>eqL2g3,#A092#.^H(#n]u##c.krL'W)xL@Nh*#vDG##LrpV-k^q^f'://$a^li'o>q%4S/p(<SV[Ee[7GS7"
"8w*_SM(il/@O;w^CTVkX4OpE@1IZY,U&Kk195ec)hFRM'@AZ7ng&UiqiX8s7[dBH%Sv'kk`nTw0OUo5#ioP8.N,$_#?U6(#]VS=#X,j<#X-^*#.Bk]#.d4-QjMG&#GN5/$)9CdOq*D8."
"=cYL#I>uu#vC58.ac$)3EwcJ$./Wt(ceD>#K4XlAvEn(<-%hWh8TKe$WbO4oJ5<A+cKKJ(-W?rdO7oA,nXQe$tiP+`AoN#-E5Pe$sZHuYN?*j1o[jV7ZR/e*j;nLgiWAJ1/IRe$n'tD+"
"49.L,'#9>,Ll`D+J1ui_23.L,G.Re$UOwXla7jV7X_X>-tssrnP+v?0_tRe$8-SKuV(E_&onx%4e)PP&#Mac)^(Qe$bsZ9M@XM-Q6uI_&10`-6h[E_&hl>w^Q(35&P*Gk4nuI=BddUS%"
"h1;$gE)>>#M5/B#?Qw7M17GcMQDVi1%####2l:$#%AD,#&[^sL+Ka/3rvK'#LuJ*#/tI-#hrH0#3nRfLcY%iLO<7I-]jh9M.)aJlULdY#oj>93Hww%#P+^*#v'9M#N`d_#<T6+8R.)da"
"$dY%b6u:Db7(V`b81r%c9:7Ac'.$$$lkxFMYcp-$//q-$=,FS7fn@SIB5#sIbMooScV45Td`OPTeiklTfr02Ug%LMUtpQn9XX*]bQiP+`2J?iT&MD_&C,-F%D/-F%Adk-$Bgk-$Cjk-$"
"Dmk-$Epk-$Fsk-$dse--LG-F%MJ-F%NM-F%uZHuYiMwE7M2l-$O8l-$P;l-$gK6R*^%.F%[]l-$^cl-$k'^w'pCm-$qFm-$x[m-$%fm-$&im-$-(n-$R@h--7Fn-$/N,R<Ed_w';Rn-$"
"Hm_w'=S[-?IWG_&Bhn-$_go-$bpo-$cso-$dvo-$e#p-$f&p-$g)p-$oAp-$qGp-$OCs92>u2F%;Sq-$<Vq-$=Yq-$90Gk=?`q-$@cq-$Afq-$RN$:)G:3F%Doq-$Erq-$Fuq-$Gxq-$"
"`KAkFI(r-$J+r-$K.r-$L1r-$M4r-$-5pu,lsVV-GbL50It-m0SaWN1=NMS7]rK]FH5tYHHD>WA@</#M_4%&Mh:.&M@@7&MAF@&MCRR&MDX[&ME_e&MFen&MGkw&M,qugLoE?)MGkn;#"
"6Ov;#I5T;-86T;->7T;-?7T;-@7T;-A7T;-C7T;-D7T;-E7T;-F7T;-K[lS.T$=xuA@eA-Q@eA-Q@eA-Q@eA-aLm-.`Dt$MIS(%M6Y1%M7`:%M8fC%M9lL%MkUo4vk1-&M@@7&MAF@&M"
"CRR&MDX[&ME_e&MFen&MGkw&M%F5gLZE?)M)G41+5r5S[TP+/`2nv_#0d=;$Fa9SI_7_Y#+;###n3+@'(Jkxu0C#s-YdS(M8O-##4Mc##q=;mLqC73#WqG3#['Z3#m*,##I,2i1A4i$#"
"P_R%#p,_'#mCDmLfw2$#qcLw-h%F$M4/gfLNd7iLmZg5#&Cg;-?B;=-1LM=-c9F7/[ww%#qjQiLKRQ##;)B;-w;D].HAP##AMYS.IEX&#Px(t-M^jjL+4M'#Rx(t-Qj&kLR%1kLmSQ##"
"S.RM0X8q'#XGY##_>gkL)oR(#u^Xv-ruclL8OO)#^Ag;-JvGd.waY+#1l@u-X*uoLQ`j,#*TGs-om-qLe'm.#/],%.1aErLn92/#?TGs-;)trLHai/#:d;..&@AvLp[^vL=C6##o<#s-"
"RU:xLKRQ##w*B;-YXW;O+iM7#S1r1.6%q%M?MS8#>,d%.CCH&Mvk+9#Q$)t-T0W'MRK(P/*2>>#,<B*<_NEX(]eVdsa''%4^bKr&ScD`#NIG`sO$1c)'Qs'jGZM#,onP$,TArHV?Wgp("
"A1H>#P/@-)XI+31sP@Q:1r+WBI)xVLY-$f[_;DwtLXvlEkMf:913j=B-2vLFd*Q<B+)YVC(F$=(NA7nMHqkRMM9CSM1ar;CwKvsB$]eFHQ/m<-,Oo>-mrP<-Ajq@-vC2=-(A2=-vGg;-"
";Mu`N_wcUC65mHG,v:.G)8ZhF2''o1pg`9C18,-GoKd<BIZ<SM@d/iFNcNj0i2bnDHvA+4uh$c4wj`f<eim5Jh%$1Fo9gi#`;iu53@(AOx?;cij[</(<FPS7tk7>>1*ho@HcXcD@.^uY"
"?CIc`Y#ZucoIk1g:dt=l<hA2'UiJ>,frGD<.'65Afc[cM?'RYP)u.Abxwp.h;#$;mggd(s)`?s$eeL8.0mYG2D:kY5ffpc;.q^S@]*aYGulmiKNf),V3>gl]O<9Abx-ZfhIr%5ocN6Gr"
"u`fxt3.wS%GEP/(XYE&+p6rS.65D)3UT.m8uU;&=B2A/C]t2#GrJ_PJ4=1&OVMYPSpB,&X5895]KbIG`^#?>crXKMg>vTYlULflorDs%t0iq;$AqAm&c@,Z,)?T/1>`I&4TKrP8mugG;"
"6?Q5AWR?&Fm#P8I+GaJLB*R>PVGG5S-%o9dhV>+Du<nDs-f$ZV?A#.:(iQ5SPVVP,K+Un5+Padt3iW8=YYrw$mfnJQLHu]tY6/^tNKUQ&@a.^twLg;m-3YATVV`FsV`AOPqr.GsIZl`M"
"%fsI+KW:p1)%RU1N+;csk*D#VtaIA>J;^],(x+dMX;RfQe=qP]2vwl,iOpG-AXXhUmuBWQrlWtE7:=GNkY[bREbF,Vnvh0-9f7gL#2i--dc#Z%u9(?&<YdhP([#@K]im4BBuD^J]mIs]"
"9'4,R;5j?#Xw#7R3Vi8&Iw[qHUG9asdrALUT<8cs#PGDiSpq(X$oM%ux#Tw6X=R(txi9>&if5e42Rq?%Q9HDB]f[S&.bFr)`6q;&rf8>&Xs]5Sm9c&X-&qHq.u/Q&s)@mA>c(>QYf5#%"
"(&b@&eQEP'S2JR7d7k87Mst[3T@s=csf89&Apxx,wp]uQ<w7Yet*hS&-`[Z,v+08N)uJm%hIF%*[/aAO<DX+IY3@SswUL&TaK5R+>%hC,VY7I,i[^J%PqNRNL6^OOiaMFVTimF,I9.dD"
"&/@Q&`4BOE2S*)u=2(;&;7_293WvA4dl48Nc$eS&TZUC,M9:F@Ab+6BcX`mG&HxxL,T)<%[kKpnWPmMN/.0XOeF4>%Q=Y'2OKN&tv-x6I*I9>&:H>p2^<<T@_qUdMl?d_&?]UQ&MMY53"
"1JZ7I(,VQ&Xu-[Bv+>#CWaUrt3#DC_a:0GsTs]IAZE15B:U&?AFi[4&.04**kptA4=DXM2+NkB,f*$Fs.,Ur$iYRJQ$FC;&lZW'/310r)?r$XLNj#v7^bg*:Vp=s18WUZ5m=pGDp*jfQ"
"IaF,M2]58N`pBj%9d/$Lbp*i+ho.Z5i$,&-Wi/=Z95xl,6ht`WPwWJP=QE@XiMERNXW4o7kT@<Z=70^t]6(;&JMp`j+q-<&a)HYHQcQD,OlgQj6ZbQj);G<&Fa$:&:RY;Zd/@ajje*t$"
"?]eW$ObL3WL52ZP@XXS&u(08$NCE@4&:C$%^:=%=f=A/Lo&@aI0t=C&x@;1lj4?LoRUk87dVZZ$Db*a&ow6W&f@Zft6eB5Qce)Gs,]1`tdw7Zl;E.8$FvQ]>e[$U1Q<SO9+ZiI1fR&j$"
";O2@&F=&1XjAfS&ctdS&)l55O<$_`O?F(2t>7rd)=.t=AFdC`tV0nr7xTD^4T#gIAX;cS&^Od9Mu'gcR^/sZ>ET/(*<@;'k;=l)Ni7L#uRqDd$i&DZY*pS&t3gox$E^rt,MVE,EvY@Q-"
"CU,<-I=@Q/I/Jx$Z+32p%>f)<a*XQ&Qf,vnB'.<&i'I)EXj2D^JQn<&rMsGDd=vER/WT_Ie@k$OwQf/1IL<^kf1]wkX#`lKFsrUk,$Xtl_LWQ&eujS&/J8;&l4CmLk#x+OHO]JGpiE9%"
"QcvJb^#6Q&hcjP&#lC_tuknFsj&WQ&xd.JGJ9GWQIXF/-D8+sQ83U#uaNYS&@@`tL+O#7I?rf?j(wPA62P^B]cLU.o=fO2tWpFWQ+M+t$QqNVM-/EfOS8i=I<'FOk:f5i&<xL=IF[GDi"
"eVqS&#.Pi&7?G7I[WI.-4SRN'igU0-x?#^XU6nDE]B5]LnbZMPO,h2%ae9F&;Yg&XJEfS&r7W^6VF25FHRtE&A=cls+4/9RSkZS&d*EP'X$eS&VYEPsqX_#miK*t$Q_[>Lei[@Zoh7+-"
"VbDJQY*nS&COwrm;t*,Rg_vW_[;nGMM*KSN2]ja&IO+/-@)J[OR>;PGfuEJDeRo[s(1QR7pQ*t$<P+pVfUGQ&T&4IURKhK,G_,<ZMgWQ&(CfU-%^cGOTUDFRJU?S&/d*wpagAajYU&a&"
"`L@Q&Zb8a&W^aL#W*,##mWt&#qd0'#upB'##'U'#'3h'#+?$(#/K6(#3WH(#7dZ(#<vv(#>&*)#C2<)#Sc/*#XuJ*#^+^*#b7p*#fC,+#jO>+#n[P+#rhc+#vtu+#$+2,#(7D,#.I`,#"
"H@%%#LL7%#PXI%#Te[%#N4i$#moA*#iKb&#?rC$#_qn%#A/5##YH4.#>Tl##(mk.#-c`4#8Yu##05>##)>N)#8Dc>#`Ur,#3Oi,#H8E)#`'+&#5f1$#iGY##Na.-#8rH0#eAU/#@r&M#"
")_<T#>%'2#HIpM#FLg2#H:TM#GFgM#Ao&M#MX,N#F%9M#H(02#JkGN#WwYN#[-mN#Z@*1#uf60#)YN1#Th7-#$0vN#cNMO#Zk>3#76m3#,G31#(-85#+Kf5#+E]5#3Xfp=Rn0H2fji4#"
"V-d3#g<v3#LRq/#V+78#</?;#s%.8#@&Y6#<pF6#GJ:7#F>(7#KD17#OPE'%+us7#f=R8#f7I8#cC[8##%X9##1k9#qb39#qnE9#,OB:#0UK:#+=':#?$-;#9hg:#9t#;#V4>>#OkUNt"
"cb/2'3UZi9=;C$TK=b8#r7G>#-4wK#r$Gu#9:.[#L'R4$rkZ,$gv@1$JYm?$BBRW$YIc^$`D4i$s[=6%W9,+%]=oP%m#=A%L3VG%e[Om%w46_%E0n4&waUv%QWI)&2X/I&hQJA&?RxT&"
"<KY+'-e2D'GtpB'Z?Yb'<=LR'W7t]'[A.d'Dgcj'81Cn'i5Kq'Ur%t'0&bx'eMG/(QY57($O_V(G@DS(]lo*)s5l#)[3h/)ZWRH)+v?w)kq6w)Wx<**sGP/*Rw-`*7icR*Sa=#+D6sd*"
"El(4+a]tQ++NSE+8pBn+JfUc+lB`8,?]S.,VXSI,wLWt,xDmc,mjMd,gxfm,CeIp,tBn%-,j++-8G6S-,>Zg-43m_-AXc7.Fp%&.6(>/.SAHO.Vn-D.<r4J.A4>n.//Zc.k:ox.?i97/"
"VOUc/i8[d/dG)-0Gu>,0W2X20`]t:0DOa=0PWEE0qqOf0gO?W0Kiid0cx*q0$eOF1[RS21[[d81lp/B1g7ZK1@^nP1uUdS1':hZ12Ufi1ZtDp1&l9v1e+]&2/(OQ'I4'hLv]0uG7X@@&"
".lp8$6DFj)CC0[k2P[&M,A9ZdBCE4o@sD**)>fDNW?q6T$pbKJRSEt?O$g%*l]q3]`6TN'x)sQMR#;OJ7.ugLjO0Xl=>p:dg96K1pi)0:P?M_;[&ivs>fvD,09KsHt4YWLrXr+5Iv#:5"
"ljeP%hX7Ll5Fk[sBLq63M:dU$%ZTkJqas-CWrT<bp;SnRlvLFV`bq;&U/+f:TAemDW>B.C2h0T%'%V4%3'*D&<;FQ%4n36f(0Q.oYar8$>,cA&@nqwtF$M=&gR7njTvc?KdLGwtdF*G,"
"c9Th5&qu*rpXf0oc1T=6PSl`ObkT9lAsrOsb+tD)n#3FscG>DiQbLcsPI][8wGBnfSMu+%'L%e,k9[mL;QXQ'ePq;d+g0MoF=uQsB.mqX*0/W+>kK>%+&5F&Mpi<&XW=sHvC(tLZiZt5"
"KHY7I3%`)b>H'dR^`9e?lee`th[KhPK4A5%>5N'sN'g1X%<Q,21:S'jDFlneL7X'['=Uwk(G;T7s=m/1AlIs,O0PqV7TiEI$j%#tZ]2Ds-8]q)S^CC&TUEF,MNVDsVh5Z$Q^K8NWVQ3%"
"now+R/<TeC?:qxt%A#n%oI:L,ph9wK%D7.-]Y;o@W>mn@n2mwKawDP'*I(2tYdJ:&l0JA#0=%i'1tD?YT<Jne)oiNl62WHsTgM`s@g0^t16j@uhDXi%3+0WH$F3gYV7m(%iWYQ%Q=Gb1"
"j;eXY-b.^t*b'lO0iMMLD*l/-1W=pRU'Yj,rmOF,;95N'Osmrhx^CL9?Ph()5>2-)PgG/t)Q?\?&qxVAX2TBhP[[46guk5o$$wr-f`.$bY<*?9uKTmKFE>qh,()^,))`@:MBos49x4Sh]"
",`.f182q8.Wcj1_d%lM1;wQd2T^2Ds^h^(*RDq<M?Ml.%-AFDs8F:wEap7m+<NB%41$7/h,KG3m#F_JquCI_,M`9Ui<a6gUX]6tLep5lO*_d.-x7q5ARSKM1QhnktEuIi,RTA@&g,rxs"
"$p:AbT7DC&#oA:%DoT/oA@CvYJ^5%SJP#FsfaCmo5>TSX0K=kor[1^t:/p<7iEB`t'@7csLkjX$Z/KJ2a.tnDPPi7%3t#pMU8sGsANXYY26iJsJL(ejK+^lXTxYC%%]K=Yh25B&%m%#t"
"InTP'1uK=MAu@_WDXiS%>)D+tY_g>u;06tLA><`tD^nD&,#F=&_J$8%@m6^S()VCEHoReYtRAbiIG:dMb20khicCcscjm7X8]f(tg&7N'k:oDs(Aje)%UU$tr`I:M3-Oc3c>#Nu[K'LP"
"?r7m+3,?>U:C.Gs1a;d$gQ2UMp/ubD,[+N'76GPskHX*r):RR7j127So.=,RE$[gs&u/x$6.IUMF>3i0sA)gL$d+WL+WM/L]D$TNb-JHsGboM`<nch2d@j)uxn$'S1J64+'>P<LR>/c2"
"Mn=:ng`s+R4i((*XlgSR%+6ES5J6pRKqkHQIbHa3L0_GM`5r*R'3f]tW7S_MQUI#L]J>0L5-Ae_0bg0g'D6G&^VX_j[TuwK?,w_t;h9wK+sH&/ce(o$G>nQj*6Hx$_+o@+&m@pWp@&S]"
"ujVXc.IlDsNqT5]XdsFSa6xds%GAx$,8C@&l.Q7t.*P7ItGD,M(&^ZK[%&G,3S8;&G5o`sPq2l$vRp%TA2hx;$t+*95LCICQ<pF,K@Q68I9J[sGEWuc5C0[k^P%S%cZ8iBeA7BKY?j*M"
"+i?A&dDt`j=Ut`,KjK(*08q4E.(l#%P8RfQ<1tI%B,(XVWh]DsXuWP'OpYE&S.tx5f$,&-o2;Z55>vq,)8;F,(:WV.'B4T@6?clsn3248j_=ol_a7htxVx:)i,v/ttpB>&HU:O%vi610"
";dh,)#g550X,--L3.[6NKj1(=,Rg,)c1GlgMI2n8LTd9mLxG=N`-&r.DB8EEr6Z8DSXk*M[3>f%1pxM%Q1)*Jqao*%0j((6Y(QC%KAlZnK7<t$`s=[UKKY7.P[Lns3va(TDo&Gsm-4`t"
"Xm2`t'HPWK7J/GsHF'e;ZtE+4UH4GIs8v[s^H3;df`(;&Vk^DN+BcC-q.$.qdklDsa4C#=2l9`ti%h>uVsl#uIF(2tDH-I,(,S87N1(;&QaN%uG'FOkf$A))]Zgh3fo%]EqC4CXB>e,)"
"R,aCB1lm8%8fODsmO(^Q5M..-bDo]t.pV<%,*c'6E6-cC6V*48Po<.)F5flLWb6Mj7:IJV(4/0kC`'K#+5[eCZxF:$`:;L_EhoTb[F''>Ppc;%/2h4ERUWt$*V:XLwaekA@3qOJ2cII,"
"ll`AX8=Et$lc3a$PWTSNdOs4%;']qHLvm@+SKtiLwo&$$_F&+Mpk=*e-c+;&=0.M,1)tM,XZWO,EL0J,@YO=&+#^;Q`J7JQQ-hQTesc;%xZd[+/FR'SLJ%GsN=jE,=Ok`,8OvM,=-p^F"
"K3e4?LnO`MvuYd;)Q<>N<,/PsknH[FnfV9^PV8+MHC8?Knm[4Avp<wTu+&QJ0REgYCods$rg,rkDY^(8<WIa+,$x?X%d`X7O0v_K_FR@Fx<qXSDXSC&4jY[.V;]Ljs:jU/T6&$UtNmeU"
"U1O)tKNNBKoY>_A3Qc9BdF/A*sfi/ZWA;T%LrZLG`SKlNHHpu$kpT?&Q-,UVQ*RFk'A08$ic.J,Nd2BJcEw3>3NLh$95hs$>0tWVC8ge(./Glg<<5N'%fI?#ik8JhtB)FsqkK;QKk37N"
"axT)E=tre,H4=I,ln#K%h9#nlu#:jTG3KgP1U0Dho%0SN[eE%YeR/$U,xg-UBkBQg]R=Z5(O,&-Agcn%eiupN<^5.UH3A[sR`c<dOGbtGk:bwO2$b'av#UO1pc^Us63$Un9-e;%&xA<L"
"#>7.-N#W<&Ij6Z55>vq,5Gx,hnI@L,0([9.m?Tj9sLrCsgq%+NZ#MIQ4)Y;Qa2DMP?qPjs;Z]x$=O37N<0^:-2je:-SER;QI*'8NsOGDs[UJe$nKr^OR2`=IUQWO,3m2J,i8BZ5;HGr-"
"iix=&+*)dMA[F/-X26G,jh/jKR<^8NY*Bu$QrMLZHe8Yeb5CcsIE85Y>`Jcsj57N'=RViLOG:52th+:&]q@`VMkH'lfL(.:.>R$lCX[B&c_o)G;mhDh2=c87$o;7I,U=9[dPd'jUoW0n"
"/7q8$i,Y_3E'XcRYA%GsNM(g$YGm6X)j)O%ETm_16&6&MGg:JsLLh/[MvC88cshtLIP<`tI;Pf$<5G;CxrQ10m=hwOSt4c2rs_KC$v3IUZEejk*j;ZmD4umsTA7j8a;mZ%10'*G*@'/%"
"ZM1>Buu@=%,+8`t$ddGMCF=j,1C;sQZv1^t=8kmDc2;`tvTLS8ri-pnx6K9-hS)aW?h3/Pk`VYU]flf%n/d-I#bgwsG1)II.qpXm0?G[b:;1:R1Y`h,IwF+%R$XVMd^CtO9xIi,R4^hp"
"ZV[GM*5GWL[opDESHml,ZZ%S.KkvGiL7jHgJm?rS+iZbRld2G%a>iiP+)]j0Q.+q$`kK@OR:LlOH).RlU.BV#+w-I_/a^kJIg@:7+rb>%l'cb`qrb$OOM[JDo=^t.%431^joiJsXTY`i"
"Vek84,tU672D9`t=[MqM_V.GsSenP%bki6<40UOlnwBV#U0(Ih.72.1+)>_t18+?Ks%r--^k(G%OrK2^S1um,`x9sQwAKY%4gQI_,ea#7R2a:6#W[B;`rMU6a*b,g7WGF)$Rn#eBoxst"
"8YI<&T_MC,Lg6J,VqNF,CQ5N'7G(2tDhj+`YB%Fs4kMJQ+]R.-VBr7.Kh;sQcspDs8qO^$*,uPWJ(fC<E1TN'?ka[swhM_N_bp1n<UU8$.1`kSS`.pn1rI_,Fi$K1F&e63kZ'2Wfu'f,"
"u#EAApMN<%A,hmL<qa$%I+h/oL)H)ack:eY?Kw:W]=5%uZE'4^wK*hc^4D2^bc:*-Ok.^tHd2]lVCK:uR.vwLm6U2Bf9:3-s.6D,Egw^][9J8%W4[Lle(j[s'qo4fg9DNn<YxPsYbs-C"
"Fm9HR:sxuHd%l]t_UBh5K<.dM4HHnen5`^iar;:6wBe>eh#v@67p_T9)nlF)vGR^;cbMJs-m:;&4pU*@T`S@%,+8`tP;TP'2$0xsZ:w:doT%kn;U.)tMeV:63^_5:ms#Y>-VGt=)-c#6"
"gK0hfq'2H<a>nr6/D2&.cWY1M<$[#%]EB4Oss.(WEH7#P7Y;P+d9QDsRqBj%ab.^to9HtL6Sr--PD^kSq+9oNbDmI:O,Ex+g0o$OcA'OfR.2:RfS./QXIWDsH8Tx$BhaRNM')bt=?44O"
"-;)l+N*JRN('AX(]`HU?t(bRN3?k(4$mo]tFgCeQ1DH4+<@[qM36)S%@eECk-:ViPGn[rn__1vP]5`.Q*Z=vPJ4SC5+F9r?#u_.Q6Y'`k#NNDs@<0sM6G;5+lp*_?DGq_aB`v-JF[@->"
"iki_9Yr[d<9M=FD$R:<dpj^qQdvsKl&j`]sX^2DsgN?hgoAr^imrJP%cdLS>3YHISw3?U+Ee1^tpS&*%6SZlEV`Wt?O+)GstE_F&TPT8RFl=Qs:LK>&HNN[t?Y-7ST$Yj,w&PF,Nk.^t"
"AE))%#*S_Ojb5inW#uD,CBhs?bdSkf<5IR7sUJ[m8DflsL(]UL0(dL+`8$G,ucPv$$YT)SaZbk8;uQ+S;#WS+o^'pnp:R_,?Lt)G5-60%ZDuXBK_pJL1+3nNUPF.u_J5[jF01F@is6#%"
"ucm#upU^]sN%Of_ll,27w<`S$AiXU%iQ<xHL#.CN[n(Ab$jYYsfpqK,/X+r)@^b]t#V@xamr%G3?-Vbrb_/o.]o.0o?wpq60vVneA2R(uLQd#PJS&.MBkX/-vm`8R2>%.-Y)7N'Nv;_s"
"mTsUk#-57.chSN'Z>wBslNjUko;2DsT-Jq)%T8+McdSZ0<Q<CNo/^@&Ar(2Mo'QJ,ffnClV=2_9_7e=>hx.gsoc*rL(1q801f+V#'ttKp8L%%kj+/KsCcQN'I)6?&Z;=RRWLGBrHTQO&"
"Laft>HVVtm?I:@.^X]f;]Y$G,s)r4%_UPG0'-'<6V/%2tasCtdq[/77p`0=GNkitQgr<GRaVg/:q..H%H,mN%FBc#PGHdCD,cFf[84tI%*L$J[2^Q^t;'gV/5s(Q1W7kA`hhX<[x@-rC"
"<@tI%xJ=7D=c)f3=F[qMa@;?%U:]nRglC?%Q,r*RrSgY%Q/X$tBF.>I-5qqc^H47.9`UP'v&r*DW(8U#5V<u),hDL%i`*GRphib`hMNRNVwoSsSgGb%4pUJ;uS@#Q#3%&MDasT'Z2>B&"
"n.w#5*>l>uAZOdMb=W4%FWORIpP%uLc*EP'(B4asFurCk(ku'<@Gfgk@Y'K#C*'=cB;2:?B?-gLQ)2^t>dh$'XIlrJ[,101bv-UMw4qoJgZA=#8HD.C4wcGM:X&OO-rv2Mgo3gtXCD4%"
"JcYF&-<)dM6a',Rbf`4%o+FGR@Ot#hke;,`cGBAkX0'vLj,f&g,l+atv(?w)?KHR*t`%x$^ES]%OtuhOtC?xe_9/7@v2S0oP-R4tGqRnRX2.(W#n.^t&95E,(2*oL3m`1j>fwD&kwVD,"
"WiPC,K*rjt+s?aa2t[%M[?]GRLhX/-K>>Ys?OTP'.5]#I<I-K#x[-;m<`o<t3rO8N9sc]5DfN,MAFFj,]/aR4Z(XRI&Y477`X[Hs9TvYsheug)M-EC[7p$iP3G2l+C+@lETd*lAN_J_J"
"i%dlKpGN'JRDJ$l<U37NbFD?%HL@Xsvi2:6egGf]Lrbm,GBJ$lRtKc]x=+>%_$OnhTHD?%(3M+OVHT[To'ua%sEC^KnZ8N+:78N'lGdwK?]st5/A7v6g;+vHNTGW-qDlJU,@Z&TcMM^T"
"AQnc%wMkMPF:&Q+me)g;@jO.->ox<C;t1e,QZAnfQ/(uBBbp<Lsp<cif(,XLNxCIQwxkrIB@@#LFMcf%qGgsMpYVFsTK2pF8vmi,OWP1PfZ;2Q@8/T+tI9`1sk8`l)+hk8.AR$l6dSj)"
"(7@pR.J;h,Avm#%Q27FRJ?5gfR`N$%wEh6N7YeV7>.V5SU*l/-GKC&NP<-O_v3ck8V77h7%d3vLUY]b2pkF8Nig=/))4fX52YAnflo<GRDD2c2]^h9M0^3xb1xl&4drd&I@U$K#Uq5w)"
"5g5*R3iih,5:eatvk>,M0Jc<L3CQDs.S,Z$[*l2^.In'Sf^aP'rBtn3)'t$MD2Ict3f5Z$9uLXLmQcpUb^,Z$fn+WM@++j,H5[]sL3C/U/TAQ+OI9Es3ZR(;R(,YsDYR()N)e$n(j,D)"
"[FTMWL@;GstrXk?s:`]K&W,4+lwswk#/x`N];%jPNL:n$UDZ6XUQwJ3g<M=MA:4j,9kAetJl:j;xh4,<I(;9Ek5o.`w+q`$xqi%J::)M+C*2T70,Hq,B=iPSu(bcR&qlkl.%bOp(ej*E"
"Wm^8NdOs4%r[R&*BSSUMwuYk+bY#ZGRPI1-<Gb>P]#m1P9CFYsE6ta$0rDssl3+@OSc'(*u`j0T_H8.;4%a3Hg_uF%OE#LP?O68CSn_n$A_`6N/qY]P?t-nGR^'lO7l@i,K^1IQ7^C1P"
"ASf>@G1ASNa/`iP5cZ8OxQ-0%ko<GR`Iild'@qi$Ps9aN<k,]PR^chPXY&iB)1GPshf`rQ;u5Lh@Tt,RBJo+jqN>ttgi5eQF+Sm+nu`=,5EjVQA_3;MuJeGM8Cw6NUF%`tC`2'O`?HF2"
".Jg`j+T.V#DU&Tl*5.ifYp4:?g]:xna,(%G:GU8RZv1^tG2'>&,T:'%nW)D&VwB.C3E:mta<j6NvFr*N.>KVMr]oa'UucVf&5:1'tW]-g:H+Gg^ceh9]o@6$RpFqmVN#v$[Ocr9W%Hj9"
")m^p,E=2.1pKW$eeO+4oTR9O;b)Eu57u(m?-De[+NOj#LR;W%ukjRIG5PJcsued7X4JAcs)XHrWsYD`tf8J[FfbU.b&o%c;5pG*RPM%GsRASwUSv<;IwLG1PODn_tFw%Y,`:rVUIO@K%"
"Mg0tVMCNt$`#vLP-:(e;4=548NSlSEYwXCIx`g3IbA7/QC?vXQuiEGR=MZ4+1TBFY/n$eRTueafiu,LP=R*rMv/*3O87RUM7YjXGPql#u'Q<CN?)b7$W1&+Mu/VP'R*((N8pQ_<_i-(="
"av?qM,<=,3+%'mZXG@$Ua3^)^J,7vTd_so$PB1eQ)<S<?D'MF7]8q@IFX&PeFMDI1Y4r*%U81vlEBJI($5:Es)rW@<,LS0k?s_XOR?fnlr:*[sbbKk^S=I%*wpiDE[@=2-g[]M%fY3`t"
"e7bQDI3o+-Rl`OGUB7h+2R5$%:o?C,0cWAX$$fI:j:g&O&9)a:xj31'#kl@UK)H/)b48.[fIaFs?/A[0c,1`tO'%&*=WM;Zph7+--HHD,:p.Fe@;.,X]$Bu,tB/7S]L;`tQ+VpRjJ>I:"
"ZNH*3*iVXs'YPo$T?;ml+j#(3HjkBt.s/Fs(0$G&S+3pA6B'b%m)Q(04&''%HQ/@6NUoG,#+QN,&-]nNa39AY]BIp$RO_UoJrXC.Hv4T[WwvN17$O(S7KEd%UrU&=$C_s-_J_;?)BR4;"
"hD'+;EFMq$w66XL.f[.-uWRPf6tnJQ8xiiL^pVgtTgR$`m8W&kC:G.%fw15o%J9SN:;IC%AU37NDV-s$+Ml<LfFfb)x>WRX95MuV9Nmj$7b8F,,#[E&J]3sk@E)>N7a7K,.ai(1i;Idk"
"?(1</$7lLs-tnO9k.a@4n6I1AJ5#w/U7XhBhf.x$pgW<hJRg/%QewYLg)aDN6le'2)I(p[mbm#uH=clsa0;qLToJ.&bU)+M,D2RsL@ax39LCnfIoMR@&OoD9)/U7%?fX,);h5977dL)h"
"FSfe_et1asbcjA`?*:PQJD;O%Qwuc=v0(AR6`3+)>J2.1i%Gj9<:W56bA+CEgCb$OEKjb)=CMBku5Z[sFrp*M3lw'N@4seLgxr=BZIHe_rP8M,?C5jBE=/JGo)s4E:'v_tdKG2;rvB`t"
"J+8>e_#(Gs;,uMZ)dI1-^YgFJw;$=P@a.^t?wq%*3ATN,'7/^tEnG9%en>:Z2h.JGs9sB8&;a1XYoAUHv,wqWG2ZZ%dg%lGt0gUHml_PMu;NZk@/A=,mY':QN@==,,%/4J&gh'bDfKv;"
"j(tv5f'5&-JuxJCA.$Unuqw@%Me%Z>^1YEdI32Te941Gs?7<sW]1ToQk(F,RYl$E<e0X_j#-2MQV*Tu$R48PEZ%E:QRL>Ds<ou9QEc-7S;bUiLP&Q/ZTcv9QQnU]taweK:_d4]sM`cO,"
"._fts,,0^t8'i%*F8E?TY86N%`_Ntj$`M(9I;^],+3N)EM08+-Ypp-Q8x7i,,Aa^$[_rAKG5T=%;D@d5kPc`g'fpDs#5s4YH%_i_'i(.QP`<`t3O*N'OAYOk*pH[sV<vCs9DaG2UJ]ls"
")`uGg*(iERM:C99mlN;M0[PC/>TS-QRS>gLc-Rt)ChHW$9RUP'?GmU?5duwHX`.xs_HV%tQ,gf))$ARN[_[cW_3vvt9/sd$RKchPwo<l&qQRFH)AE`t`.=TRd%?p3'1e+RHJ'PT;qB]$"
"6U@lp52O%uw,@Z7VwS.`$Q9Eso'k[sRR'Ql3huU#UFP8$ZH4(3QXHof:4h>PT&aFP_fQX>0Rn=DoQ0O71)'I_&7;7[_.9OEpDUJs`hvD,ROe8Iv4G<L*E0Us$6>u>>U;_thMfe(`vE8R"
"j(XcR:c.M'3rlVDN<&r$TDcJ,G=D[9PGA(;bE+Iso1;^qLjdGM:ONnN$[^Z$[XWP'u'k[si?BUQ#Eo0onX@a)2&YWK$pbKJ?2ol>G5VweCSrG,6`%pn4r4as,=Y57uY+Ji#f94Bueud,"
"EbkJLD-u/-(sIO8ln4Wd9R8LK>BbGRn<d*VVq=2Hq-(?%fvpU?eJ<MCohqFs;?.^tBklDsJ.%F4KLoG,'7QN,*-]nN[_[cWg)Oq$b1gm%3]`B,qglF&Tibh9_URHs&jxws7+C_tk0bmD"
"Jl/GsXk]X#3dh<d%:Fjgp-uttbF>DsaQj,)W)wv,5j3Q8q:J$l6pVmL;1DMk,PR77nEk37SSS'j*#YdrcU)+MYvK@I$j%#t+eM`sjUK#uG9YUZ+EYF,`@QP,aie(tQBnDswaNX$R^K8N"
"YGY=taFJp._761:d2e6Nd]XdtG(Q^V8w7cs#k*);Q+LxNYDMs(p&Q$trvj8t;7Vh)G4%hlSDfN%q=mPEqpOtZE1CnVIpE1B)XN#7OdHx4l.pDsL/wK[=P42-m[AIY%?Wq+u.X3%8f6C,"
"4URC,B)V-q-p0`t(0.^tN:(s)#<E1BWI4T%VhmM,&%0xs2Qs<Qg^_<nF(m`22hrHigne3okj1#5&`;MU2]C_%u,_R%IrX,)G;eqM-Jn78i6ck$h0DB;7bmO,QX1Gsw:YQY_C5PRqI9dR"
"j:Dd;JJ?%FXl:;&Qp*m]MVT^=6o1_tn66[b3lL$uIYOQD_5;`tO4Kl^=]Sj0NfX]tXa&'bb5h*i'B&r$v]%#t_dM`s3q<'*@9GF).N<;5cb]<5/VHS%:L$?>C@7csNkjX$Z8gf2/4uF)"
"`Pn,MI=_U-w*'XO%+CvYFT,%SiaOesW#mAqXB0D&,tNMgCDI;V;8C@&`g<A#LL%rQ+M&=dgo`>5`s?qMTMcY?(H&F.c'+gQr^jP'K>xGi+(+Rek]t?0gY-Yskx&_i,1%bR>&E#7k]wYL"
"7^Q^t+J>ws$LrCslK)x)$&Jx+2TTs-cHWiLwiw]c3eW$TRo<`tL#?C<v=pN,Vm%VRCI>UeuE8E,2`x$1&IKLpmJCgC'_`$kpKa(aTX,DsiS:%*82aoXQuBM_EgL.Yd;l&%)m9oDfr9dD"
"[B)m,BUptQJR+j,SjMJQ^USMCg;eqM1m_'%QAefQw`;.L$&B=##)p&t*$K%u9ApEslQ6?t#3K%ug*hhLb)5Is2$>s.,uV8tpHrCsCWKM:Y0'lJb0M/oi#;]s:[2DssYdd)`1XhZ]HLO/"
"[)7ctqc1n<&0(<-r;>&FAjBOEMRa9%h9/]n$fw'hun31^DM`HY?L>Q%2uVm$(2U[F`p6#%pvsI,4eFtL(((]ttW+o.d_m&M*'LHscUR(u?dq;&I.ZAMUjmq6#&uJ2a?s$0H9lQJxr/bA"
"kq^LjkIWCl,NrCs1C2Ds@S.i)HJ/689hOE,1r#G=9%i;lLLdAOD5j[5>o.(WUq_'Wb.SFMNx.T%d:.CafpU/LMw/sMa/+o1JNG[$/G>[Kk?f@%rc%x+ULjD&:[N/%7p>ntE$3mL-wa>3"
"D0.C8+;j$XP_ixbpXQe$oLf4$+xe$Xin)j^[OU3-f%($DLoGG<T;.UCMH]@%QsFt^&H44/HIcTrBO6Sf.]O;Meni?%'/#[KeNL/LE3u/-.bpMsKst98Ac?k7lkx-)vCJF;7`<T%'o'QA"
"EA8x$:@RUMXXhm;QT'IV0r+&bVDE)AQ-C^[/8.77rLO$%),-j^jpJ(MQ-0%QH+aV=.'+A^'BWuJmVanN^qr<D;o_KC',VhKK8EPs.:cFIEH[@Y<MVX5sFd[f:Nw'OMq>%--po,)bE;0X"
"(r(MPR--CFvc^AMe.u.-W^F>%M/O_E>]E)%I'0oN[e4mW>FgHs<<irtM`91P9``l+2(WuLKM8,Pl;6.(ug-@%QZYLPV#_nI$YG1PF(O)%F$B4O[,]ctG767.s(kRNc6EP'fa&Cab2.Pf"
"5P+DsRG)x)oopPS.D)h,0=<l&k]wYL5BUas76GPs[VH[sibH32wobrl&]5eOjVFb`nG=_tT',T%^YEF,T0[?&k$Of(o(9SN8NHFMg2L%uax%u,Q/le;m-suj:L[Djd%.r,APFK:1#PA%"
"+wFb5vF2LT-F2MFCPT)EY?vl,F#<SX^EkxcBTuLXT0/%%Y_nC37_`87LDHD&o34N'26aO/pS[(Ug.).18L0(4.VkM2>>T;*h<7W?#,Zntapev`OMrCsSD$%GBBo5%QtNRN@]O)N.S%i,"
"Q(J/LsuU--ORG;%q[41ZZXMO,6L)N'KT;?s[HnFs:Xhs)O=6YopP%uL'%?P0xW0[$Tg^8Nwkj*..@r*.F.d*.cwnJQ*Cjxc@uVw$;hJOOMK&1Mxkr'<Fe$W%R9oU$^gH,M4@3RN<SnZ$"
"+?ocR`/i0-_e#IA'',eR:2/fi>P#q$P?:*RM@)&./SRfLjH2#tkgWc<QR(W#T6*nj'77fr0Mq4k&i(NgogoR#pAX_<_^(g%]u%7RXikS[AD=2-QogrER*=>?l$vhFhM:B%XQ&`[wqJ'*"
"kiw+R:DU8R4D%.-FeVqMW1NPBpILeQ]&F6J`NL`_'p1xsKY(Abv&KXsk:xD&Gq>`.[6[;Q5S7.-Q'ARNLM<`t4tgWLQ4slBL8sVZ?JF2-N@voFcSIMC/8ak$&))F,M/%@&jT%N01d410"
"RxY<-)88]%3qu[sJb;B,,Q.i)nnF8NFYx;8L-@_W)j9@&2n)dM`7:-M:0>Iso8a9&3uDbV]^-gL47n6N`rg=#GbV8R+$bwU$v3[`@)[rUK=Am+sd;GsA`=8N*>Zk+-JJhG.S%%4(O09&"
"K@CO,kc,Ml6Da]s]gM`s<F[L,<p(pn0AM^,7;AK,e43#8NIbrt9IpFsJR.i)VMq0KLA0^tf^nD&@oqk&WeiN9dUKqm^#(HIY%WG,,OMe_&uC/eeb4f(GgV'68^d'7=`5C%sEoFJJu1c)"
"Kntc^Ht#:B8DsG2kF<f()+@DsU#1k)QJn[FvQ`.Gf@SLZZ:)D%5[WP'Cw&x<iU3(j.a'()f=fwOrKHpie1_$ut.6Rn7lh.[Ckc6%O&(:C:'[/C$r1e,e+;JsCt<R/a>D`tiOwH`e.Jg:"
"x>he(bK5Eh,wNL'fWS-cG_l+a?n*D_R/Q;m54x_,nl_U8qIgP'D6GPsr.ZnRT/`=I)s`]s)7goe^tv?u]toFs([nfPN^?`B?C_s-6BlP7CA9`t#%xeGf+I.-m?H=&ZVwR7-b.^to.6tL"
"D:jiLg4`uRUwOj,rmOF,Q1M:HrWJIZ7di$OJBbol<H.8$dxOO/FS#C%QBa56Tbjt$NgD^JW6HeU74j=G)7@&ee/UV(Kx?/fJx>Is_u6%F6B8EE[g%HWg9SE%B2CtVWh]DsKq2SX,IiP'"
"R4RZs4I&r$](;mh8nY_i4iYAk+EM`sK`Xc<6uOR.8$4,R?h[0%RFr9Mi,)<%,/GF&X1(%4L$>H,Keip).2GF&GN14/kfg_/QjVVM=gU4/5ZpH8_K3xsBC?QIsM`]s7h;7.ao+u#su72f"
"pD%_ix_YQ%^rB8FrS)f:)^NkSaEsPSi;S,l*ou-Q7Un90sBn<&B7rFsfhV]t=SfE%B6iJstIQ,MAFFj,F+Lk)D=fs-=((b$Z/KJ2weqn[KLK@5pt*lJ;gSQ]1Eed`bH[ucBhT-M%Ym$G"
"LJoFswfrS%7lbYDLibh9x,rxsJA#Ii+fFbs;/l2ZD'gP%Tt3ZL6%;c)LZ<&F/G&2ZG:N9%>5=.ou;WO8e8eqMWcbkod[l-G*ja<%M)7'S,clb)6wG>YpF;OE<E,K1OrM_,d?Q3%liw+R"
"_413t'pg2%r+4,RHv`0_GP&T7io4hP:>$s@D]'k$I%W3O^.d#%smYGMb5%FRX$BCM4w#n(A4xa6<^Y7Ck+3L^B;7;VVQY2K-JCtLTG4.u_o#1KZCC;&oRY3%nW)D&g;/KQXtOj,V1s6e"
"#U^Ms9cT2%pxnfQ1G(IVBY]58ju=hP<J?8AFYtj$2U(LG)p72pa^VqMbTL691f+V#pLwKp+'Jo.k4Jgs5aQN'j%YFDeo&=&ZEJ^O:C9bWWPwah8+(o1E=&HsZ]w&*o>ocRJR4/-gx58m"
"NpdGM(KeAJgWG<BJ=eEJ$#Zk+6vq]3]Y%INqVlB&9KvCs4TaDoXNjaZC9kh^4)YH(<*VK,g7u>#bMWcix?axP6FVB,:$QPno#ruO9+[D)WV%4f>u98SH4xJ14_]#*#QcD,o[qFsirth5"
"q1wUt&K+&%4r-UMUj7ctB59]VHV@CTfN^h[7T:YTF1/m+#PuIsJrtoN/Mmk+3_Ucj9FHMinp59&4A9frVRF:&'%TLBG+>J,mK`20:ALI1NfG<-1<fT%?kbIsO#-?Gc._e:24&C&RFDB,"
"jdfe1s=me;_gqTM&[D21[r1pN6&FP^N^_a$WuiMPSD63%,7nVQCkE;M0S=J,g-220o78:6XNlTfheG.oFZRo]6*_XseXT1(CIp;d/`Nq1I<u[=7ww5JJ=(W#-tK'UNqAE,?-0PQs%[=J"
"C+_@IV>2P,n%UP,M+fbiIKAbi5>l9usxSw6eQ(v$i##c2cvH,M31e6N<>.Z$&?ocR_&V0-YI'h@#h]HR4WQ1hM=dq$T^?'S9@5Wd`E4t;+5Qb`1&*2hr`>gLDDr*01a^.iiWfR#j*;Ws"
"2^e8&[o/19WfkS[>842-Oi^rER3XY?ktcLFT4qDEdaMm,::TXQKX4j,XsifQak4/Dg>w6N-T:'%O;[fQj<pF,pC2))'Na4kB>9Ilr<eA,(W5o)qnF8N7$_aYY=>/)pTq8*3c^sQawTaY"
"v5&/MiaQip9mSs?arLQN3foU-%527I-XcAXS^<vPVa:.QLcwTF7CXcNiM@FRafe,)HfM^TjJ=aCbv6UM=H2N=@IcDNMEKoN'2@,Y<6Q]P9L*;Mw^tSIa>u,-cJ$TR`WtVM_&shDk/lDs"
".O]#*1Im9M'P@.-^MhV$n)AGR^sC0-Jle/@uK&-R(F&YdYO_X#qV7:M.DDiL&i%_s[=EY.<MY%/VLXR-BGw^4]1Yw/6,IGV5DB9na9jxaEdXD)I+I.(,T'<-D&$&%s.Kx+otRB3K>p=#"
"'?LgM``MS8ZpPwK9kq9MSWrbtEAK]VI`[_ThZ#.]9d_uTY0nW%rY7:M)w5Y#i._X%YirH,L85g)/b?W$$0'>&i2HQBLB65fIj_9N6UuIsAK;=,jXObD'u<l&qF9RfRkN0KsEmk+EnBk-"
"[,6IQuAMH,l72))6B/LlT:H/l];r8&r;'UsWe=gN$Uj#7EC,IU%N6i$kka$'Y:x5/Gl.B,22)*3t$'mZZSR$UfT>*^Bv$vTqW>q$UgH'S_G9frrP<jLJKDR@%6MH,6f/w5NJ)u/GOvM,"
"pcA=#/<Au,sDxA,1VL^s1#[(bln_cFvNBXmj_OuOMF;JKSTu]sl3Ne)qh=8N^:3mLEu;UQ%=oT%%'bVMH?FP,anbLuUc4hq7:&A&/IiM0n0S[=0bcAX7^-H,cFfoNH-g`Se8@o]Srr#U"
"slbECap$:MD@'E%7I=N,kX-9@X%fi,Fe+-Q*WL'%ad?aI<V8K%q1kcRuE&A&>'nqLdIw9Qn#2L/=rPaplgrX.kPgP,bEVEns,Xg@x^JHR,h=re*%9'NV/'A&,&Ml-:J7$pM,KL,*$K))"
"3c#vTLg5D)`=/-);w0-)#p/^tfh788cRT/)w>s#&fnt[ZYU4:&5=Ar.rqqFs[[g<dd[E@s<w^*7VI1/):)(Js$e;O%A+fM,QsmhLf$IeQNsX$0x33^/OL:RsT-S%%2lq9Mt5w[-LWlcN"
"#Axo]:P2Y23UJM,:%(pN2@8JM;a&EsPJhw-,qEGM>F%IM(DlY@;i0GNrmueQ9V6,%:G-G%n-;bs/,/=)^.:##YcZ(#J]&*#wZ%-#CPo5#O1@8#t*b9#Oo+Y#m0pE#*OrG#FLpM#q>]P#"
"6vXQ#GPLR#[7RS#G;-_#P%ga#lt1c#46+e#Mgte#flQg#'MNh#=i$o#^Cno#wT^q#?N)s#]GJt#p(Gu#.iLv#Iw<x#g^B#$9>j%$a0V($/hR)$Gs9+$o43-$:L,/$T320$p8f1$:8:3$"
"Mo64$gna5$06d7$JgV8$fr=:$&VLV$8:@<$Kk3=$[E'>$,vD@$DVAA$X=GB$o0`C$-h[D$?HXE$P)UF$l(*H$*`&I$LwuJ$ej7L$wD+M$42:N$MuHO$^O<P$xZ#R$86mR$WMfT$$]_r$"
"9:IW$O-bX$b^TY$g-8)t#Eu4OZZni$mUKkEK&L--q?I@&O,cc3'.[+R6VF(ke2t5t6c<4S+d,E,*_Db9sWv7$dxtDs+:OkSnqM?#6D6FMSPT&t6-8biGDiqmA,DqmP^]bi4&od)j->m8"
"YgJnNi@/G,i+nDsHh?_tRW2Te4^atG8v(Q/#W0a:At/uG<>%N0tOkk8-F2MFGgx5<4b;Gs-LRq$n-AE%TDkRFYnw>d1nFB,)DSgLcZ]],db*Z>Ig<kLFvEiID2h*%-;c2/(IJj0[Bh_*"
"Y)Qu#wHe@+Rq81Z:/pS:`f)[$j$p$Us4F`te9w)Eb=WQ&R>#oj5ifU#P04%*Z,aAO<Gb+I^KeSsnL@,Z-x9cbd7BLphMERNZ2/Ks4HQiPG-^OO6u[.-3ntqdB(th',sf4gRI8Ycg/Bhl"
"cq+9@QFWQ&X&8=&s(f>%0DFkf8wGjsLYh@uf?(l0oY'&9#aCg6k^=g1gjd&=l%PwKd:O[=gd/?P_fQX>9_st$HJe`$W?fC,6#9HDBg9C,KOb87YPLjZZafS&fmU_&kr`tGsZ8wep,WZ5"
"g'5&-1?+C,[n5DsZ%vO,[+9CH=G:E%5[WP'eJ)u5D%DsQFDN%u&L188,^/#ubWuV$TgG?K[%&G,8tnPSR$sD%?Zb$b6teJQ%I@S&3<]U-(fpDs,>jE,=Ok`,PGSiL<aQB&u%trM;VF9%"
"L1oF2WqDJQnlZNtk>pFs>X2`tFZVQ&0(XS&%u)I-o9jC,l#FDsD+[W$]47Q&.;VQ&wNZJ,e=t1%noefQFF'SmQ#eGM)T*^JjgcWBKF*bJ%)dk+4Z:A3p.BSNxm28$4[S&*a.qGGEMGWQ"
"kRF9%K]rS%ElWS&n*mLFCJQ.:3fII,uuWVM=4GPskUlkAY.V;ZHinxLEs9RNgi:HM#3>97b*XQ&iDmZ&,$Gb5[PLjZSmP#u(>54%kR,=&oPQBT/tnS&Y_WEE8b%f,#p;I,E9(G%AmiqM"
";rI.-joAJH9^L7@4xFV#Ar%LpU?5(WgoiJs^bQN'xJxqLMZ0@2H<JLZ5X)^Om4B)SR0lHQl[o:d,RUkJQd$Ej#[p<lPX0Q&g%=oNj;vYsFs=Y@,=tMK<TtSRd)ULl6bVi&OK&&k[h3I`"
"rK.g:*AwAktS/&t'DYS&%@*GR3.dlOjZ)PE$3lOMuAWZkIl5eQfKeS&e+I7-A<XGRo<d*VuPxR7>:[dD@9GWQ+<U&tUrC;&LHW.-U&M.Q0waZ53(dZ,*H,3B:TVvlcg;(3v'2H,ehbGM"
"VtNUGq8+@6isneGdVL--dcW<&wTg-Ii;)]s4bOpnu1Cj&utV..Z;RgL?G5gLQROqMW$nS&h5KhlKu4sMblUdM#$uDs)twh&:bj?KYPnS&5&=X(b5`JLc1pDS#%Q3%@>aS&5OAIGH6Tu$"
"N@vw)-@QtL(P@.-9't(S[;#0LE*l/-sEb37<N+t$sY#*E(Aw&F=D]dM8u$UM9U'pn0xI_,q/VG&;15HMNc+sMkp)6.TiXgL.x$BlU7uOI9g;UM;<4sQsOQtL(WI,Mv(ZdMY.[SA#/)Q&"
"KLx.-h^=^$(1gJDx*@61NZl<IB3[Z,xZ&[e&N3_4g?q=kD>dC&>EXA&4Nl0f=<Otl.####]Y`p)+#*##";


static const char* GetDefaultCompressedFontDataTTFBase85()
{
	return Quantum_compressed_data_base85;
}


