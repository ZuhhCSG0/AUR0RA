//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#pragma once

extern void RenderInterface();

struct Variables
{
	Variables()
	{

	}

	struct Ragebot_s
	{
		
		bool MainSwitch;
		bool 	Enabled;
		bool 	AutoFire;
		float 	FOV;
		bool 	Silent;
		bool AutoPistol;
		int KeyPress;
		bool AimStep;
		

			bool	EnabledAntiAim;
			int		Pitch;
			int		YawTrue;
			int		YawFake;
			bool	AtTarget;
			bool	Edge;
			bool KnifeAA;


			bool FriendlyFire;
			int		Hitbox;
			int		Hitscan;
			float Pointscale;
			bool Multipoint;
			float Multipoints;


			bool AntiRecoil;
			bool AutoWall;
			bool AutoStop;
			bool AutoCrouch;
			bool AutoScope;
			float MinimumDamage;
			bool Hitchance;
			float HitchanceAmount;
			bool rizolver;
			bool FakeLagFix;
			bool playerlist;
            int BAIMkey;
	} Ragebot;

	struct
	{
		bool drawFov;
		bool EnableLegitAA;
		float AAAngle;
		bool ManualAA;
		int Up = 1;
		int Down = 1;
		int Left = 1;
		int Right = 1;
		int AALeft;
		int AARight;
		int AABack;
		int AADisabled;
		bool MainSwitch;
        bool backtrack;
		float backtrackTicks;
		bool AutoPistol;
		
		struct
		{
			bool 	Enabled;
			bool AutoPistol;
			bool	rizolver;
            
		} Aimbot;


			int MainKey = 1;
            float MainSmooth;
			float Mainfov;
            float main_random_smooth;
            float main_recoil_min;
            float main_recoil_max;
            float main_randomized_angle;



			int PistolKey = 6;
			float Pistolfov;
			float PistolSmooth;
            float pistol_random_smooth;
            float pistol_recoil_min;
            float pistol_recoil_max;
            float pistol_randomized_angle;



			int SniperKey = 6;
			float Sniperfov;
			float SniperSmooth;
            float sniper_random_smooth;
            float sniper_recoil_min;
            float sniper_recoil_max;
            float sniper_randomized_angle;
			
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			}Filter;

