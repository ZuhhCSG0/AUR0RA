

#pragma once

#include "entities.h"
#include "SDK.h"
#include "singleton.hpp"

Vector GetAutostrafeView();

class misc
    : public singleton<misc>
{
public:
	void OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local, bool& bSendPacket);
private:
	void AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local);
};
template<class T, class U>
inline T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    else if (in >= high)
        return high;
    else
        return in;
}

inline float bitsToFloat(unsigned long i)
{
    return *reinterpret_cast<float*>(&i);
}


inline float FloatNegate(float f)
{
    return bitsToFloat(FloatBits(f) ^ 0x80000000);
}

char* const skybox_models[] =
{
	"cs_baggage_skybox_",
	"cs_tibet",
	"embassy",
	"italy",
	"jungle",
	"nukeblank",
	"office",
	"sky_cs15_daylight01_hdr",
	"sky_cs15_daylight02_hdr",
	"sky_cs15_daylight03_hdr",
	"sky_cs15_daylight04_hdr",
	"sky_csgo_cloudy01",
	"sky_csgo_night02",
	"sky_csgo_night02b",
	"sky_csgo_night_flat",
	"sky_day02_05_hdr",
	"sky_day02_05",
	"sky_venice",
	"sky_dust",
	"sky_l4d_rural02_ldr",
	"vertigo_hdr",
	"vertigoblue_hdr",
	"vertigo",
	"vietnam"
};

char* const AuroraList[] =
{
	"If you used a gaming carpet, you wouldn't lose!",
	"Why suffer in competitive? Get Project Aurora today!",
	"Gaming Carpets provide the foot stability you need!",
	"Get your premium gaming carpet today!",
	"Dominate the competition with Project Aurora!",
	"Balance your carpets static electricity with Project Aurora!"
};
char* const OffensiveList[] =
{
	"LOL, How much did you tag that wall for?",
	"You've gotta be playing on a touchpad.",
	"Nice reaction time, you sell?",
	"Is this silver?",
	"Why you looking at my kneecaps bro?",
	"Why are you still trying to win?"
};
char* const VACList[] =
{
	"I cant be cheating... you can't cheat on VAC seccured servers!",
	"VAC is a highly advanced anti-cheat! You just cant bypass it!",
	"VAC has detected no cheaters in this lobby! Vac never fails!",
	"Valve is the greatest company on earth, praise be to GabeN!",
	"VAC scans working memory! You can't bypass it! XD",
	"Im sorry, you must be mistaken. You cannot cheat on VAC seccured servers!"
};
char* const NiggerwareList[] =
{
	"Purchase your field nigger today! Only 10$ a month.",
	"Niggerware Enslaves the competiton for 10$ a month.",
	"Damn, I sure wish I had my house nigger with me right now.",
	"Fresh nigger babies, they make good, healthy, fatty meat for a meal.",
	"Damn boy, you should work at my plantation!",
	"I don't care if you're white or sub-human! But my noose does..."
};
char* const pAuroraLinkList[] =
{
	"www.Project-Aurora.xyz | Quality Gaming Carpet!",
	"www.Project-Aurora.xyz | Quality Gaming Carpet!",
	"www.Project-Aurora.xyz | Quality Gaming Carpet!",
	"www.Project-Aurora.xyz | Quality Gaming Carpet!",
	"www.Project-Aurora.xyz | Quality Gaming Carpet!"
};
char* const NiggerwareLinkList[] =
{
	"NIGGERWARE.XYZ | Enslave your competition!",
	"NIGGERWARE.XYZ | Enslave your competition!",
	"NIGGERWARE.XYZ | Enslave your competition!",
	"NIGGERWARE.XYZ | Enslave your competition!",
	"NIGGERWARE.XYZ | Enslave your competition!",
	"NIGGERWARE.XYZ | Enslave your competition!"
};
inline void SetName(const char* new_name)
{
    static auto name = g_CVar->FindVar("name");

    name->SetValue(new_name);
    *reinterpret_cast<int*>(uintptr_t(&name->fnChangeCallback) + 0xC) = 0;
}
inline void setclantag(const char* tag)
{
    static auto ClanTagOffset = U::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", "xxxxxxxxx");
    if (ClanTagOffset)
    {
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
inline void RankReveal(CInput::CUserCmd* cmd)
{
	if (cmd->buttons & IN_SCORE && g_Options.Misc.ServerRankRevealAll)
	{
		static auto ServerRankRevealAll = (bool(__cdecl*)(int*))((PDWORD)U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????"));
		if (g_Options.Misc.ServerRankRevealAll)
		{
			static int fArray[3] = { 0,0,0 };
			ServerRankRevealAll(fArray);
		}
	}
}