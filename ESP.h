//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once

#include "SDK.h"
#include "singleton.hpp"
class visuals
    :public singleton<visuals>
{
public:
    visuals();
	void OnPaintTraverse(C_BaseEntity* local);
	void DrawPlayer(C_BaseEntity* entity, player_info_t pinfo, C_BaseEntity* local);
	void DrawSkeleton(C_BaseEntity * entity);
private:
	struct playerlist_t
	{
		char *name;
		char *steamid;
		int   money;
		int   health;
		int   mmwins;
		char *mmrank;
	}players[64];
	// Other shit
	C_BaseEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h, gay;
	};
    void DLight(C_BaseEntity* local, C_BaseEntity* entity);

	// Get player info
	Color GetPlayerColor(C_BaseEntity* pEntity, C_BaseEntity* local);
	bool GetBox(C_BaseEntity* pEntity, ESPBox &result);
	void BoxAndText(C_BaseEntity* pEntity, std::string text);

	// Draw shit about player
	void DrawFOVCrosshair();
	void DrawBox(ESPBox size, Color color);
	void PlayerBox(float x, float y, float w, float h, Color clr);
	void DrawHealth(Vector bot, Vector top, float health);
	void DrawHealth(C_BaseEntity* pEntity, ESPBox size);
	void DrawInfo(RECT rect, C_BaseEntity* pPlayer, C_BaseEntity* local);
	RECT DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local);
	void DrawSnapLine(Vector to, Color clr);
	void DrawDrop(C_BaseEntity* pEntity);
	void DrawDropicon(C_BaseEntity* pEntity);
	void DrawBombPlanted(C_BaseEntity* entity, C_BaseEntity* local);
	void DrawBomb(C_BaseEntity* pEntity, ClientClass* cClass);
	void DrawThrowable(C_BaseEntity* throwable);
    void NightMode();
    void SpecList(C_BaseEntity *local);
	void DrawAwall();
	void Hitmarker();
};

inline float CSGO_Armor(float flDamage, int ArmorValue)
{
    float flArmorRatio = 0.5f;
    float flArmorBonus = 0.5f;
    if (ArmorValue > 0) {
        float flNew = flDamage * flArmorRatio;
        float flArmor = (flDamage - flNew) * flArmorBonus;

        if (flArmor > static_cast<float>(ArmorValue)) {
            flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
            flNew = flDamage - flArmor;
        }

        flDamage = flNew;
    }
    return flDamage;
}

template <typename T, std::size_t N> T* end_(T(&arr)[N]) { return arr + N; }

template <typename T, std::size_t N> T* begin_(T(&arr)[N]) { return arr; }


char* const itemNames[] =
{
	"knife", //0 - default
	"deagle",
	"elite",
	"fiveseven",
	"glock",
	"none",
	"none",
	"ak47",
	"aug",
	"awp",

	"famas", //10
	"g3sg1",
	"none",
	"galil",
	"m249",
	"none",
	"m4a4",
	"mac-10",
	"none",
	"p90",

	"none", //20
	"none",
	"none",
	"none",
	"ump45",
	"xm1014",
	"bizon",
	"mag7",
	"negev",
	"sawed-off",

	"tec9", //30
	"taser",
	"p2000",
	"mp7",
	"mp9",
	"nova",
	"p250",
	"none",
	"scar20",
	"sg556",

	"ssg08", //40
	"knife",
	"knife",
	"flash",
	"nade",
	"smoke",
	"molotov",
	"decoy",
	"incendiary",
	"c4",

	"none", //50
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"knife",

	"m4a1", //60
	"usp",
	"none",
	"cz75",
	"revolver"
};


char* const itemNamesicon[] =
{
	"3", //0 - default
	"A", //1
	"B", //2
	"C", //3
	"D", //4
	"none", //5
	"none", //6
	"W", //7
	"U", //8
	"Z", //9

	"R", //10
	"X", //11
	"none", //12
	"Q", //13
	"g", //14
	"none", //15
	"S", //16
	"K", //17
	"none", //18
	"P", //19

	"none", //20
	"none",
	"none",
	"none",
	"L",
	"b",
	"M",
	"d",
	"f",
	"c",

	"H", //30
	"h",
	"E",
	"N",
	"O",
	"e",
	"F",
	"none",
	"Y",
	"V",

	"a", //40
	"1",
	"1",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",

	"none", //50
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"none",
	"knife",

	"T", //60
	"G",
	"none",
	"I",
	"J"
};

inline const char* ItemDefinitionIndexToString(int index)
{
    if (index < 0 || index > 64)
        index = 0;

    return itemNames[index];
}
inline const char* ItemDefinitionIndexToStringicon(int index)
{
	if (index < 0 || index > 64)
		index = 0;

	return itemNamesicon[index];
}
inline float flGetDistance(Vector from, Vector to)
{
    Vector angle;
    angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;

    return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
}
