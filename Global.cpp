//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#include "SDK.h"

bool				G::Aimbotting;
bool				G::InAntiAim;
bool				G::Return;
HMODULE				G::Dll;
HWND				G::Window;
bool				G::PressedKeys[256] = {};
char				G::AnimatedClantag[16];
bool				G::d3dinit = false;
float				G::FOV;
int					G::ChamMode = -1;
bool				G::SendPacket = true;
int					G::BestTarget = -1;
char				G::buf3[128];
char				G::extra_flags;
float				G::hitmarkeralpha;

