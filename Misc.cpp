//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"


std::string animatedclantag;
int iLastTime;
bool bDone=false;
void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local, bool& bSendPacket)
{
	if (g_Options.Misc.Skybox) { ConVar* skybox = g_CVar->FindVar("sv_skyname"); if (skybox) skybox->SetValue(skybox_models[g_Options.Misc.Skybox]); }

	if (g_Options.Misc.fps)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_postprocess_enable");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(0);
			}
		}
	}
	else
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_postprocess_enable");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(1);
			}
		}
	}
	if (g_Options.Misc.Gray)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_drawgray");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(1);
			}
		}
	}
	else
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_drawgray");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(0);
			}
		}
	}
	if (g_Options.Misc.crack)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_showmiplevels");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(1);
			}
		}
	}
	else
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("mat_showmiplevels");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(0);
			}
		}
	}
	//r_showenvcubemap
	if (g_Options.Misc.chromatic)
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("r_showenvcubemap");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(1);
			}
		}
	}
	else
	{
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			ConVar* DrawOtherModels = g_CVar->FindVar("r_showenvcubemap");
			if (DrawOtherModels)
			{
				DrawOtherModels->SetValue(0);
			}
		}
	}
	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{

			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
		}
	}
	if (g_Options.Misc.syncclantag)
	{
		{
			static int counter = 0;
			static int motion = 0;
			int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 2.5;

			if (counter % 48 == 0)
				motion++;
			int value = ServerTime % 20;
			switch (value) {
			case 0: setclantag(XorStr("       ")); break;
			case 1: setclantag(XorStr("p      ")); break;
			case 2: setclantag(XorStr("pA     ")); break;
			case 3: setclantag(XorStr("pAu    ")); break;
			case 4: setclantag(XorStr("pAur   ")); break;
			case 5: setclantag(XorStr("pAuro  ")); break;
			case 6: setclantag(XorStr("pAuror ")); break;
			case 7: setclantag(XorStr("pAurora")); break;
			case 8: setclantag(XorStr("pAuror ")); break;
			case 9: setclantag(XorStr("pAuro  ")); break;
			case 10: setclantag(XorStr("pAur  ")); break;
			case 11: setclantag(XorStr("pAu   ")); break;
			case 12: setclantag(XorStr("pA    ")); break;
			case 13: setclantag(XorStr("p     ")); break;
			case 14: setclantag(XorStr("       ")); break;
			case 15: setclantag(XorStr("Premium")); break;
			case 16: setclantag(XorStr("       ")); break;
			case 17: setclantag(XorStr("Gaming ")); break;
			case 18: setclantag(XorStr("       ")); break;
			case 19: setclantag(XorStr("Carpet ")); break;

			}
			counter++;
		}

		iLastTime = int(g_Globals->curtime);
	}
	if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
	{
		animatedclantag = G::AnimatedClantag;
	}
	if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
	{
		if (int(g_Globals->curtime) != iLastTime)
		{
			auto length = animatedclantag.length();
			animatedclantag.insert(0, 1, animatedclantag[length - 2]);
			animatedclantag.erase(length - 1, 1);

			setclantag(animatedclantag.c_str());
			iLastTime = int(g_Globals->curtime);
		}
	}
	if (g_Options.Misc.namespam)
	{
		char name[151];
		char fucked_char = static_cast<char>(-1);
		for (auto i = 0; i <= 150; i++)
			name[i] = fucked_char;

		const char nick[12] = "pAurora";
		memcpy(name, nick, 11);

		SetName(name);
	}
	static size_t lastTime = 0;
	static int counter = 0;
	if (GetTickCount() > lastTime)
	{

		counter = counter + 1;
		if (counter > 5)
			counter = 0;
		switch (g_Options.Misc.spammer)
		{
		case 1:
			SayInChat(AuroraList[counter]);
			break;
		case 2:
			SayInChat(OffensiveList[counter]);
			break;
		case 3:
			SayInChat(VACList[counter]);
			break;
		case 4:
			SayInChat(NiggerwareList[counter]);
			break;
		case 5:
			SayInChat(pAuroraLinkList[counter]);
			break;
		case 6:
			SayInChat(NiggerwareLinkList[counter]);
			break;
		}

		lastTime = GetTickCount() + 850;


	}
	if (g_Options.Misc.AutoStrafe)
		AutoStrafe(cmd, local);

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());

	static bool WasFiring = false;
	if (pWeapon != nullptr)
	{
		if (MiscFunctions::IsPistol(pWeapon) && g_Options.Legitbot.AutoPistol && pWeapon->m_AttributeManager()->m_Item()->GetItemDefinitionIndex() != 64)
		{
			if (cmd->buttons & IN_ATTACK && !MiscFunctions::IsKnife(pWeapon) && !MiscFunctions::IsGrenade(pWeapon))
			{
				if (WasFiring)
				{
					cmd->buttons &= ~IN_ATTACK;
				}
			}

			WasFiring = cmd->buttons & IN_ATTACK ? true : false;
		}
	}

	if (g_Options.Misc.silentstealer)
	{
		bool bDidMeme = false;
		int iNameIndex = -1;
		char chName[130];
		static ConVar* name = g_CVar->FindVar("name");
		{
			for (int iPlayerIndex = 0; iPlayerIndex < g_Engine->GetMaxClients(); iPlayerIndex++)
			{
				C_BaseEntity *pEntity = g_EntityList->GetClientEntity(iPlayerIndex);
				if (!pEntity || pEntity == local || iPlayerIndex == g_Engine->GetLocalPlayer())
					continue;
				if (rand() % 3 == 1)
				{
					iNameIndex = pEntity->GetIndex();
					bDidMeme = true;
				}
			}
			if (bDidMeme)
			{
				player_info_t pInfo;
				g_Engine->GetPlayerInfo(iNameIndex, &pInfo);
				sprintf(chName, "%s ", pInfo.name);
				name->SetValue(chName);
			}
		}

	}

	if (g_Options.Legitbot.ManualAA)
	{
		if (!g_Options.Legitbot.EnableLegitAA) return;

		if (GetAsyncKeyState(g_Options.Legitbot.AALeft))
		{
			g_Options.Legitbot.AAAngle = -90;
		}
		if (GetAsyncKeyState(g_Options.Legitbot.AARight))
		{
			g_Options.Legitbot.AAAngle = 90;
		}
		if (GetAsyncKeyState(g_Options.Legitbot.AABack))
		{
			g_Options.Legitbot.AAAngle = 180;
		}
		if (GetAsyncKeyState(g_Options.Legitbot.AADisabled))
		{
			g_Options.Legitbot.AAAngle = 0;
		}
	}

	if (g_Options.Legitbot.EnableLegitAA)
	{
		if (!local) return;
		if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE || local->GetMoveType() & MOVETYPE_LADDER) return;
		if (MiscFunctions::IsGrenade(pWeapon)) return;
		{
			static int ChokedPackets = -1;
			ChokedPackets++;
			if (ChokedPackets < 1)
			{
				bSendPacket = true;
			}
			else
			{
				bSendPacket = false;
				cmd->viewangles.y -= g_Options.Legitbot.AAAngle;
				ChokedPackets = -1;
			}
		}
	}
	clamp_angles;
	normalize_angles;
}






void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

    QAngle oldangles; g_Engine->GetViewAngles(oldangles);
    static float move = 450;
    float s_move = move * 0.5065f;
    if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
        return;
    if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
        return;

    if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
    {
        cmd->forwardmove = move * 0.015f;
        cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * s_move;

        if (cmd->mousedx)
            cmd->sidemove = (float)clamp(cmd->mousedx, -1, 1) * s_move;

        static float strafe = cmd->viewangles.y;

        float rt = cmd->viewangles.y, rotation;
        rotation = strafe - rt;

        if (rotation < FloatNegate(g_Globals->interval_per_tick))
            cmd->sidemove = -s_move;

        if (rotation > g_Globals->interval_per_tick)
            cmd->sidemove = s_move;

        strafe = rt;
    }
    movementfix(oldangles, cmd, cmd->forwardmove, cmd->sidemove);
}

