//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once
#include "IDirect3DDevice9.h"
#include "Themes.h"

typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void KnifeApplyCallbk()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}
void dankestSetClanTag(const char* tag, const char* name)
{
	static auto ClanTagOffset = U::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", "xxxxxxxxx");
	if (ClanTagOffset)
	{
		if (strlen(name) > 0) {
			auto name_ = std::string(name);
			auto newline = name_.find("\\n");
			auto tab = name_.find("\\t");
			if (newline != std::string::npos) {
				name_.replace(newline, newline + 2, "\n");
			}
			if (tab != std::string::npos) {
				name_.replace(tab, tab + 2, "\t");
			}
		}
		auto tag_ = std::string(tag);
		if (strlen(tag) > 0) {
			auto newline = tag_.find("\\n");
			auto tab = tag_.find("\\t");
			if (newline != std::string::npos) {
				tag_.replace(newline, newline + 2, "\n");
			}
			if (tab != std::string::npos) {
				tag_.replace(tab, tab + 2, "\t");
			}
		}
		static auto dankesttSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(ClanTagOffset);
		dankesttSetClanTag(tag_.data(), tag_.data());
	}
}

namespace ImGui
{
	class Tab
	{
	private:

		std::vector<std::string> labels;

	public:

		void add(std::string name)
		{
			labels.push_back(name);
		}

		void draw(int *selected)
		{
			ImGuiStyle &style = GetStyle();
			ImVec4 color = style.Colors[ImGuiCol_Button];
			ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
			ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
			ImVec2 max = GetContentRegionMax();
			float size_x = max.x / labels.size() - 0.f;
			float size_y = max.y / labels.size() - 30.f;

			for (size_t i = 0; i < labels.size(); i++)
			{
				if (i == *selected)
				{
					style.Colors[ImGuiCol_Button] = colorActive;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorActive;
				}
				else
				{
					style.Colors[ImGuiCol_Button] = color;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				}

				if (Button(labels.at(i).c_str(), { size_x, size_y }))
					*selected = i;
			}

			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}
	};
}

const char* hitsound[] =
{
	"Off",
	"On",
	"Trump",
	"Skeet"
};