		struct
		{
			bool	Enabled;
			float Delay;
			int Key = 6;
			float hitchance;
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			} Filter;

		} Triggerbot;

	} Legitbot;

	struct 
	{
		
		bool 	Enabled;
		bool AAIndicator;
		bool Box;
		bool Name;
		bool HP;
		bool Weapon;
		bool Info;
		bool Chams;
		bool Skeleton;
		bool DrawSkeleton;
		bool AimSpot;
		bool DLight;
		bool SpreadCrosshair;
		bool GrenadeESP;
		bool C4;
		bool backtrackline;
		int ESPKey;
		bool RecoilCrosshair;
		bool Glow;
		bool IsScoped;
		bool HasDefuser;
		bool NoVisualRecoil;
		int Hands;
		int Weapons;
		float FOVChanger;
		float viewmodelChanger;
		bool NoFlash;
		bool NoSmoke;
		int TPKey;
		float tpdist = 200;
		bool ThirdPerson;
		int antiaim_thirdperson_angle;
		bool Time;
		bool Flashed;
		bool money;
		bool C4World;
		bool C4Worldwicon;
		bool WeaponsWorld;
		bool WeaponsWorldicon;
		bool noscopeborder;
		bool GrenadePrediction;


		bool handcham;
		bool weaponviewcham;
		int chamhandalpha;

		int weaponmat;
		int handmat;
		int weaponhandalpha;

		int matierial;
		bool outline;
		bool Teamchams;
		int champlayeralpha;

		bool Chamweapon;
		bool XQZ;

		int HitmarkerSound;

		bool DrawAwall;

		bool glowplayer;
		int playerglowalpha;
		bool teamglow;

		bool weaponglow;
		int weaponglowalpha;

		bool bombglow;
		int bombglowalpha;



		struct
		{
			bool Players;
			bool EnemyOnly;
		} Filter;

		struct
		{
			bool Players;
			bool EnemyOnly;
			bool Weapons;
			bool DynamicBox;


		} GlowFilter;

	} Visuals;

	struct misc_s
	{
		bool BuyLog;
		bool inventoryalwayson;
        bool silentstealer;
        int ragequit;
		bool 	Bhop;
		bool 	AutoStrafe;
		float MinVel;
		bool Radar;
		int		AirStuckKey;
		int lagexploit;
		int lagexploitmultiplier = 3;
		float lagexploitvalue;
		float FakeLag;
		bool AdaptiveFakeLag;
        bool nightMode;
		int NameSpammer;
		bool NameChangerFix;
		bool NoName;
		int		ChatSpamMode;
		bool ClantagChanger;
		int ClanTagSpeed;
        bool syncclantag;
		bool SpecList;
		bool FPSBooster;
		int SkyBoxChanger;
        bool namespam;
        int spammer;
		int AutoDefuse;
		bool Spam;
		bool isRecording;
		bool isReplaying;
		bool RecordPath;
		bool AutoAccept;
		bool SpoofConfirmation = false;
		bool animatedclantag = false;
		int customtab;
		bool fps;
		bool ServerRankRevealAll;
        bool niggatest;
		bool Hitmarker;
		int hitsound;
		int HitMarkerColor;
		bool Watermark;
		bool AAIndicator;
		int Skybox;
		int CurrentSky;
		bool bought;

		bool Gray;
		bool crack;
		bool chromatic;
	} Misc;
	struct
	{
		bool Enabled;
		//knife
		int Knife;
		int KnifeSkin;
		//gloves
		int gloves;
		//Pistols
		int uspskin;
		int p2000skin;
		int glock18skin;
		int dualskin;
		int p250skin;
		int cz75skin;
		int five7skin;
		int tec9skin;
		int deagleskin;
		int revolverskin;
		//MP's
		int mp9skin;
		int mac10skin;
		int mp7skin;
		int ump45skin;
		int ppbizonskin;
		int p90skin;
		//Heavies
		int novaskin;
		int xm1014skin;
		int mag7skin;
		int sawedoffskin;
		int m249skin;
		int negevskin;
		//Rifles
		int famasskin;
		int galilskin;
		int m4a4skin;
		int m4a1skin;
		int	ak47skin;
		int augskin;
		int sg553skin;
		//Snipers
		int ssg08skin;
		int awpskin;
		int scar20skin;
		int g3sg1skin;

	} Skinchanger;

	struct
	{
		bool	Opened = true;
		int 	Key;
		bool	Ragebot = false;
		bool	Legitbot = false;
		bool	Visual = false;
		bool	Misc = false;
		int		ConfigFile = 0;
		int		Theme = 0;
		bool	Colors = false;
		int     menu_hitbox_select;
	} Menu;

	struct
	{
		float TeamESP[3] = { 0, 1.f, 0 };
		float EnemyESP[3] = { 1.f, 0, 0 };
		float TeamDLights[3] = { 1.f, 0.92f, 0.23f };
		float EnemyDLights[3] = { 1.f, 0.92f, 0.23f };
		float EnemyGlow[3] = { 1.f, 0, 0 };
		float TeamGlow[3] = { 0, 1.f, 0 };
		float WeaponGlow[3] = { 1.f, 0.92f, 0.23f };
		float C4glow[3] = { 0.96f, 0.26f, 0.21f };
		float EnemyChamsVis[3] = { 0.96f, 0.26f, 0.21f };
		float EnemyChamsNVis[3] = { 1.f, 0.92f, 0.23f };
		float TeamChamsVis[3] = { 0.30f, 0.69f, 0.31f };
		float TeamChamsNVis[3] = { 0.01f, 0.66f, 0.96f };
		float WeaponCham[3] = { 1.f, 0, 0 };
		float HandCham[3] = { 1.f, 0, 0 };
		float WeaponViewCham[3] = { 1.f, 0, 0 };
		float hands_color[3] = { 1.f, 0, 0 };
		float hands_alpha;
		float tracer_color[3] = { 0.96f, 0.26f, 0.21f };
		float box_color_t[3] = { 1.f, 0, 0 };
		float box_color_ct[3] = { 1.f, 0, 0 };
		float color_skeleton[3] = { 0.98f, 0.98f, 0.98f };
		float color_spread[3] = { 0, 1.f, 0 };
		float color_recoil[3] = { 0.96f, 0.26f, 0.21f };
		float dlight_color[3] = { 1.f, 0.92f, 0.23f };
		float hitmark_color[3] = { 0.98f, 0.98f, 0.98f };
		float backtrackdots_color[3] = { 1.f, 0.92f, 0.23f };
		float window_bg[3] = { 0.15f, 0.14f, 0.15f };


	}Colors;
};

extern Variables g_Options;