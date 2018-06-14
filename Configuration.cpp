//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>


void CConfig::Setup()
{
	SetupValue(g_Options.Legitbot.drawFov, false, ("Legitbot"), ("DrawFovv"));
	SetupValue(g_Options.Legitbot.AADisabled, false, ("Legitbot"), ("AADisabled"));
	SetupValue(g_Options.Legitbot.AALeft, false, ("Legitbot"), ("AALeft"));
	SetupValue(g_Options.Legitbot.AARight, false, ("Legitbot"), ("AARight"));
	SetupValue(g_Options.Legitbot.AABack, false, ("Legitbot"), ("AABack"));
	SetupValue(g_Options.Legitbot.EnableLegitAA, false, ("Legitbot"), ("Enable Legit Anti-Aim"));
	SetupValue(g_Options.Legitbot.AAAngle, 0, ("Legitbot"), ("AA Angle"));
	SetupValue(g_Options.Legitbot.ManualAA, false, ("Legitbot"), ("Manual AA"));
	SetupValue(g_Options.Legitbot.MainSwitch, false, ("Legitbot"), ("LegitToggle"));
	SetupValue(g_Options.Legitbot.backtrack, false, ("Legitbot"), ("Backtrack"));
	SetupValue(g_Options.Legitbot.backtrackTicks, 0, ("Legitbot"), ("BacktrackTicks"));

	SetupValue(g_Options.Legitbot.AutoPistol, false, ("Legitbot"), ("AutoPistol"));
	SetupValue(g_Options.Legitbot.MainKey, 1, ("Legitbot"), ("Key"));
	SetupValue(g_Options.Legitbot.Mainfov, 0.f, ("Legitbot"), ("FOV"));
	SetupValue(g_Options.Legitbot.MainSmooth, 1.f, ("Legitbot"), ("Speed"));
	SetupValue(g_Options.Legitbot.main_recoil_min, 0, ("Legitbot"), ("RCS-min"));
	SetupValue(g_Options.Legitbot.main_recoil_max, 0, ("Legitbot"), ("RCS-max"));

	SetupValue(g_Options.Legitbot.PistolKey, false, ("Legitbot"), ("Key-Pistol"));
	SetupValue(g_Options.Legitbot.Pistolfov, 0.f, ("Legitbot"), ("FOV-Pistol"));
	SetupValue(g_Options.Legitbot.PistolSmooth, 1.f, ("Legitbot"), ("Speed-Pistol"));
	SetupValue(g_Options.Legitbot.pistol_recoil_min, 0, ("Legitbot"), ("RCS-min-pistol"));
	SetupValue(g_Options.Legitbot.pistol_recoil_max, 0, ("Legitbot"), ("RCS-max-pistol"));

	SetupValue(g_Options.Legitbot.SniperKey, false, ("Legitbot"), ("Key-Sniper"));
	SetupValue(g_Options.Legitbot.Sniperfov, 0.f, ("Legitbot"), ("FOV-Sniper"));
	SetupValue(g_Options.Legitbot.SniperSmooth, 1.f, ("Legitbot"), ("Speed-Sniper"));
	SetupValue(g_Options.Legitbot.sniper_recoil_min, 0, ("Legitbot"), ("RCS-min-sniper"));
	SetupValue(g_Options.Legitbot.sniper_recoil_max, 0, ("Legitbot"), ("RCS-max-sniper"));

	SetupValue(g_Options.Visuals.Skeleton, false, ("Visuals"), ("Skeleton"));
	SetupValue(g_Options.Visuals.IsScoped, false, ("Visuals"), ("IsScoped"));
	SetupValue(g_Options.Visuals.Enabled, false, ("Visuals"), ("VisualsEnabled"));
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("Box"));
	SetupValue(g_Options.Visuals.HasDefuser, false, ("Visuals"), ("Kit"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("Name"));
	SetupValue(g_Options.Visuals.HP, false, ("Visuals"), ("HP"));
	SetupValue(g_Options.Visuals.Weapon, false, ("Visuals"), ("Weapon"));
	SetupValue(g_Options.Visuals.backtrackline, false, ("Visuals"), ("backtrackline"));
	SetupValue(g_Options.Visuals.GrenadeESP, false, ("Visuals"), ("GranadeESP"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("Granade Prediction"));
	SetupValue(g_Options.Visuals.RecoilCrosshair, false, ("Visuals"), ("RecoilCrosshair"));
	SetupValue(g_Options.Visuals.SpreadCrosshair, false, ("Visuals"), ("SpreadCrosshair"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("fovchanger"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 68.f, ("Visuals"), ("viewmodel_fov"));
	SetupValue(g_Options.Visuals.Time, false, ("Visuals"), ("Time"));
	SetupValue(g_Options.Visuals.DLight, false, ("Visuals"), ("DLight"));
	SetupValue(g_Options.Visuals.C4, false, ("Visuals"), ("C4"));
	SetupValue(g_Options.Visuals.ESPKey, false, ("Visuals"), ("ESP Toggle"));
	SetupValue(g_Options.Visuals.money, false, ("Visuals"), ("Money"));
	SetupValue(g_Options.Visuals.NoFlash, false, ("Visuals"), ("NoFlash"));
	SetupValue(g_Options.Visuals.NoSmoke, false, ("Visuals"), ("NoSmoke"));
	
	
	SetupValue(g_Options.Visuals.weaponglow, false, ("Visuals"), ("WeaponGlow"));
	SetupValue(g_Options.Visuals.weaponglowalpha, 255, ("Visuals"), ("WeaponGlow Alpha"));
	SetupValue(g_Options.Colors.WeaponGlow[0], 0.f, ("Colors"), ("Weapon1Color"));
	SetupValue(g_Options.Colors.WeaponGlow[1], 1.f, ("Colors"), ("Weapon2Color"));
	SetupValue(g_Options.Colors.WeaponGlow[2], 0.f, ("Colors"), ("Weapon3Color"));
	SetupValue(g_Options.Visuals.bombglow, false, ("Visuals"), ("BombGlow"));
	SetupValue(g_Options.Visuals.bombglowalpha, 255, ("Visuals"), ("BombGlow Alpha"));
	SetupValue(g_Options.Colors.C4glow[0], 0.f, ("Colors"), ("C41Color"));
	SetupValue(g_Options.Colors.C4glow[1], 1.f, ("Colors"), ("C42Color"));
	SetupValue(g_Options.Colors.C4glow[2], 0.f, ("Colors"), ("C43Color"));

	
	//Chams
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("PlayerChams"));
	SetupValue(g_Options.Visuals.Teamchams, false, ("Visuals"), ("Teamchams"));
	SetupValue(g_Options.Colors.TeamChamsNVis[0], 0.0f, ("Colors"), ("TeamChamsNVisRed"));
	SetupValue(g_Options.Colors.TeamChamsNVis[1], 0.0f, ("Colors"), ("TeamChamsNVisGreen"));
	SetupValue(g_Options.Colors.TeamChamsNVis[2], 1.0f, ("Colors"), ("TeamChamsNVisBlue"));
	SetupValue(g_Options.Colors.TeamChamsVis[0], 0.0f, ("Colors"), ("TeamChamsVisRed"));
	SetupValue(g_Options.Colors.TeamChamsVis[1], 1.0f, ("Colors"), ("TeamChamsVisGreen"));
	SetupValue(g_Options.Colors.TeamChamsVis[2], 0.0f, ("Colors"), ("TeamChamsVisBlue"));
	SetupValue(g_Options.Visuals.XQZ, false, ("Visuals"), ("XQZ Chams"));
	SetupValue(g_Options.Visuals.champlayeralpha, 100, ("Visuals"), ("PlayerCham Alpha"));
	SetupValue(g_Options.Visuals.matierial, 0, ("Visuals"), ("PlayerCham Material"));
	SetupValue(g_Options.Colors.EnemyChamsNVis[0], 1.0f, ("Colors"), ("EnemyChamsNVisRed"));
	SetupValue(g_Options.Colors.EnemyChamsNVis[1], 0.0f, ("Colors"), ("EnemyChamsNVisGreen"));
	SetupValue(g_Options.Colors.EnemyChamsNVis[2], 0.0f, ("Colors"), ("EnemyChamsNVisBlue"));
	SetupValue(g_Options.Colors.EnemyChamsVis[0], 0.0f, ("Colors"), ("EnemyChamsVisRed"));
	SetupValue(g_Options.Colors.EnemyChamsVis[1], 1.0f, ("Colors"), ("EnemyChamsVisGreen"));
	SetupValue(g_Options.Colors.EnemyChamsVis[2], 0.0f, ("Colors"), ("EnemyChamsVisBlue"));
	
	//Skeleton
	SetupValue(g_Options.Colors.color_skeleton[0], 0.98f, ("Colors"), ("SkeletonRed"));
	SetupValue(g_Options.Colors.color_skeleton[1], 0.98f, ("Colors"), ("SkeletonGreen"));
	SetupValue(g_Options.Colors.color_skeleton[2], 0.98f, ("Colors"), ("SkeletonBlue"));
	
	//Grenade Predition
	SetupValue(g_Options.Colors.tracer_color[0], 0.f, ("Colors"), ("Tracer1Color"));
	SetupValue(g_Options.Colors.tracer_color[1], 1.f, ("Colors"), ("Tracer2Color"));
	SetupValue(g_Options.Colors.tracer_color[2], 0.f, ("Colors"), ("Tracer3Color"));

	//Recoil Crosshair
	SetupValue(g_Options.Colors.color_recoil[0], 1.f, ("Colors"), ("RecoilCrosshair1Color"));
	SetupValue(g_Options.Colors.color_recoil[1], 0.f, ("Colors"), ("RecoilCrosshair2Color"));
	SetupValue(g_Options.Colors.color_recoil[2], 0.f, ("Colors"), ("RecoilCrosshair3Color"));

	//Underglow (Dynamic Lights)
	SetupValue(g_Options.Colors.dlight_color[0], 0.f, ("Colors"), ("DynamicLight1Color"));
	SetupValue(g_Options.Colors.dlight_color[1], 1.f, ("Colors"), ("DynamicLight2Color"));
	SetupValue(g_Options.Colors.dlight_color[2], 0.f, ("Colors"), ("DynamicLight3Color"));

	//Backtrack
	SetupValue(g_Options.Colors.backtrackdots_color[0], 1.f, ("Colors"), ("backtrackdots1Color"));
	SetupValue(g_Options.Colors.backtrackdots_color[1], 0.f, ("Colors"), ("backtrackdots2Color"));
	SetupValue(g_Options.Colors.backtrackdots_color[2], 0.f, ("Colors"), ("backtrackdots3Color"));

	//Third Person
	SetupValue(g_Options.Visuals.tpdist, false, ("Visuals"), ("thirdperson distance"));
	SetupValue(g_Options.Visuals.TPKey, false, ("Visuals"), ("thirdperson key"));
	SetupValue(g_Options.Visuals.ThirdPerson, false, ("Visuals"), ("thirdperson switch"));

	//Misc Visuals
	SetupValue(g_Options.Misc.fps, false, ("Visuals"), ("fpsboost"));
	SetupValue(g_Options.Misc.crack, false, ("Visuals"), ("ShroomsMode"));

	//Player ESP Options
	SetupValue(g_Options.Visuals.Filter.EnemyOnly, false, ("Visuals"), ("EnemyOnly"));
	SetupValue(g_Options.Visuals.C4World, false, ("Visuals"), ("C4World"));
	SetupValue(g_Options.Visuals.Flashed, false, ("Visuals"), ("EnemyState"));
	
	//Hitmarkers
	SetupValue(g_Options.Misc.Hitmarker, false, ("Misc"), ("Hitmarker"));
	SetupValue(g_Options.Misc.hitsound, false, ("Misc"), ("Hitmarker Sound"));
	SetupValue(g_Options.Colors.hitmark_color[0], 0.f, ("Colors"), ("hitmarker1Color"));
	SetupValue(g_Options.Colors.hitmark_color[1], 1.f, ("Colors"), ("hitmarker2Color"));
	SetupValue(g_Options.Colors.hitmark_color[2], 0.f, ("Colors"), ("hitmarker3Color"));

	SetupValue(g_Options.Misc.Watermark, true, ("Misc"), ("Watermark"));
	SetupValue(g_Options.Misc.AAIndicator, true, ("Misc"), ("AA Indicator"));
	SetupValue(g_Options.Misc.AutoStrafe, false, ("Misc"), ("AutoStrafe"));
	SetupValue(g_Options.Misc.nightMode, false, ("Misc"), ("NightMode"));
	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("Bhop"));
	SetupValue(g_Options.Misc.ServerRankRevealAll, false, ("Misc"), ("Reveal Ranks"));
	SetupValue(g_Options.Misc.AutoAccept, false, ("Misc"), ("AutoAccept"));
	SetupValue(g_Options.Misc.bought, false, ("Misc"), ("Show enemies purchases"));
	SetupValue(g_Options.Misc.SpecList, false, ("Misc"), ("SpecList"));
	SetupValue(g_Options.Misc.Radar, false, ("Misc"), ("Radar"));
	SetupValue(g_Options.Misc.inventoryalwayson, false, ("Misc"), ("alwayson"));

	SetupValue(g_Options.Skinchanger.Enabled, false, ("Skinchanger"), ("Enabled"));
	//knifes
	SetupValue(g_Options.Skinchanger.Knife, 10, ("SkinChanger"), ("Knife"));
	SetupValue(g_Options.Skinchanger.KnifeSkin, 0, ("SkinChanger"), ("KnifeSkin"));
	//gloves
	SetupValue(g_Options.Skinchanger.gloves, 0, ("SkinChanger"), ("gloves"));
	//pistols
	SetupValue(g_Options.Skinchanger.uspskin, 0, ("SkinChanger"), ("USP-S"));
	SetupValue(g_Options.Skinchanger.p2000skin, 0, ("SkinChanger"), ("P2000"));
	SetupValue(g_Options.Skinchanger.glock18skin, 0, ("SkinChanger"), ("Glock-18"));
	SetupValue(g_Options.Skinchanger.dualskin, 0, ("SkinChanger"), ("Dual Barettas"));
	SetupValue(g_Options.Skinchanger.p250skin, 0, ("SkinChanger"), ("P250"));
	SetupValue(g_Options.Skinchanger.cz75skin, 0, ("SkinChanger"), ("CZ-75"));
	SetupValue(g_Options.Skinchanger.five7skin, 0, ("SkinChanger"), ("Five-Seven"));
	SetupValue(g_Options.Skinchanger.tec9skin, 0, ("SkinChanger"), ("Tec-9"));
	SetupValue(g_Options.Skinchanger.deagleskin, 0, ("SkinChanger"), ("Deagle"));
	SetupValue(g_Options.Skinchanger.revolverskin, 0, ("SkinChanger"), ("Revolver"));
	//heavies
	SetupValue(g_Options.Skinchanger.novaskin, 0, ("SkinChanger"), ("Nova"));
	SetupValue(g_Options.Skinchanger.xm1014skin, 0, ("SkinChanger"), ("XM1014"));
	SetupValue(g_Options.Skinchanger.mag7skin, 0, ("SkinChanger"), ("Mag-7"));
	SetupValue(g_Options.Skinchanger.sawedoffskin, 0, ("SkinChanger"), ("Sawed-Off"));
	SetupValue(g_Options.Skinchanger.m249skin, 0, ("SkinChanger"), ("M249"));
	SetupValue(g_Options.Skinchanger.negevskin, 0, ("SkinChanger"), ("Negev"));
	//mp's
	SetupValue(g_Options.Skinchanger.mp9skin, 0, ("SkinChanger"), ("MP9"));
	SetupValue(g_Options.Skinchanger.mac10skin, 0, ("SkinChanger"), ("Mac-10"));
	SetupValue(g_Options.Skinchanger.mp7skin, 0, ("SkinChanger"), ("MP7"));
	SetupValue(g_Options.Skinchanger.ump45skin, 0, ("SkinChanger"), ("Ump-45"));
	SetupValue(g_Options.Skinchanger.ppbizonskin, 0, ("SkinChanger"), ("PP-Bizon"));
	SetupValue(g_Options.Skinchanger.p90skin, 0, ("SkinChanger"), ("P90"));
	//rifles
	SetupValue(g_Options.Skinchanger.famasskin, 0, ("SkinChanger"), ("Famas"));
	SetupValue(g_Options.Skinchanger.galilskin, 0, ("SkinChanger"), ("Galil"));
	SetupValue(g_Options.Skinchanger.m4a4skin, 0, ("SkinChanger"), ("M4A4"));
	SetupValue(g_Options.Skinchanger.m4a1skin, 0, ("SkinChanger"), ("M4A1-S"));
	SetupValue(g_Options.Skinchanger.ak47skin, 0, ("SkinChanger"), ("AK-47"));
	SetupValue(g_Options.Skinchanger.augskin, 0, ("SkinChanger"), ("Aug"));
	SetupValue(g_Options.Skinchanger.sg553skin, 0, ("SkinChanger"), ("SG-553"));
	//snipers
	SetupValue(g_Options.Skinchanger.ssg08skin, 0, ("SkinChanger"), ("SSG-08"));
	SetupValue(g_Options.Skinchanger.awpskin, 0, ("SkinChanger"), ("AWP"));
	SetupValue(g_Options.Skinchanger.scar20skin, 0, ("SkinChanger"), ("SCAR-20"));
	SetupValue(g_Options.Skinchanger.g3sg1skin, 0, ("SkinChanger"), ("G3SG1"));
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, path)))
	{


		folder = std::string(path) + ("\\Aurora\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\Aurora\\CONFIG_1.ini");
			break;
		case 1:
			file = std::string(path) + ("\\Aurora\\CONFIG_2.ini");
			break;
		case 2:
			file = std::string(path) + ("\\Aurora\\CONFIG_3.ini");
			break;
		case 3:
			file = std::string(path) + ("\\Aurora\\CONFIG_4.ini");
			break;
		}
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\Aurora\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\Aurora\\CONFIG_1.ini");
			break;
		case 1:
			file = std::string(path) + ("\\Aurora\\CONFIG_2.ini");
			break;
		case 2:
			file = std::string(path) + ("\\Aurora\\CONFIG_3.ini");
			break;
		case 3:
			file = std::string(path) + ("\\Aurora\\CONFIG_4.ini");
			break;
		}
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}


CConfig* Config = new CConfig();
Variables g_Options;


