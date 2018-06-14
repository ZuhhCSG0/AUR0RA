//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once
#include "HookIncludes.h"
#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
std::unordered_map<char*, char*> killIcons = {};
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
HANDLE worldmodel_handle;
CBaseCombatWeapon* worldmodel;


void SkinChanger()
{
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	auto weapons = pLocal->m_hMyWeapons();
	for (size_t i = 0; weapons[i] != INVALID_EHANDLE_INDEX; i++)
	{
		C_BaseEntity *pEntity = g_EntityList->GetClientEntityFromHandle(weapons[i]);
		if (pEntity)
		{
			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntity;
			if (g_Options.Skinchanger.Enabled)
			{
				int Model = g_Options.Skinchanger.Knife;
				int weapon = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
				switch (weapon)
				{
					//Pistols
				case 61: // USP
				{
					switch (g_Options.Skinchanger.uspskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 705;//Cortex
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 657;//Blueprint
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 653;//Neo-Noir
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 637;//Cyrex
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 540;//Lead Conduit
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 504;//Kill Confirmed
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 489;//Torque
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 454;//Para Green
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 217;//Blood Tiger
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 364;//Business Class
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 332;//Royal Blue
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 318;//Road Rash
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 339;//Caiman
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 313;//Orion
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 290;//Guardian
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 277;//Stainless
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 25;//Forest Leaves
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 236;//Night Ops
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 138;//Overgrowth
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 221;//Serum
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 60;//Dark Water
						break;
					default:
						break;
					}
				}
				break;
				case 32: // P2000
				{
					switch (g_Options.Skinchanger.p2000skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 700; //Urban Hazard
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 667; //Woodsman
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 635; //Turf
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 591; //Imperial Dragon
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 550; //Oceanic
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 515; //Imperial
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 443; //Pathfinder
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 485; //Handgun
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 389; //Fire Elemental
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 184; //Corticera
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 346; //Coach Class
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 357; //Ivory
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 95; //Grassland
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 327; //Chainmail
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 275; //Red FragCam
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 338; //Pulse
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 246; //Amber Fade
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 21; //Granite Marbleized
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 32; //Silver
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 211; //Ocean Foam
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 71; //Scorpion
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 104; //Grassland Leaves
						break;
					default:
						break;
					}
				}
				break;
				case 4: // Glock-18
				{
					switch (g_Options.Skinchanger.glock18skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 694; //Moonrise
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 680; //Off World
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 623; //Ironwork
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 607; //Weasel
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 586; //Wasteland Rebel
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 532; //Royal Ledion
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 495; //Wraiths
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 479; //Bunsen Burner
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 437; //Twilight Galaxy
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 399; //Catacombs
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 381; //Grinder
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 353; //Water Elemental
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 40; //Night
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 293; //Death Rattle
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 278; //Blue Fissure
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 3; //Candy Apple
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 2; //Groundwater
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 208; //Sand Dune
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 48; //Dragon Tattoo
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 38; //Fade
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 159; //Brass
						break;
					default:
						break;
					}
				}
				break;
				case 2: // dual
				{
					switch (g_Options.Skinchanger.dualskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 658; //Cobra Strike
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 625; //Royal Consorts
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 544; //Ventilators
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 528; //Cartel
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 491; //Dualing Dragons
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 447; //Duelist
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 450; //Moon in Libra
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 396; //Urban Shock
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 330; //Briar
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 307; //Retribution
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 276; //Panther
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 261; //Marina
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 46; //Contractor
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 249; //Cobalt Quartz
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 43; //Stained
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 47; //Colony
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 190; //Black Limba
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 220; //Hemoglobin
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 153; //Demolition
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 28; //Anodized Navy
						break;
					default:
						break;
					}
				}
				break;
				case 36: // P250
				{
					switch (g_Options.Skinchanger.p250skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 678; //See Ya Later
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 668; //Red Rock
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 650; //Ripple
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 592; //Iron Clad
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 551; //Asiimov
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 501; //Wingshot
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 466; //Crimson Kimono
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 467; //Mint Kimono
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 102; //Whiteout
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 426; //Valence
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 404; //Muertos
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 388; //Cartel
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 373; //Contamination
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 358; //Supernova
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 295; //Franklin
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 271; //Undertow
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 77; //Boreal Forest
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 258; //Mehndi
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 34; //Metallic DDPAT
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 27; //Bone Mask
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 99; //Sand Dune
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 230; //Steel Disruption
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 207; //Facets
						break;
					case 24:
						*pWeapon->FallbackPaintKit() = 219; //Hive
						break;
					case 25:
						*pWeapon->FallbackPaintKit() = 168; //Nuclear Threat
						break;
					case 26:
						*pWeapon->FallbackPaintKit() = 162; //Splash
						break;
					case 27:
						*pWeapon->FallbackPaintKit() = 15; //Gunsmoke
						break;
					case 28:
						*pWeapon->FallbackPaintKit() = 164; //Modern Hunter
						break;
					default:
						break;
					}
				}
				break;
				case 63: // CZ-75
				{
					switch (g_Options.Skinchanger.cz75skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 687; //Tacticat
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 643; //Xiangliu
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 622; //Polymer
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 602; //Imprint
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 543; //Red Astor
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 476; //Yellow Jacket
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 453; //Emerald
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 298; //Army Sheen
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 435; //Pole Position
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 218; //Hexane
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 350; //Tigris
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 366; //Green Plaid
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 325; //Chalice
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 322; //Nitro
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 334; //Twist
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 315; //Poison Dart
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 297; //Tuxedo
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 270; //Victoria
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 269; //The Fuschia Is Now
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 268; //Tread Plate
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 12; //Crimson Web
						break;
					default:
						break;
					}
				}
				break;
				case 3: // Five-7
				{
					switch (g_Options.Skinchanger.five7skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 693; //Flame Test
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 660; //Hyper Beast
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 646; //Capillary
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 605; //Scumbria
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 585; //Violent Daimyo
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 530; //Triumvirate
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 510; //Retrobution
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 464; //Neon Kimono
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 254; //Nitro
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 427; //Monkey Business
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 387; //Urban Hazard
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 377; //Hot Shot
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 352; //Fowl Play
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 274; //Copper Galaxy
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 223; //Nightshade
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 265; //Kami
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 252; //Silver Quartz
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 141; //Orange Peel
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 46; //Contractor
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 78; //Forest Night
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 44; //Case Hardened
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 210; //Anodized Gunmetal
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 3; //Candy Apple
						break;
					case 24:
						*pWeapon->FallbackPaintKit() = 151; //Jungle
						break;
					default:
						break;
					}
				}
				break;
				case 30: // Five-7
				{
					switch (g_Options.Skinchanger.tec9skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 684; //Cracked Opal
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 671; //Cut Out
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 614; //Fuel Injector
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 599; //Ice Cap
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 555; //Re-Entry
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 539; //Jambiya
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 520; //Avalanche
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 463; //Terrace
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 439; //Hades
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 459; //Bamboo Forest
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 374; //Toxic
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 303; //Isaac
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 17; //Urban DDPAT
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 289; //Sandstorm
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 272; //Titanium Bit
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 248; //Red Quartz
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 235; //VariCamo
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 2; //Groundwater
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 242; //Army Mesh
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 216; //Blue Titanium
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 206; //Tornado
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 179; //Nuclear Threat
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 159; //Brass
						break;
					case 24:
						*pWeapon->FallbackPaintKit() = 36; //Ossofied
						break;
					 default:
						break;
					}
				}
				break;
				case 1: // Deagle
				{
					switch (g_Options.Skinchanger.deagleskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 645; //Oxide Blaze
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 603; //Directive
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 527; //Kumicho Dragon
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 509; //Corinthian
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 469; //Sunset Storm 壱
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 470; //Sunset Storm 弐
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 468; //Midnight Storm
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 40; //Night
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 425; //Bronze Deco
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 397; //Naga
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 232; //Crimson Web
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 351; //Conspiracy
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 328; //Hand Cannon
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 347; //Pilot
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 17; //Urban DDPAT
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 296; //Meteorite
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 273; //Heirloom
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 231; //Cobalt Disruption
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 237; //Urban Rubble
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 90; //Mudder
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 185; //Golden Koi
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 61; //Hypnotic
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 37; //Blaze
						break;
					default:
						break;
					}
				}
				break;
				case 64: // Revolver
				{
					switch (g_Options.Skinchanger.revolverskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 701; //Grip
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 683; //Llama Cannon
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 595; //Reboot
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 522; //Fade
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 523; //Amber Fade
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 12; //Crimson Web
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 27; //Bone Mask
						break;
					default:
						break;
					}
				}
				break;
				//heavies
				case 35: // NOVA
				{
					switch (g_Options.Skinchanger.novaskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 699; //Wild Six
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 634; //Gila
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 590; //Exo
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 537; //Hyper Beast
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 484; //Ranger
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 450; //Moon in Libra
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 62; //Bloomstick
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 356; //Koi
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 294; //Green Apple
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 299; //Caged Steel
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 286; //Antique
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 263; //Rising Skull
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 225; //Ghost Camo
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 3; //Candy Apple
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 99; //Sand Dune
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 170; //Predator
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 107; //Polar Mesh
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 214; //Graphite
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 191; //Tempest
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 164; //Modern Hunter
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 166; //Blaze Orange
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 25; //Forest Leaves
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 158; //Walnut
						break;
					default:
						break;
					}
				}
				break;
				case 25: // XM1014
				{
					switch (g_Options.Skinchanger.xm1014skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 706; //Oxide Blaze
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 689; //Ziggy
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 654; //Seasons
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 616; //Slipstream
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 557; //Black Tie
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 521; //Teclu Burner
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 505; //Scumbria
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 407; //Quicksilver
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 393; //Tranquility
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 370; //Bone Machine
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 320; //Red Python
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 348; //Red Leather
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 238; //VariCamo Blue
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 314; //Heaven Guard
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 42; //Blue Steel
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 240; //CaliCamo
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 96; //Blue Spruce
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 205; //Jungle
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 166; //Blaze Orange
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 169; //Fallout Warning
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 95; //Grassland
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 135; //Urban Perforated
						break;
					default:
						break;
					}
				}
				break;
				case 27: // MAG-7
				{
					switch (g_Options.Skinchanger.mag7skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 703; //SWAG-7
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 666; //Hard Water
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 633; //Sonar
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 608; //Petroglyph
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 535; //Praetorian
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 499; //Cobalt Core
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 462; //Counter Terrace
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 473; //Seabird
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 431; //Heat
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 385; //Firestarter
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 32; //Silver
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 100; //Storm
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 291; //Heaven Guard
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 39; //Bulldozer
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 34; //Metallic DDPAT
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 198; //Hazard
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 177; //Memento
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 171; //Irradiated Alert
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 99; //Sand Dune
						break;
					default:
						break;
					}
				}
				break;
				case 29: // Sawed-Off
				{
					switch (g_Options.Skinchanger.sawedoffskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 673; //Morris
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 655; //Zander
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 638; //Wasteland Princess
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 596; //Limelight
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 552; //Fubar
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 517; //Yorick
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 458; //Bamboo Shadow
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 434; //Origami
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 405; //Serenity
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 390; //Highwayman
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 345; //First Class
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 323; //Rust Coat
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 119; //Sage Spray
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 5; //Forest DDPAT
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 256; //The Kraken
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 250; //Full Stop
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 246; //Amber Fade
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 30; //Snake Camo
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 204; //Mosaico
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 83; //Orange DDPAT
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 41; //Copper
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 171; //Irradiated Alert
						break;
					default:
						break;
					}
				}
				break;
				case 28: // Negev
				{
					switch (g_Options.Skinchanger.negevskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 698; //Lionfish
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 610; //Dazzle
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 514; //Power Loader
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 483; //Loudmouth
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 432; //Man-o'-war
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 369; //Nuclear Waste
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 317; //Bratatat
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 355; //Desert-Strike
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 298; //Army Sheen
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 285; //Terrain
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 240; //CaliCamo
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 201; //Palm
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 28; //Anodized Navy
						break;
					default:
						break;
					}
				}
				break;
				case 14: // M249
				{
					switch (g_Options.Skinchanger.m249skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 648; //Emerald Poison Dart
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 547; //Spectre
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 496; //Nebula Crusader
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 452; //Shipping Forecast
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 472; //Impact Drill
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 401; //System Lock
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 22; //Contrast Spray
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 266; //Magma
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 243; //Gator Mesh
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 202; //Jungle DDPAT
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 75; //Blizzard Marbleized
						break;
					default:
						break;
					}
				}
				break;
				//mp's
				case 34: // MP9
				{
					switch (g_Options.Skinchanger.mp9skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 697; //Black Sand
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 679; //Goo
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 630; //Sand Scale
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 609; //Airlock
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 549; //Bioleak
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 482; //Ruby Poison Dart
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 448; //Pandora's Box
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 403; //Deadly Poison
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 386; //Dart
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 368; //Setting Sun
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 329; //Dark Age
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 366; //Green Plaid
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 100; //Storm
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 262; //Rose Iron
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 33; //Hot Rod
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 141; //Orange Peel
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 148; //Sand Dashed
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 61; //Hypnotic
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 199; //Dry Season
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 39; //Bulldozer
						break;
					default:
						break;
					}
				}
				break;
				case 17: // MAC-10
				{
					switch (g_Options.Skinchanger.mac10skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 682; //Oceanic
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 665; //Aloha
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 651; //Last Dive
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 589; //Carnivore
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 534; //Lapis Gator
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 498; //Rangeen
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 38; //Fade
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 433; //Neon Rider
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 402; //Malachite
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 372; //Nuclear Garden
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 98; //Ultraviolet
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 343; //Commuter
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 333; //Indigo
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 337; //Tatter
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 310; //Curse
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 32; //Silver
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 284; //Heat
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 246; //Amber Fade
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 157; //Palm
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 3; //Candy Apple
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 188; //Graven
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 101; //Tornado
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 17; //Urban DDPAT
						break;
					default:
						break;
					}
				}
				break;
				case 33: // MP7
				{
					switch (g_Options.Skinchanger.mp7skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 696; //Bloodsport
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 649; //Akoben
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 627; //Cirrus
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 536; //Impire
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 500; //Special Delivery
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 481; //Nemesis
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 250; //Full Stop
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 442; //Asterion
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 423; //Armor Core
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 213; //Ocean Foam
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 354; //Urban Hazard
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 15; //Gunsmoke
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 365; //Olive Plaid
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 5; //Forest DDPAT
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 28; //Anodized Navy
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 141; //Orange Peel
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 245; //Army Recon
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 209; //Groundwater
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 11; //Skulls
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 102; //Whiteout
						break;
					default:
						break;
					}
				}
				break;
				case 24: // UMP-45
				{
					switch (g_Options.Skinchanger.ump45skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 704; //Arctic Wolf
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 688; //Exposure
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 672; //Metal Flowers
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 652; //Scaffold
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 615; //Briefing
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 556; //Primal Saber
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 488; //Riot
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 441; //Minotaur's Labyrinth
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 436; //Grand Prix
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 392; //Delusion
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 362; //Labyrinth
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 333; //Indigo
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 175; //Scorched
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 70; //Carbon Fiber
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 281; //Corporal
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 37; //Blaze
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 15; //Gunsmoke
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 17; //Urban DDPAT
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 193; //Bone Pile
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 169; //Fallout Warning
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 93; //Caramel
						break;
					default:
						break;
					}
				}
				break;
				case 19: // P90
				{
					switch (g_Options.Skinchanger.p90skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 669; //Death Grip
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 636; //Shallow Grave
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 611; //Grim
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 593; //Chopper
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 516; //Shapewood
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 486; //Elite Build
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 20; //Virus
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 359; //Asiimov
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 342; //Leather
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 100; //Storm
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 335; //Module
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 311; //Desert Warfare
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 283; //Trigon
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 228; //Blind Spot
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 244; //Teardown
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 234; //Ash Wood
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 175; //Scorched
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 124; //Sand Spray
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 67; //Cold Blooded
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 182; //Emerald Dragon
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 156; //Death by Kitty
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 111; //Glacier Mesh
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 169; //Fallout Warning
						break;
					default:
						break;
					}
				}
				break;
				case 26: // PP-Bizon
				{
					switch (g_Options.Skinchanger.ppbizonskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 692; //Night Riot
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 676; //High Roller
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 641; //Jungle Slipstream
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 594; //Harvester
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 542; //Judgement of Anubis
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 526; //Photic Zone
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 508; //Fuel Rod
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 457; //Bamboo Print
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 376; //Chemical Green
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 13; //Blue Streak
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 349; //Osiris
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 306; //Antique
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 224; //Water Sigil
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 267; //Cobalt Halftone
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 159; //Brass
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 236; //Night Ops
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 148; //Sand Dashed
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 149; //Urban Dashed
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 203; //Rust Coat
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 164; //Modern Hunter
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 70; //Carbon Fiber
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 25; //Forest Leaves
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 171; //Irradiated Alert
						break;
					default:
						break;
					}
				}
				break;
				//Rifles
				case 13: // Galil
				{
					switch (g_Options.Skinchanger.galilskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 661; //Sugar Rush
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 647; //Crimson Tsunami
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 629; //Black Sand
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 546; //Firefight
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 494; //Stone Cold
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 478; //Rocket Pop
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 460; //Aqua Terrace
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 237; //Urban Rubble
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 428; //Eco
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 398; //Chatterbox
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 379; //Cerberus
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 308; //Kami
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 297; //Tuxedo
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 216; //Blue Titanium
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 264; //Sandstorm
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 235; //VariCamo
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 119; //Sage Spray
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 241; //Hunting Blind
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 192; //Shattered
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 83; //Orange DDPAT
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 76; //Winter Forest
						break;
					default:
						break;
					}
				}
				break;
				case 10: // Famas
				{
					switch (g_Options.Skinchanger.famasskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 659; //Macabre
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 626; //Mecha Industires
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 604; //Roll Cage
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 529; //Valance
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 492; //Survivor Z
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 477; //Neural Net
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 429; //Djinn
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 371; //Styx
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 288; //Sergeant
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 154; //Afterimage
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 260; //Pulse
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 244; //Teardown
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 92; //Cyanospatter
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 47; //Colony
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 218; //Hexane
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 194; //Spitfire
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 178; //Doomkitty
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 22; //Contrast Spray
						break;
					}
				}
				break;
				case 16: // M4A4
				{
					switch (g_Options.Skinchanger.m4a4skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 695; //Neo-Noir
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 664; //Hellfire
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 632; //Buzz Kill
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 588; //Desolate Space
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 533; //The Battlestar
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 512; //Royal Paladin
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 449; //Poseidon
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 480; //Evil Daimyo
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 471; //Daybreak
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 400; //龍王 (Dragon King)
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 384; //Griffin
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 155; //Bullet Rain
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 336; //Desert-Strike
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 309; //Howl
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 255; //Asiimov
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 215; //X-Ray
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 17; //Urban DDPAT
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 187; //Zirka
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 164; //Modern Hunter
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 176; //Faded Zebra
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 167; //Radiation Hazard
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 101; //Tornado
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 16; //Jungle Tiger
						break;
					case 24:
						*pWeapon->FallbackPaintKit() = 8; //Desert Storm
						break;
					default:
						break;
					}
				}
				break;
				case 60: // M4A1-S
				{
					switch (g_Options.Skinchanger.m4a1skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 681; //Leaded Glass
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 663; //Briefing
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 644; //Decimator
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 631; //Flashback
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 587; //Mecha Industries
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 548; //Chantico's Fire
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 497; //Golden Coil
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 445; //Hot Rod
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 440; //Icarus Fell
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 430; //Hyper Beast
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 383; //Basilisk
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 360; //Cyrex
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 326; //Knight
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 321; //Master Piece
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 301; //Atomic Alloy
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 257; //Guardian
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 254; //Nitro
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 235; //VariCamo
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 77; //Boreal Forest
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 217; //Blood Tiger
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 189; //Bright Water
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 60; //Dark Water
						break;
					default:
						break;
					}
				}
				break;
				case 7: // AK47
				{
					switch (g_Options.Skinchanger.ak47skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 675; //The Empress
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 656; //Orbit Mk01
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 639; //Bloodsport
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 600; //Neon Revolution
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 524; //Fuel Injector
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 506; //Point Disarray
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 490; //Frontside Misty
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 474; //Aquamarine Revenge
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 456; //Hydroponic
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 422; //Elite Build
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 394; //Cartel
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 380; //Wasteland Rebel
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 316; //Jaguar
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 340; //Jet Set
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 341; //First Class
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 302; //Vulcan
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 300; //Emerald Pinstripe
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 282; //Redline
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 226; //Blue Laminate
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 72; //Safari Mesh
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 180; //Fire Serpent
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 44; //Case Hardened
						break;
					case 23:
						*pWeapon->FallbackPaintKit() = 14; //Red Laminate
						break;
					case 24:
						*pWeapon->FallbackPaintKit() = 172; //Black Laminate
						break;
					case 25:
						*pWeapon->FallbackPaintKit() = 122; //Jungle Spray
						break;
					case 26:
						*pWeapon->FallbackPaintKit() = 170; //Predator
						break;
					default:
						break;
					}
				}
				break;
				case 8: // AUG
				{
					switch (g_Options.Skinchanger.augskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 690; //Stymphalian
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 674; //Triqua
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 601; //Syd Mead
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 583; //Aristocrat
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 541; //Fleet Flock
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 507; //Ricochet
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 455; //Akihabara Accept
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 444; //Deadalus
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 375; //Radiation Hazard
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 9; //Bengal Tiger
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 305; //Torque
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 280; //Chameleon
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 110; //Condemned
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 100; //Storm
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 46; //Contractor
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 47; //Colony
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 197; //Anodized Navy
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 73; //Wings
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 33; //Hot Rod
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 10; //Copperhead
						break;
					default:
						break;
					}
				}
				break;
				case 39: // SG 553
				{
					switch (g_Options.Skinchanger.sg553skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 702; //Aloha
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 686; //Phantom
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 613; //Triarch
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 598; //Aerial
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 553; //Atlas
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 519; //Tiger Moth
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 487; //Cyrex
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 39; //Bulldozer
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 378; //Fallout Warning
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 363; //Traveler
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 298; //Army Sheen
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 287; //Pulse
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 28; //Anodized Navy
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 247; //Damascus Steel
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 243; //Gator Mesh
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 136; //Waves Perforated
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 186; //Wave Spray
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 98; //Ultraviolet
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 101; //Tornado
						break;
					default:
						break;
					}
				}
				break;

				//snipers

				case 40: // SSG 08
				{
					switch (g_Options.Skinchanger.ssg08skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 670; //Death's Head
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 624; //Dragonfire
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 554; //Ghost Crusader
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 538; //Necropos
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 503; //Big Iron
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 60; //Dark Water
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 361; //Abyss
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 319; //Detour
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 99; //Sand Dune
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 304; //Slashed
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 253; //Acid Fade
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 233; //Tropical Storm
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 96; //Blue Spruce
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 222; //Blood in the Water
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 200; //Mayan Dreams
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 26; //Lichen Dashed
						break;
					default:
						break;
					}
				}
				break;
				case 9: // AWP
				{
					switch (g_Options.Skinchanger.awpskin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 691; //Mortis
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 662; //Oni Taiji
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 640; //Fever Dream
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 584; //Phobos
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 525; //Elite Build
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 475; //Hyper Beast
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 446; //Medusa
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 451; //Sun in Leo
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 424; //Worm God
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 395; //Man-o'-war
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 181; //Corticera
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 344; //Dragon Lore
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 84; //Pink DDPAT
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 279; //Asiimov
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 259; //Redline
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 227; //Electric Hive
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 251; //Pit Viper
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 72; //Safari Mesh
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 212; //Graphite
						break;
					case 20:
						*pWeapon->FallbackPaintKit() = 51; //Lightning Strike
						break;
					case 21:
						*pWeapon->FallbackPaintKit() = 174; //BOOM
						break;
					case 22:
						*pWeapon->FallbackPaintKit() = 30; //Snake Camo
						break;
					default:
						break;
					}
				}
				break;
				case 38: // SCAR-20
				{
					switch (g_Options.Skinchanger.scar20skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 685; //Jungle Slipstream
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 642; //Blueprint
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 612; //Powercore
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 597; //Bloodsport
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 518; //Outbreak
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 502; //Green Marine
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 298; //Army Sheen
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 406; //Grotto
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 391; //Cardiac
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 100; //Storm
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 312; //Cyrex
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 70; //Carbon Fiber
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 46; //Contractor
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 116; //Sand Mesh
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 232; //Crimson Web
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 196; //Emerald
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 165; //Splash Jam
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 157; //Palm
						break;
					default:
						break;
					}
				}
				break;
				case 11: // G3SG1
				{
					switch (g_Options.Skinchanger.g3sg1skin)
					{
					case 0:
						break;
					case 1:
						*pWeapon->FallbackPaintKit() = 677; //Hunter
						break;
					case 2:
						*pWeapon->FallbackPaintKit() = 628; //Stinger
						break;
					case 3:
						*pWeapon->FallbackPaintKit() = 606; //Ventilator
						break;
					case 4:
						*pWeapon->FallbackPaintKit() = 545; //Orange Crash
						break;
					case 5:
						*pWeapon->FallbackPaintKit() = 511; //The Executioner
						break;
					case 6:
						*pWeapon->FallbackPaintKit() = 493; //Flux
						break;
					case 7:
						*pWeapon->FallbackPaintKit() = 438; //Chronos
						break;
					case 8:
						*pWeapon->FallbackPaintKit() = 465; //Orange Kimono
						break;
					case 9:
						*pWeapon->FallbackPaintKit() = 382; //Murky
						break;
					case 10:
						*pWeapon->FallbackPaintKit() = 46; //Contractor
						break;
					case 11:
						*pWeapon->FallbackPaintKit() = 294; //Green Apple
						break;
					case 12:
						*pWeapon->FallbackPaintKit() = 229; //Azure Zebra
						break;
					case 13:
						*pWeapon->FallbackPaintKit() = 235; //VariCamo
						break;
					case 14:
						*pWeapon->FallbackPaintKit() = 147; //Jungle Dashed
						break;
					case 15:
						*pWeapon->FallbackPaintKit() = 74; //Polar Camo
						break;
					case 16:
						*pWeapon->FallbackPaintKit() = 8; //Desert Storm
						break;
					case 17:
						*pWeapon->FallbackPaintKit() = 72; //Safari Mesh
						break;
					case 18:
						*pWeapon->FallbackPaintKit() = 195; //Demeter
						break;
					case 19:
						*pWeapon->FallbackPaintKit() = 6; //Arctic Camo
						break;
					default:
						break;
					}
				}
				break;
				default:
					break;
				}
				if (pEntity->GetClientClass()->m_ClassID == (int)ClassID::CKnife)
				{
					worldmodel_handle = pWeapon->m_hWeaponWorldModel();
					if (worldmodel_handle) worldmodel = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(worldmodel_handle);
					if (Model == 0) // Bayonet
					{
						int iBayonet = g_ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
						*pWeapon->ModelIndex() = iBayonet; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iBayonet;
						if (worldmodel) *worldmodel->ModelIndex() = iBayonet + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 500;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "bayonet";
						killIcons["knife_t"] = "bayonet";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 558; // Lore
						}
					}
					else if (Model == 1) // Bowie Knife
					{
						int iBowie = g_ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
						*pWeapon->ModelIndex() = iBowie; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iBowie;
						if (worldmodel) *worldmodel->ModelIndex() = iBowie + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 514;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_survival_bowie";
						killIcons["knife_t"] = "knife_survival_bowie";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 558; // Lore
						}

					}
					else if (Model == 2) // Butterfly Knife
					{
						int iButterfly = g_ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
						*pWeapon->ModelIndex() = iButterfly; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iButterfly;
						if (worldmodel) *worldmodel->ModelIndex() = iButterfly + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 515;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_butterfly";
						killIcons["knife_t"] = "knife_butterfly";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 558; // Lore
						}

					}
					else if (Model == 3) // Falchion Knife
					{
						int iFalchion = g_ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
						*pWeapon->ModelIndex() = iFalchion; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iFalchion;
						if (worldmodel) *worldmodel->ModelIndex() = iFalchion + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 512;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_falchion";
						killIcons["knife_t"] = "knife_falchion";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 558; // Lore
						}
					}
					else if (Model == 4) // Flip Knife
					{
						int iFlip = g_ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
						*pWeapon->ModelIndex() = iFlip; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iFlip;
						if (worldmodel) *worldmodel->ModelIndex() = iFlip + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 505;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_flip";
						killIcons["knife_t"] = "knife_flip";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 559; // Lore
						}

					}
					else if (Model == 5) // Gut Knife
					{
						int iGut = g_ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
						*pWeapon->ModelIndex() = iGut; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iGut;
						if (worldmodel) *worldmodel->ModelIndex() = iGut + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 506;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_gut";
						killIcons["knife_t"] = "knife_gut";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 560; // Lore
						}
					}
					else if (Model == 6) // Huntsman Knife
					{
						int iHuntsman = g_ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
						*pWeapon->ModelIndex() = iHuntsman; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iHuntsman;
						if (worldmodel) *worldmodel->ModelIndex() = iHuntsman + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 509;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_tactical";
						killIcons["knife_t"] = "knife_tactical";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 559; // Lore
						}
					}
					else if (Model == 7) // Karambit
					{
						int iKarambit = g_ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
						*pWeapon->ModelIndex() = iKarambit; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iKarambit;
						if (worldmodel) *worldmodel->ModelIndex() = iKarambit + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 507;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_karambit";
						killIcons["knife_t"] = "knife_karambit";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 570; // Doppler Phase 4
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 568; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 561; // Lore
						}
					}
					else if (Model == 8) // M9 Bayonet
					{
						int iM9Bayonet = g_ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
						*pWeapon->ModelIndex() = iM9Bayonet; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iM9Bayonet;
						if (worldmodel) *worldmodel->ModelIndex() = iM9Bayonet + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 508;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_m9_bayonet";
						killIcons["knife_t"] = "knife_m9_bayonet";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 0; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 570; // Doppler Phase 4
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 568; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 562; // Lore
						}
					}
					else if (Model == 9) // Shadow Daggers
					{
						int iDagger = g_ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
						*pWeapon->ModelIndex() = iDagger; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iDagger;
						if (worldmodel) *worldmodel->ModelIndex() = iDagger + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 516;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife_push";
						killIcons["knife_t"] = "knife_push";
						int Skin = g_Options.Skinchanger.KnifeSkin;
						if (Skin == 0)
						{
							*pWeapon->FallbackPaintKit() = 5; // Forest DDPAT
						}
						else if (Skin == 1)
						{
							*pWeapon->FallbackPaintKit() = 12; // Crimson Web
						}
						else if (Skin == 2)
						{
							*pWeapon->FallbackPaintKit() = 27; // Bone Mask
						}
						else if (Skin == 3)
						{
							*pWeapon->FallbackPaintKit() = 38; // Fade
						}
						else if (Skin == 4)
						{
							*pWeapon->FallbackPaintKit() = 40; // Night
						}
						else if (Skin == 5)
						{
							*pWeapon->FallbackPaintKit() = 42; // Blue Steel
						}
						else if (Skin == 6)
						{
							*pWeapon->FallbackPaintKit() = 43; // Stained
						}
						else if (Skin == 7)
						{
							*pWeapon->FallbackPaintKit() = 44; // Case Hardened
						}
						else if (Skin == 8)
						{
							*pWeapon->FallbackPaintKit() = 59; // Slaughter
						}
						else if (Skin == 9)
						{
							*pWeapon->FallbackPaintKit() = 72; // Safari Mesh
						}
						else if (Skin == 10)
						{
							*pWeapon->FallbackPaintKit() = 77; // Boreal Forest
						}
						else if (Skin == 11)
						{
							*pWeapon->FallbackPaintKit() = 98; // Ultraviolet
						}
						else if (Skin == 12)
						{
							*pWeapon->FallbackPaintKit() = 143; // Urban Masked
						}
						else if (Skin == 13)
						{
							*pWeapon->FallbackPaintKit() = 175; // Scorched
						}
						else if (Skin == 14)
						{
							*pWeapon->FallbackPaintKit() = 323; // Rust Coat
						}
						else if (Skin == 15)
						{
							*pWeapon->FallbackPaintKit() = 409; // Tiger Tooth
						}
						else if (Skin == 16)
						{
							*pWeapon->FallbackPaintKit() = 410; // Damascus Steel
						}
						else if (Skin == 17)
						{
							*pWeapon->FallbackPaintKit() = 411; // Damascus Steel
						}
						else if (Skin == 18)
						{
							*pWeapon->FallbackPaintKit() = 413; // Marble Fade
						}
						else if (Skin == 19)
						{
							*pWeapon->FallbackPaintKit() = 414; // Rust Coat
						}
						else if (Skin == 20)
						{
							*pWeapon->FallbackPaintKit() = 415; // Doppler Ruby
						}
						else if (Skin == 21)
						{
							*pWeapon->FallbackPaintKit() = 416; // Doppler Sapphire
						}
						else if (Skin == 22)
						{
							*pWeapon->FallbackPaintKit() = 417; // Doppler Blackpearl
						}
						else if (Skin == 23)
						{
							*pWeapon->FallbackPaintKit() = 418; // Doppler Phase 1
						}
						else if (Skin == 24)
						{
							*pWeapon->FallbackPaintKit() = 419; // Doppler Phase 2
						}
						else if (Skin == 25)
						{
							*pWeapon->FallbackPaintKit() = 420; // Doppler Phase 3
						}
						else if (Skin == 26)
						{
							*pWeapon->FallbackPaintKit() = 421; // Doppler Phase 4
						}
						else if (Skin == 27)
						{
							*pWeapon->FallbackPaintKit() = 569; // Gamma Doppler Phase1
						}
						else if (Skin == 28)
						{
							*pWeapon->FallbackPaintKit() = 570; // Gamma Doppler Phase2
						}
						else if (Skin == 29)
						{
							*pWeapon->FallbackPaintKit() = 571; // Gamma Doppler Phase3
						}
						else if (Skin == 30)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Phase4
						}
						else if (Skin == 31)
						{
							*pWeapon->FallbackPaintKit() = 568; // Gamma Doppler Emerald
						}
						else if (Skin == 32)
						{
							*pWeapon->FallbackPaintKit() = 561; // Lore
						}
					}
					else if (Model == 10) // Default
					{
						int iGunGame = g_ModelInfo->GetModelIndex("models/weapons/v_knife.mdl");
						*pWeapon->ModelIndex() = iGunGame; // m_nModelIndex
						*pWeapon->ViewModelIndex() = iGunGame;
						if (worldmodel) *worldmodel->ModelIndex() = iGunGame + 1;
						*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 42;
						*pWeapon->GetEntityQuality() = 3;
						killIcons.clear();
						killIcons["knife_default_ct"] = "knife";
						killIcons["knife_t"] = "knife";
					}
				}
				*pWeapon->OwnerXuidLow() = 0;
				*pWeapon->OwnerXuidHigh() = 0;
				*pWeapon->FallbackWear() = 0.001f;
				*pWeapon->m_AttributeManager()->m_Item()->ItemIDHigh() = 1;
			}
		}
	}
}