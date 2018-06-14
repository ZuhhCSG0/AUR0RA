//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Tabs.h"
#include <chrono>
#include "Themes.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


void RenderInterface() {


		static int page = 5;

		switch(g_Options.Menu.Theme)
		{
		case 0:
			RenderDefault();
			break;
		}

		ImGui::SetNextWindowSize(ImVec2(510, 280), ImGuiSetCond_Always);

		if (ImGui::Begin(XorStr("Project Aurora"), &g_Options.Menu.Opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | G::extra_flags))
		{



			ImGui::Columns(1, NULL, false);


			const char* tabs[] = {
				
				"VISUALS",
				"AIM",
				"SKIN CHANGER",
				"OTHER",
			};

			for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
			{


				if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
					page = i;


				if (i < IM_ARRAYSIZE(tabs) - 1)
					ImGui::SameLine();
			}

			ImGui::Separator();

			switch (page)
			{
			case 0:
				RenderVisuals();
				break;
			case 1:
				RenderLegit();
				break;
			case 2:
				RenderSkinChanger();
				break;
			case 3:
				RenderMisc();
				break;
			case 4:
				RenderMain();
				break;
			case 5:
				RenderInfo();
				break;
			}
			ImGui::End();
		}
}