void RenderInfo()
{
	ImGui::BeginChild("Support", ImVec2(150, 140), true);
	{
		ImGui::Text("    Helpful Links");
		ImGui::Separator();
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(255, 152, 0, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(255, 167, 38, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(255, 183, 77, 255);
		if (ImGui::Button(("   Contact Support   ")))
		{
			ShellExecute(NULL, "open", "www.goo.gl/forms/tzttTjroiWV8CzWN2", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(156, 39, 176, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(171, 71, 188, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(186, 104, 200, 255);
		if (ImGui::Button(("Feature Walkthrough")))
		{
			ShellExecute(NULL, "open", "www.project-aurora.xyz/FeatureWalkthrough.pdf", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(76, 175, 80, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(102, 187, 106, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(129, 199, 132, 255);
		if (ImGui::Button((" Request a Feature  ")))
		{
			ShellExecute(NULL, "open", "www.goo.gl/forms/OcAWnEZkChgd27x83", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(244, 67, 54, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(239, 83, 80, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(229, 115, 115, 255);
		if (ImGui::Button(("    Report a Bug     ")))
		{
			ShellExecute(NULL, "open", "www.goo.gl/forms/Efiy7GZEQWI8phS23", NULL, NULL, SW_SHOWNORMAL);
		}


	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("About", ImVec2(190, 140), true);
	{
		ImGui::Text("    Announcement Board");
		ImGui::Separator();
		ImGui::TextDisabled("Thank you for your purchase!");
		ImGui::TextDisabled("If you have any issues please");
		ImGui::TextDisabled("check the Helpful Links area!");
		ImGui::TextDisabled("- 0xAC1D | 5/18/2018");




	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("Links", ImVec2(150, 140), true);
	{
		ImGui::Text("      Developers");
		ImGui::Separator();
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(27, 40, 56, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(49, 61, 75, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(72, 82, 95, 255);
		ImGui::Text("       0xAC1D");
		if (ImGui::Button(("  Steam  ")))
		{
			ShellExecute(NULL, "open", "www.steamcommunity.com/id/Project_Aurora/", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::SameLine();
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(0, 172, 237, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(25, 180, 238, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(50, 188, 240, 255);
		if (ImGui::Button((" Twitter ")))
		{
			ShellExecute(NULL, "open", "www.twitter.com/0xAc1d_", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::Separator();
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(27, 40, 56, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(49, 61, 75, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(72, 82, 95, 255);
		ImGui::Text("      GhostDog");
		if (ImGui::Button(("  Steam  ")))
		{
			ShellExecute(NULL, "open", "www.steamcommunity.com/id/justgowithittob", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::SameLine();
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(114, 137, 218, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(128, 148, 221, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(142, 160, 225, 255);
		if (ImGui::Button((" Discord ")))
		{
			ShellExecute(NULL, "open", "www.discord.gg/aEUg9Ef", NULL, NULL, SW_SHOWNORMAL);
		}
		ImGui::Separator();

	}ImGui::EndChild();
	ImGui::BeginChild("Version", ImVec2(247, 70), true);
	{
		ImGui::Text("          Multi-Hack Information");
		ImGui::Separator();
		ImGui::TextDisabled("     DLL Version: 1.0 - Build: 405");
		ImGui::TextDisabled("   Launcher Version: 1.1 - Build: 55");

	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("Subscription", ImVec2(247, 70), true);
	{
		ImGui::Text("        Subscription  Information");
		ImGui::Separator();
		ImGui::TextDisabled("        Edition: V1 - Iteration: 0");
		ImGui::TextDisabled(" Support Period: 5.18.2018 - 6.30.2018");

	}ImGui::EndChild();
}


void RenderMain()
{

	ImGui::BeginChild("Main", ImVec2(), true);
	{
	static float r = 1.0f;
	static float g = 0.f;
	static float b = 0.f;

	if (r == 1.f && g >= 0.f && b <= 0.f)
	{
		g += 0.005f;
		b = 0.f;
	}
	if (r <= 1.f && g >= 1.f && b == 0.f)
	{
		g = 1.f;
		r -= 0.005f;
	}
	if (r <= 0.f && g == 1.f && b >= 0.f)
	{
		r = 0.f;
		b += 0.005f;
	}
	if (r == 0.f && g <= 1.f && b >= 1.f)
	{
		b = 1.f;
		g -= 0.005f;
	}
	if (r >= 0.f && g <= 0.f && b == 1.f)
	{
		g = 0.f;
		r += 0.005f;
	}
	if (r >= 1.f && g >= 0.f && b <= 1.f)
	{
		r = 1.f;
		b -= 0.005f;
	}
	}ImGui::EndChild();
	ImGui::SameLine();


}

void drawConfig()
{
	ImGui::PushItemWidth(10);
	ImGui::Combo("Config", &g_Options.Menu.ConfigFile, configFiles, ARRAYSIZE(configFiles));
	ImGui::PopItemWidth();
	if (ImGui::Button("Save")) Config->Save();
	ImGui::SameLine();
	if (ImGui::Button("Load")) Config->Load();
	ImGui::SameLine();
	if (ImGui::Button("Reset")) Config->Setup();
}

void RenderLegit()
{

		ImGui::BeginChild("general", ImVec2(180, 210), true);
		{
			ImGui::Text("Aim Modifiers");
			ImGui::Separator();
			ImGui::Checkbox(("Enable Aimbot"), &g_Options.Legitbot.MainSwitch);
			ImGui::Checkbox(("Backtrack"), &g_Options.Legitbot.backtrack);
			ImGui::SliderFloat(("Ticks"), &g_Options.Legitbot.backtrackTicks, 0, 12, "%1.f");
			ImGui::Checkbox(("Auto Pistol"), &g_Options.Legitbot.AutoPistol);
			ImGui::Checkbox(("Draw Fov"), &g_Options.Legitbot.drawFov);

		}ImGui::EndChild();
		ImGui::SameLine();


		ImGui::BeginChild("Aimbot Shit", ImVec2(305, 210), true);
		{

			ImGui::Text("Aimbot Settings");
			ImGui::Separator();

			static int aimtab = 0;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(21, 101, 192, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(30, 136, 229, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 118, 210, 255);

			if (ImGui::Button(XorStr("  Pistol  ")))
			{
				aimtab = 0;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("  Rifle - SMG - Heavy  ")))
			{
				aimtab = 1;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("   Sniper   ")))
			{
				aimtab = 2;
			}




			if (aimtab == 0)
			{


				ImGui::PushItemWidth(80);
				ImGui::Hotkey("Key##1", &g_Options.Legitbot.PistolKey);
				ImGui::PushItemWidth(280);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::SliderFloat("Smooth##1", &g_Options.Legitbot.PistolSmooth, 5.00f, 30.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::SliderFloat("FOV##1", &g_Options.Legitbot.Pistolfov, 0.00f, 5.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::SliderFloat("Min RCS##1", &g_Options.Legitbot.pistol_recoil_min, 1.00f, 75.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::SliderFloat("Max RCS##1", &g_Options.Legitbot.pistol_recoil_max, 1.00f, 75.00f, "%.2f");



			}
			if (aimtab == 1)
			{


				ImGui::PushItemWidth(80);
				ImGui::Hotkey("Key##0", &g_Options.Legitbot.MainKey);
				ImGui::PushItemWidth(280);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::SliderFloat("Smooth##0", &g_Options.Legitbot.MainSmooth, 3.00f, 30.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::SliderFloat("FOV##0", &g_Options.Legitbot.Mainfov, 0.00f, 10.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::SliderFloat("Min RCS##0", &g_Options.Legitbot.main_recoil_min, 1.00f, 75.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::SliderFloat("Max RCS##0", &g_Options.Legitbot.main_recoil_max, 1.00f, 75.00f, "%.2f");


			}
			if (aimtab == 2)
			{

				ImGui::PushItemWidth(80);
				ImGui::Hotkey("Key##2", &g_Options.Legitbot.SniperKey);
				ImGui::PushItemWidth(280);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				ImGui::SliderFloat("Smooth##2", &g_Options.Legitbot.SniperSmooth, 0.01f, 30.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
				ImGui::SliderFloat("FOV##2", &g_Options.Legitbot.Sniperfov, 0.00f, 15.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
				ImGui::SliderFloat("Minimum Recoil Control ##2", &g_Options.Legitbot.sniper_recoil_min, 1.00f, 75.00f, "%.2f");
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::SliderFloat("Maximum Recoil Control ##2", &g_Options.Legitbot.sniper_recoil_max, 1.00f, 75.00f, "%.2f");

			}

		}ImGui::EndChild();
		ImGui::SameLine();






}

void RenderVisuals()
{



		ImGui::BeginChild("one", ImVec2(258, 153), true);
		{
			ImGui::Columns(1);
			ImGui::Text("Player ESP   ");
			ImGui::SameLine();
			ImGui::PushItemWidth(35);
			ImGui::Hotkey("Toggle Key##0", &g_Options.Visuals.ESPKey);
			ImGui::Separator();
			ImGui::Columns(3);
			ImGui::Checkbox(("Box"), &g_Options.Visuals.Box);
			ImGui::Checkbox(("Name"), &g_Options.Visuals.Name);
			ImGui::Checkbox(("HP"), &g_Options.Visuals.HP);
			ImGui::NextColumn();
			ImGui::Checkbox(("Kit"), &g_Options.Visuals.HasDefuser);
			ImGui::Checkbox(("Scope"), &g_Options.Visuals.IsScoped);
			ImGui::Checkbox(("Flash"), &g_Options.Visuals.Flashed);
			ImGui::NextColumn();
			ImGui::Checkbox(("Money"), &g_Options.Visuals.money);
			ImGui::Checkbox(("Weapon"), &g_Options.Visuals.Weapon);
			ImGui::Checkbox(("C4"), &g_Options.Visuals.C4);
			ImGui::Columns(2);
			ImGui::Checkbox(("BT Indicator"), &g_Options.Visuals.backtrackline);
			ImGui::SameLine();
			ImGui::MyColorEdit3(XorStr("##232gd"), (float*)&g_Options.Colors.backtrackdots_color, 1 << 7);
			ImGui::Checkbox(("Underglow"), &g_Options.Visuals.DLight);
			ImGui::SameLine();
			ImGui::MyColorEdit3(XorStr("##63456"), (float*)&g_Options.Colors.dlight_color, 1 << 7);
			ImGui::NextColumn();
			ImGui::Checkbox(("Skeleton"), &g_Options.Visuals.Skeleton);
			ImGui::SameLine();
			ImGui::MyColorEdit3(XorStr("##04593"), (float*)&g_Options.Colors.color_skeleton, 1 << 7);
			ImGui::Checkbox(("Enemies Only"), &g_Options.Visuals.Filter.EnemyOnly);

		}ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("two", ImVec2(234, 153), true);
		{
				ImGui::Columns(1);
				ImGui::Text("World ESP");
				ImGui::Separator();
				ImGui::Columns(2);
				ImGui::Checkbox(("C4 Timer"), &g_Options.Visuals.C4World);
				ImGui::Checkbox(("Radar ESP"), &g_Options.Misc.Radar);
				ImGui::Checkbox(("Grenade ESP"), &g_Options.Visuals.GrenadeESP);
				ImGui::Checkbox(("No-Flash"), &g_Options.Visuals.NoFlash);
				ImGui::NextColumn();
				ImGui::Checkbox(("C4 ESP"), &g_Options.Visuals.bombglow);
				ImGui::SameLine();
				ImGui::MyColorEdit3(XorStr("##35340"), (float*)&g_Options.Colors.C4glow, 1 << 7);
				ImGui::Checkbox(XorStr("Gun ESP"), &g_Options.Visuals.weaponglow);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##ESPWeapon", g_Options.Colors.WeaponGlow, 1 << 7);
				ImGui::Checkbox(("Recoil CH"), &g_Options.Visuals.RecoilCrosshair);
				ImGui::SameLine();
				ImGui::MyColorEdit3(XorStr("##95340"), (float*)&g_Options.Colors.color_recoil, 1 << 7);
				ImGui::Checkbox(("No-Smoke"), &g_Options.Visuals.NoSmoke);
				ImGui::Columns(1);
				ImGui::Checkbox(("Grenade Prediction ESP"), &g_Options.Visuals.GrenadePrediction);
				ImGui::SameLine();
				ImGui::MyColorEdit3(XorStr("##65340"), (float*)&g_Options.Colors.tracer_color, 1 << 7);

		}ImGui::EndChild();
			
		ImGui::BeginChild("three", ImVec2(497, 56), true);
		{
				ImGui::Columns(3);
				ImGui::Checkbox(XorStr("Enemy Chams"), &g_Options.Visuals.Chams);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##42ESP", g_Options.Colors.EnemyChamsVis, 1 << 7);
				ImGui::Checkbox(XorStr("Team Chams"), &g_Options.Visuals.Teamchams);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##E772SP", g_Options.Colors.TeamChamsVis, 1 << 7);
				ImGui::NextColumn();
				ImGui::Checkbox(XorStr("Wall Hack Chams"), &g_Options.Visuals.XQZ);
				ImGui::Text("Enemy: ");
				ImGui::SameLine();
				ImGui::MyColorEdit3("##43ESP", g_Options.Colors.EnemyChamsNVis, 1 << 7);
				ImGui::SameLine();
				ImGui::Text("Team: ");
				ImGui::SameLine();
				ImGui::MyColorEdit3("##79ESP", g_Options.Colors.TeamChamsNVis, 1 << 7);
				ImGui::NextColumn();
				ImGui::Text("Chams Style:");
				ImGui::SameLine();
				ImGui::PushItemWidth(75);
				ImGui::Combo("##sdgl", &g_Options.Visuals.matierial, "Normal\0\rFlat\0\rWireframe\0\0", -1);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
				ImGui::PushItemWidth(150);
				ImGui::SliderInt(XorStr("Chams Alpha"), &g_Options.Visuals.champlayeralpha, 75, 100);

		}ImGui::EndChild();
	
}

void RenderMisc()
{

	static int misctab = 0;


	ImGui::PushItemWidth(80);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.09803921568f, 0.09803921568f, 0.09803921568f, 0.97f);
	ImGui::Combo("", &g_Options.Menu.ConfigFile, configFiles, ARRAYSIZE(configFiles));
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	ImGui::SameLine();
	ImGui::PopItemWidth();
	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(76, 175, 80, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(129, 199, 132, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(102, 187, 106, 255);
	if (ImGui::Button("Save")) Config->Save();
	ImGui::SameLine();
	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(21, 101, 192, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(30, 136, 229, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 118, 210, 255);
	if (ImGui::Button("Load")) Config->Load();
	ImGui::SameLine();
	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(244, 67, 54, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(229, 57, 53, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(211, 47, 47, 255);
	if (ImGui::Button(XorStr("Unhook DLL")))
	{
		g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
		unload = true;
	}
	ImGui::SameLine();
	ImGui::Text("   Developed by: 0xAC1D & GhostDog");
	ImGui::Columns(1, NULL, false);
	ImGui::BeginChild("misctab", ImVec2(490, 185), true);
	{
		static int misctab = 0;
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(21, 101, 192, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(30, 136, 229, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 118, 210, 255);
		if (ImGui::Button(XorStr("         Anti-Aim         ")))
		{
			misctab = 0;
		}

		ImGui::SameLine();

		if (ImGui::Button(XorStr("  NameTags & Indicators  ")))
		{
			misctab = 1;
		}

		ImGui::SameLine();

		if (ImGui::Button(XorStr("      Miscellaneous      ")))
		{
			misctab = 2;
		}

		if (misctab == 0)
		{
			ImGui::Separator();
			ImGui::Columns(2, NULL, false);
			ImGui::Checkbox(("Enable Anti-Aim"), &g_Options.Legitbot.EnableLegitAA);
			ImGui::Checkbox(("Anti-Aim on Keypress"), &g_Options.Legitbot.ManualAA);
			ImGui::Checkbox(XorStr("3rd Person & Toggle Key:"), &g_Options.Visuals.ThirdPerson);
			ImGui::SameLine();
			ImGui::PushItemWidth(51);
			ImGui::Hotkey(XorStr("##273"), &g_Options.Visuals.TPKey);
			ImGui::Text("View Anti-Aim Angles:");
			ImGui::SameLine();
			ImGui::PushItemWidth(51);
			ImGui::Combo("", &g_Options.Visuals.antiaim_thirdperson_angle, AntiAimThirdperson, ARRAYSIZE(AntiAimThirdperson));
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::PushItemWidth(51);
			ImGui::Hotkey(("Left Anti-Aim Key"), &g_Options.Legitbot.AALeft);
			ImGui::PushItemWidth(51);
			ImGui::Hotkey(("Right Anti-Aim Key"), &g_Options.Legitbot.AARight);
			ImGui::PushItemWidth(51);
			ImGui::Hotkey(("Backwards Anti-Aim Key"), &g_Options.Legitbot.AABack);
			ImGui::PushItemWidth(51);
			ImGui::Hotkey(("Disable Anti-Aim Key"), &g_Options.Legitbot.AADisabled);
			ImGui::Columns(1);
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.23f, 0.72f, 1.00f);
			ImGui::PushItemWidth(470);
			ImGui::SliderFloat(XorStr("3rd Persion Distance ##tpdist"), &g_Options.Visuals.tpdist, 50.f, 450.f, "%.0f");
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.34f, 0.13f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.34f, 0.13f, 1.00f);
			ImGui::PushItemWidth(470);
			ImGui::SliderFloat(("Anti-Aim Angle"), &g_Options.Legitbot.AAAngle, -180, 180, "%1.f");
		}
		if (misctab == 1)
		{
			ImGui::Separator();
			ImGui::Columns(2, NULL, false);
			ImGui::PushItemWidth(100);
			static char buf1[128] = ""; ImGui::InputText(("##Name"), buf1, 128, ImGuiInputTextFlags_AllowTabInput);
			ImGui::SameLine();
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(255, 152, 0, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(255, 167, 38, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(255, 183, 77, 255);
			ImGui::PushItemWidth(50);
			if (ImGui::Button(("Change Name")))
			{
				ConVar* name = g_CVar->FindVar("name");
				if (name)
				{
					*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
					name->SetValue(buf1);
				}
			}
			ImGui::PushItemWidth(100);
			static char buf2[128] = ""; ImGui::InputText(("##Clantag"), buf2, 16, ImGuiInputTextFlags_AllowTabInput);
			ImGui::SameLine();
			ImGui::PushItemWidth(50);

			if (ImGui::Button(("Change Clantag")))
			{
				dankestSetClanTag(buf2, buf2);
			}
			ImGui::PushItemWidth(100);
			ImGui::Combo(("Chat Spammer"), &g_Options.Misc.spammer, spammers, ARRAYSIZE(spammers));
			ImGui::Checkbox(("Animated Clantag"), &g_Options.Misc.syncclantag);
			ImGui::NextColumn();
			ImGui::Checkbox(("Time Indicator"), &g_Options.Visuals.Time);
			ImGui::Checkbox(("Logo Indicator"), &g_Options.Misc.Watermark);
			ImGui::Checkbox(("Anti-Aim Indicator"), &g_Options.Misc.AAIndicator);
		}
		if (misctab == 2)
		{
			ImGui::Separator();
			ImGui::Columns(3, NULL, false);
			ImGui::Checkbox(("Auto Accept"), &g_Options.Misc.AutoAccept);
			ImGui::Checkbox(("Bunny Hop"), &g_Options.Misc.Bhop);
			ImGui::Checkbox(("Show Rank"), &g_Options.Misc.ServerRankRevealAll);
			ImGui::Checkbox(("Spectators"), &g_Options.Misc.SpecList);

			ImGui::NextColumn();
			ImGui::Checkbox(("FPS Boost"), &g_Options.Misc.fps);
			ImGui::Checkbox(("Night Mode"), &g_Options.Misc.nightMode);
			ImGui::Checkbox(("Shrooms Mode"), &g_Options.Misc.crack);
			ImGui::NextColumn();
			ImGui::Checkbox(("Hitmarkers"), &g_Options.Misc.Hitmarker);
			ImGui::SameLine();
			ImGui::MyColorEdit3(("##fd5432"), g_Options.Colors.hitmark_color, 1 << 7);
			ImGui::PushItemWidth(50);
			ImGui::Combo(XorStr("Hitmarker Sound"), &g_Options.Misc.hitsound, hitsound, _ARRAYSIZE(hitsound));
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.12f, 0.39f, 1.00f);
			ImGui::PushItemWidth(150);
			ImGui::SliderFloat(("Increase FOV"), &g_Options.Visuals.FOVChanger, 0.f, 60.f, "%.0f");
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
			ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.59f, 0.53f, 1.00f);
			ImGui::PushItemWidth(150);
			ImGui::SliderFloat(("Hand Position"), &g_Options.Visuals.viewmodelChanger, 0.f, 120.f, "%.0f");
		}
		
	}ImGui::EndChild();

}

void RenderSkinChanger()
{
	static int skintab = 0;
	{

		ImGui::Columns(2, NULL, false);
		ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.09803921568f, 0.09803921568f, 0.09803921568f, 0.97f);
		ImGui::Checkbox(("Activate Skinchanger"), &g_Options.Skinchanger.Enabled);
		ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
		ImGui::NextColumn();
		ImGui::PushItemWidth(250);
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(76, 175, 80, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(129, 199, 132, 255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(102, 187, 106, 255);
		if (ImGui::Button(("    Force Update Skins    ")))
		{
			KnifeApplyCallbk();
		}

		ImGui::Columns(1);

		ImGui::BeginChild("SkinchangerTabs", ImVec2(), true);
		{
			static int skintab = 0;
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(21, 101, 192, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(30, 136, 229, 255);
			ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(25, 118, 210, 255);
			if (ImGui::Button(XorStr("  Pistol  ")))
			{
				skintab = 0;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("  Shot-Gun  ")))
			{
				skintab = 1;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("  Heavy  ")))
			{
				skintab = 2;
			}
			
			ImGui::SameLine();

			if (ImGui::Button(XorStr("  SMG  ")))
			{
				skintab = 3;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("  Rifle  ")))
			{
				skintab = 4;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("  Sniper  ")))
			{
				skintab = 5;
			}

			ImGui::SameLine();

			if (ImGui::Button(XorStr("   Other   ")))
			{
				skintab = 6;
			}

			if (skintab == 0)
			{


				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("USP-S"), &g_Options.Skinchanger.uspskin, usps, ARRAYSIZE(usps));
				ImGui::Combo(("P2000"), &g_Options.Skinchanger.p2000skin, p2000, ARRAYSIZE(p2000));
				ImGui::Combo(("Glock-18"), &g_Options.Skinchanger.glock18skin, glock18, ARRAYSIZE(glock18));
				ImGui::Combo(("Dualies"), &g_Options.Skinchanger.dualskin, dual, ARRAYSIZE(dual));
				ImGui::Combo(("P250"), &g_Options.Skinchanger.p250skin, p250, ARRAYSIZE(p250));
				ImGui::NextColumn();
				ImGui::Combo(("CZ-75"), &g_Options.Skinchanger.cz75skin, cz75, ARRAYSIZE(cz75));
				ImGui::Combo(("Five-Seven"), &g_Options.Skinchanger.five7skin, five7, ARRAYSIZE(five7));
				ImGui::Combo(("Tec-9"), &g_Options.Skinchanger.tec9skin, tec9, ARRAYSIZE(tec9));
				ImGui::Combo(("Deagle"), &g_Options.Skinchanger.deagleskin, deagle, ARRAYSIZE(deagle));
				ImGui::Combo(("Revolver"), &g_Options.Skinchanger.revolverskin, revolver, ARRAYSIZE(revolver));



			}
			if (skintab == 1)
			{



				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("Nova"), &g_Options.Skinchanger.novaskin, nova, ARRAYSIZE(nova));
				ImGui::Combo(("XM1014"), &g_Options.Skinchanger.xm1014skin, xm1014, ARRAYSIZE(xm1014));
				ImGui::NextColumn();
				ImGui::Combo(("Mag-7"), &g_Options.Skinchanger.mag7skin, mag7, ARRAYSIZE(mag7));
				ImGui::Combo(("Sawed-Off"), &g_Options.Skinchanger.sawedoffskin, sawedoff, ARRAYSIZE(sawedoff));


			}
			if (skintab == 2)
			{
				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("Negev"), &g_Options.Skinchanger.negevskin, negev, ARRAYSIZE(negev));
				ImGui::NextColumn();
				ImGui::Combo(("M249"), &g_Options.Skinchanger.m249skin, m249, ARRAYSIZE(m249));

			}
			if (skintab == 3)
			{

				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("MP9"), &g_Options.Skinchanger.mp9skin, mp9, ARRAYSIZE(mp9));
				ImGui::Combo(("MAC-10"), &g_Options.Skinchanger.mac10skin, mac10, ARRAYSIZE(mac10));
				ImGui::Combo(("MP7"), &g_Options.Skinchanger.mp7skin, mp7, ARRAYSIZE(mp7));
				ImGui::NextColumn();
				ImGui::Combo(("UMP-45"), &g_Options.Skinchanger.ump45skin, ump45, ARRAYSIZE(ump45));
				ImGui::Combo(("P90"), &g_Options.Skinchanger.p90skin, p90, ARRAYSIZE(p90));
				ImGui::Combo(("PP-Bizon"), &g_Options.Skinchanger.ppbizonskin, ppbizon, ARRAYSIZE(ppbizon));

			}
			if (skintab == 4)
			{

				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("Famas"), &g_Options.Skinchanger.famasskin, famas, ARRAYSIZE(famas));
				ImGui::Combo(("Galil"), &g_Options.Skinchanger.galilskin, galil, ARRAYSIZE(galil));
				ImGui::Combo(("M4A4"), &g_Options.Skinchanger.m4a4skin, m4a4, ARRAYSIZE(m4a4));
				ImGui::Combo(("M4A1-S"), &g_Options.Skinchanger.m4a1skin, m4a1s, ARRAYSIZE(m4a1s));
				ImGui::NextColumn();
				ImGui::Combo(("AK-47"), &g_Options.Skinchanger.ak47skin, ak47, ARRAYSIZE(ak47));
				ImGui::Combo(("AUG"), &g_Options.Skinchanger.augskin, aug, ARRAYSIZE(aug));
				ImGui::Combo(("SG-553"), &g_Options.Skinchanger.sg553skin, sg553, ARRAYSIZE(sg553));

			}
			if (skintab == 5)
			{

				ImGui::Columns(2, NULL, false);
				ImGui::Combo(("SSG-08"), &g_Options.Skinchanger.ssg08skin, ssg08, ARRAYSIZE(ssg08));
				ImGui::Combo(("AWP"), &g_Options.Skinchanger.awpskin, awp, ARRAYSIZE(awp));
				ImGui::NextColumn();
				ImGui::Combo(("SCAR-20"), &g_Options.Skinchanger.scar20skin, scar20, ARRAYSIZE(scar20));
				ImGui::Combo(("G3SG1"), &g_Options.Skinchanger.g3sg1skin, g3sg1, ARRAYSIZE(g3sg1));

			}
			if (skintab == 6)
			{

				ImGui::Combo(("Knife Model"), &g_Options.Skinchanger.Knife, knives, ARRAYSIZE(knives));
				ImGui::Combo(("Knife Skin"), &g_Options.Skinchanger.KnifeSkin, knifeskins, ARRAYSIZE(knifeskins));
				ImGui::Combo(("Gloves"), &g_Options.Skinchanger.gloves, gloves, _ARRAYSIZE(gloves));

			}

		}ImGui::EndChild();
	}
}

