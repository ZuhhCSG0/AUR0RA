//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once
#include "HookIncludes.h"
#include "Interfaces.h"
#include <ctime>
#include "ESP.h"
typedef void(__thiscall* paint_traverse_t)(PVOID, unsigned int, bool, bool);


bool once = true;
bool once1 = false;
int width1 = 0;
int height1 = 0;
void __fastcall hkPaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
    static auto ofunc = hooks::panel.get_original<paint_traverse_t>(41);
	C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	if (local != nullptr && local->IsAlive() && g_Options.Visuals.noscopeborder && !strcmp("HudZoom", g_Panel->GetName(vguiPanel)))
	{
		return;
	}
    ofunc(pPanels, vguiPanel, forceRepaint, allowForce);
	static unsigned int FocusOverlayPanel = 0;
	static bool FoundPanel = false;
	if (!FoundPanel)
	{
		PCHAR szPanelName = (PCHAR)g_Panel->GetName(vguiPanel);
		if (strstr(szPanelName, "FocusOverlayPanel"))
		{
			FocusOverlayPanel = vguiPanel;
			FoundPanel = true;
		}
	}
	else if (FocusOverlayPanel == vguiPanel)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			static auto linegoesthrusmoke = U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0", "xxxxxxxx????xxx");
			static auto smokecout = *(DWORD*)(linegoesthrusmoke + 0x8);
			if (g_Options.Visuals.NoSmoke) *(int*)(smokecout) = 0;

			visuals::instance().OnPaintTraverse(local);

			auto m_flFlashDuration = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
			auto m_flFlashMaxAlpha = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
			if (local != nullptr)
			{
				CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
				if (g_Options.Visuals.NoFlash)
				{
					*MakePtr(float*, local, m_flFlashDuration) = 0.f;
					*MakePtr(float*, local, m_flFlashMaxAlpha) = 0.f;
				}
				if (local && local->IsScoped() && g_Options.Visuals.noscopeborder && MiscFunctions::IsSniper(pWeapon))
				{
					int width = 0;
					int height = 0;
					g_Engine->GetScreenSize(width, height);

					int centerX = static_cast<int>(width * 0.5f);
					int centerY = static_cast<int>(height * 0.5f);
					g_Render->Line(0, centerY, width, centerY, Color(0, 0, 0, 255));
					g_Render->Line(centerX, 0, centerX, height, Color(0, 0, 0, 255));
				}
			}
		}
		if (!g_Engine->IsInGame()) {
			g_Options.Misc.NameChangerFix = false;
			g_Options.Misc.NameSpammer = 0;
			g_Options.Misc.NoName = false;
			g_Options.Misc.ChatSpamMode = false;
		}

		if (g_Options.Visuals.Time)
		{
			std::time_t result = std::time(nullptr);
			g_Render->Text(95, 1, Color(171, 71, 188, 255), g_Render->font.Watermark, std::asctime(std::localtime(&result)));
			g_Render->Text(235, 1, Color(250, 250, 250, 255), g_Render->font.Watermark, "|");
		}
		if (g_Options.Misc.Watermark)
		{
			g_Render->Text(1, 1, Color(117, 117, 117, 255), g_Render->font.Watermark, "Project");
			g_Render->Text(40, 1, Color(156, 39, 176, 255), g_Render->font.Watermark, "A");
			g_Render->Text(47, 1, Color(33, 150, 243, 255), g_Render->font.Watermark, "u");
			g_Render->Text(54, 1, Color(76, 175, 80, 255), g_Render->font.Watermark, "r");
			g_Render->Text(60, 1, Color(255, 235, 59, 255), g_Render->font.Watermark, "o");
			g_Render->Text(67, 1, Color(255, 152, 0, 255), g_Render->font.Watermark, "r");
			g_Render->Text(73, 1, Color(244, 67, 54, 255), g_Render->font.Watermark, "a");
			g_Render->Text(85, 1, Color(250, 250, 250, 255), g_Render->font.Watermark, "|");
		}
		if (GetKeyState(g_Options.Visuals.ESPKey))
		{
			g_Render->Text(245, 1, Color(66, 165, 245, 255), g_Render->font.Watermark, "ESP Enabled");
		}
		if (g_Options.Legitbot.EnableLegitAA && g_Options.Misc.AAIndicator)
		{
			g_Render->Text(310, 1, Color(250, 250, 250, 255), g_Render->font.Watermark, "|");
			g_Render->Text(320, 1, Color(102, 187, 106, 255), g_Render->font.Watermark, "Anti-Aim Enabled");
			g_Render->Text(410, 1, Color(250, 250, 250, 255), g_Render->font.Watermark, "|");
			g_Render->Text(420, 1, Color(255, 238, 88, 255), g_Render->font.Watermark, "Head Position:");

			if (g_Options.Legitbot.EnableLegitAA && g_Options.Misc.AAIndicator && (g_Options.Legitbot.AAAngle > 0 && g_Options.Legitbot.AAAngle < 179))
			{
				g_Render->Text(495, 1, Color(255, 167, 38, 255), g_Render->font.Watermark, L"Right");
			}
			if (g_Options.Legitbot.EnableLegitAA && g_Options.Misc.AAIndicator && (g_Options.Legitbot.AAAngle < 0 && g_Options.Legitbot.AAAngle > -179))
			{
				g_Render->Text(495, 1, Color(255, 167, 38, 255), g_Render->font.Watermark, L"Left");
			}
			if (g_Options.Legitbot.EnableLegitAA && g_Options.Misc.AAIndicator && (g_Options.Legitbot.AAAngle > 179 || g_Options.Legitbot.AAAngle < -179))
			{
				g_Render->Text(495, 1, Color(239, 83, 80, 255), g_Render->font.Watermark, L"Backward");
			}
			if (g_Options.Legitbot.EnableLegitAA && g_Options.Misc.AAIndicator && (g_Options.Legitbot.AAAngle > -1 && g_Options.Legitbot.AAAngle < 1))
			{
				g_Render->Text(495, 1, Color(189, 189, 189, 255), g_Render->font.Watermark, L"Forward (Anti-Aim Off)");
			}
		}
	}
	}

