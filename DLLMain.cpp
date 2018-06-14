//Project Aurora 
//Developed by: 0xAC1D and GhostDog

#include "Interfaces.h"
#include "Hooks.h"
#include "Render.h"
#include "SDK.h"

#include "recvproxy.h"
#include "Misc.h"
#include <TlHelp32.h>


bool unload;

UCHAR
szFileSys[255],
szVolNameBuff[255];

DWORD
dwMFL,
dwSysFlags,
dwSerial;

//define Users HWID

#define ghostdog (-1908538499)
#define OxAC1D (-1742967127)
#define blaze (-1138687643)
#define mercy (-1830322695)
#define razzer (571389901)
#define weebie (2082839291)
#define west (-297806002)
#define vizikk (-2132616487)
#define wize (2081698601)

bool on_dll_detach()
{
	UnloadProxy();
	hooks::cleanup();
	return 1;
}


DWORD GetProcessId(LPCTSTR name)
{

	PROCESSENTRY32 pe32;
	HANDLE snapshot = NULL;
	DWORD pid = 0;

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &pe32)) {
			do {
				std::string sName = pe32.szExeFile;
				std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);

				if (!lstrcmp(sName.c_str(), name)) {
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &pe32));
		}

		CloseHandle(snapshot);
	}

	return pid;
}

void CheckDebugger()
{
	std::vector<std::string> m_processList;
	m_processList.push_back(XorStr("ollydbg.exe"));
	m_processList.push_back(XorStr("wireshark.exe"));
	m_processList.push_back(XorStr("lordpe.exe"));
	m_processList.push_back(XorStr("hookshark.exe"));
	m_processList.push_back(XorStr("idag.exe"));
	m_processList.push_back(XorStr("MPGH Virus Scan Tool v6.exe"));

	for (unsigned int ax = 0; ax < m_processList.size(); ax++)
	{
		std::string sProcess = m_processList.at(ax);
		if (GetProcessId(sProcess.c_str()) != 0)
		{
			exit(0);
		}
	}
}


bool on_dll_attach(void* base)
{
	GetVolumeInformation("C:\\", (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

	//Add UserName from #Define HWID

	if (dwSerial == OxAC1D || dwSerial == ghostdog || dwSerial == blaze || dwSerial == mercy || dwSerial == razzer || dwSerial == weebie || dwSerial == west || dwSerial == vizikk || dwSerial == wize)
	{
		CheckDebugger();

		InitialiseInterfaces();
		g_Netvars->GetNetvars();
		g_Render->SetupFonts();
		hooks::initialize();
		NetvarHook();


		while (unload == false)
		{
			Sleep(1000);
		}


		UnloadProxy();
		hooks::cleanup();

		Sleep(2000);
		FreeLibraryAndExitThread((HMODULE)base, 0);
	}
	else {
		MessageBox(0, "HWID Not Found! Please contact a developer...", "Project Aurora", MB_OK | MB_ICONERROR);
		Sleep(2000);
		exit(0);
	}
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_    LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return on_dll_detach();
	}
	return TRUE;
}


