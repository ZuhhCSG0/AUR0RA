#pragma once
#include "HookIncludes.h"
static CreateClientClassFn GetWearableCreateFn()
{
	auto clazz = g_CHLClient->GetAllClasses();

	while (strcmp(clazz->m_pNetworkName, "CEconWearable"))
		clazz = clazz->m_pNext;

	return clazz->m_pCreateFn;
}
IClientNetworkable* CL_CreateDLLEntity(int iEnt, int iClass, int iSerialNum)
{
	ClientClass* pClient = g_CHLClient->GetAllClasses();
	if (!pClient)
		return false;

	while (pClient)
	{
		if (pClient->m_ClassID == iClass)
			return pClient->m_pCreateFn(iEnt, iSerialNum);
		pClient = pClient->m_pNext;
	}
	return false;
}

bool isKnife(int id)
{
	switch (id)
	{
	case 42:
	case 500:
	case 506:
	case 505:
	case 508:
	case 507:
	case 515:
	case 514:
	case 512:
	case 516:
	case 59:
		return true;
	}
	return false;
}

void GloveChanger()
{
	C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	player_info_t localPlayerInfo;
	if (!g_Engine->GetPlayerInfo(g_Engine->GetLocalPlayer(), &localPlayerInfo)) return;


	auto wearables = local->GetWearables();
	static CBaseHandle glove_handle = 0;

	auto glove = reinterpret_cast<CGloves*>(g_EntityList->GetClientEntityFromHandle(wearables[0]));

	if (!glove) // There is no glove
	{
		// Try to get our last created glove
		auto our_glove = reinterpret_cast<CGloves*>(g_EntityList->GetClientEntityFromHandle(glove_handle));

		if (our_glove) // Our glove still exists
		{
			wearables[0] = glove_handle;
			glove = our_glove;
		}
	}

	if (!local->IsAlive())
	{
		// We are dead but we have a glove, destroy it
		if (glove)
		{
			glove->SetDestroyedOnRecreateEntities();
			glove->Release();
		}

		return;
	}



	if (!glove)
	{
		int iEnt = g_EntityList->GetHighestEntityIndex() + 1;
		int iSerialNumber = RandomInt(0x0, 0xFFF);

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)CL_CreateDLLEntity(iEnt, (int)ClassID::CEconWearable, iSerialNumber);
		if (pWeapon)
		{
			auto m_Index = iEnt | (iSerialNumber << 16);
			glove_handle = m_Index;
			*(DWORD*)((DWORD)local + offsetz.DT_BaseCombatCharacter.m_hMyWearables) = m_Index;
			glove = (CGloves*)g_EntityList->GetClientEntity(iEnt);
		}

		{
			static auto set_abs_origin_fn = reinterpret_cast<void(__thiscall*)(void*, const Vector&)>
				(U::FindPattern("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x51\x53\x56\x57\x8B\xF1", "xxxxxxxxxxxx"));

			static const Vector new_pos = { 10000.f, 10000.f, 10000.f };

			set_abs_origin_fn(glove, new_pos);
		}
	}



	*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;


	if (glove)
	{
		switch (g_Options.Skinchanger.gloves)
		{
		case 1: //Bloodhound Gloves | Snakebite
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5027 || *glove->FallbackPaintKit() != 10007)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5027;
				*glove->FallbackPaintKit() = 10007;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 2: //Bloodhound Gloves | Bronzed
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5027 || *glove->FallbackPaintKit() != 10008)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5027;
				*glove->FallbackPaintKit() = 10008;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 3: //Bloodhound Gloves | Guerrilla
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5027 || *glove->FallbackPaintKit() != 10039)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5027;
				*glove->FallbackPaintKit() = 10039;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 4: //Bloodhound Gloves | Charred
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5027 || *glove->FallbackPaintKit() != 10006)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5027;
				*glove->FallbackPaintKit() = 10006;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 5: //Hydra Gloves | Case Hardened
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5035 || *glove->FallbackPaintKit() != 10060)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5035;
				*glove->FallbackPaintKit() = 10060;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 6: //Hydra Gloves | Emerald
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5035 || *glove->FallbackPaintKit() != 10057)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5035;
				*glove->FallbackPaintKit() = 10057;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 7: //Hydra Gloves | Rattler
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5035 || *glove->FallbackPaintKit() != 10059)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5035;
				*glove->FallbackPaintKit() = 10059;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 8: //Hydra Gloves | Mangrove
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5035 || *glove->FallbackPaintKit() != 10058)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5035;
				*glove->FallbackPaintKit() = 10058;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 9: //Sport Gloves | Omega
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10047)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10047;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 10: //Sport Gloves | Vice
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10048)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10048;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 11: //Sport Gloves | Amphibious
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10045)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10045;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 12: //Sport Gloves | Bronze Morph
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10046)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10046;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 13: //Sport Gloves | Pandora's Box
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10037)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10037;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 14: //Sport Gloves | Arid
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10019)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10019;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 15: //Sport Gloves | Superconductor
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10018)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10018;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 16: //Sport Gloves | Hedge Maze
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != 10038)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = 10038;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 17: //Hand Wraps | Cobalt Skulls
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10053)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10053;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 18: //Hand Wraps | Overprint
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10054)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10054;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 19: //Hand Wraps | Duct Tape
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10055)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10055;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 20: //Hand Wraps | Arboreal
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10056)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10056;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 21: //Hand Wraps | Slaughter
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10021)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10021;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 22: //Hand Wraps | Leather
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10009)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10009;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 23: //Hand Wraps | Badlands
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10036)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10036;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 24: //Hand Wraps | Spruce DDPAT
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != 10010)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = 10010;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 25: //Driver Gloves | King Snake
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10041)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10041;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 26: //Driver Gloves | Imperial Plaid
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10042)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10042;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 27: //Driver Gloves | Overtake
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10043)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10043;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 28: //Driver Gloves | Racing Green
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10044)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10044;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 29: //Driver Gloves | Diamondback
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10040)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10040;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 30: //Driver Gloves | Crimson Weave
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10016)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10016;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 31: //Driver Gloves | Convoy
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10015)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10015;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 32: //Driver Gloves | Lunar Weave
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != 10013)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = 10013;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 33: //Specialist Gloves | Fade
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10063)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10063;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 34: //Specialist Gloves | Crimson Web
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10061)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10061;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 35: //Specialist Gloves | Mogul
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10064)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10064;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 36: //Specialist Gloves | Buckshot
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10062)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10062;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 37: //Specialist Gloves | Foundation
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10035)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10035;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 38: //Specialist Gloves | Crimson Kimono
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10033)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10033;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 39: //Specialist Gloves | Emerald Web
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10034)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10034;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 40: //Specialist Gloves | Forest DDPAT
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != 10030)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = 10030;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 41: //Moto Gloves | POW!
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10049)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10049;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 42: //Moto Gloves | Turtle
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10050)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10050;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 43: //Moto Gloves | Transport
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10051)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10051;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 44: //Moto Gloves | Polygon
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10052)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10052;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 45: //Moto Gloves | Cool Mint
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10028)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10028;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 46: //Moto Gloves | Boom!
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10027)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10027;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 47: //Moto Gloves | Spearmint
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10026)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10026;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 48: //Moto Gloves | Eclipse
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != 10024)
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = 10024;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		}
	}
}