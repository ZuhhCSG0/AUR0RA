//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once
#include "Interface.h"

void RenderDefault()
{
	ImGuiStyle& style = ImGui::GetStyle();


	style.Alpha = 0.99f;               // Global alpha applies to everything in ImGui
	style.WindowPadding = ImVec2(10, 10);     // Padding within a window
	style.WindowMinSize = ImVec2(200, 200);   // Minimum window size
	style.WindowRounding = 1.0f;               // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f); // wysrodkowanie textu tytulu
	style.ChildWindowRounding = 0.0f;               // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	style.FramePadding = ImVec2(4, 3);       // Padding within a framed rectangle (used by most widgets)
	style.FrameRounding = 1.0f;               // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style.ItemSpacing = ImVec2(5, 5);       // Horizontal and vertical spacing between widgets/lines
	style.ItemInnerSpacing = ImVec2(4, 4);       // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style.TouchExtraPadding = ImVec2(0, 0);       // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	style.IndentSpacing = 21.0f;              // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style.ColumnsMinSpacing = 6.0f;               // Minimum horizontal spacing between two columns
	style.ScrollbarSize = 16.0f;              // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style.ScrollbarRounding = 9.0f;               // Radius of grab corners rounding for scrollbar
	style.GrabMinSize = 10.0f;              // Minimum width/height of a grab box for slider/scrollbar
	style.GrabRounding = 8.0f;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f); // Alignment of button text when button is larger than text.
	style.DisplayWindowPadding = ImVec2(22, 22);     // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	style.DisplaySafeAreaPadding = ImVec2(4, 4);       // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	style.AntiAliasedLines = true;               // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style.AntiAliasedShapes = true;               // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	style.CurveTessellationTol = 0.25f;              // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.















	G::extra_flags = 0;
	style.WindowPadding = ImVec2(10, 10);
	style.WindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 4);
	style.FrameRounding = 0.00f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 9.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.92f, 0.93f, 1.00f);    //ImVec4(0.10196078431f, 0.10196078431f, 0.10196078431f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.38f, 0.38f, 0.38, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.09803921568f, 0.09803921568f, 0.09803921568f, 0.97f);  // bg listy
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.06274509803f, 0.08235294117f, 0.15686274509f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);   // border linia to co nizej
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);  // t³o pasek fov i przyciskow
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.49f, 0.20f, 1.00f);  // kolor chekboxa po najechaniu
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.63f, 0.28f, 1.00f); // Checkbox
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09411764705f, 0.09411764705f, 0.09411764705f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.12549019607f, 0.12549019607f, 0.12549019607f, 0.98f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.12549019607f, 0.12549019607f, 0.12549019607f, 0.98f); // pasek górny tam gdzie jest chujowa nazwa
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.12549019607f, 0.12549019607f, 0.12549019607f, 0.98f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.0f, 0.34f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.85f, 0.26f, 0.08f, 1.00f);   //  scroll
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);  ///
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);   // t³o listy
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.69f, 0.31f, 1.00f); // przycisk
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.59f, 0.95f, 1.00f);   // pasek fov 
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.59f, 0.95f, 1.00f); // aktywny pasek fov
	style.Colors[ImGuiCol_Button] = ImVec4(0.96f, 0.26f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.83f, 0.18f, 0.18f, 1.00f);  // kolor button jak sie na niego najedzie
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.72f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);    // aktywna lista
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.90f, 0.45f, 0.45f, 0.99f);  // po najechaniu
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.94f, 0.33, 0.31f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);  // idk cos z lista
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.27450980392f, 0.27450980392f, 0.27450980392f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.90f, 0.45f, 0.58f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);   //
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.89f, 0.76f, 0.38f, 0.63f);  // idk
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.96f, 0.26f, 0.21f, 0.50f);  // idk
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);  // idk
}
