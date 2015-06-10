// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
//#define MATHFUNCSDLL_EXPORTS 1
#include "KeyboardHook.h"
HMODULE hDLLModule		= NULL;

#pragma data_seg ("Shared") 
HHOOK   hKeyboardHook = NULL;
#pragma data_seg () 



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hDLLModule = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	bool generateOriginalKeypress = false; 

	if (nCode == HC_ACTION)
	{
		if (wParam == WM_KEYDOWN){
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			printf("VK: %d \n", p->vkCode);
			keybd_event('B', 0, 0, 0);
		}
		else if (wParam == WM_KEYUP) // Keyup
		{
			keybd_event('B', 0, KEYEVENTF_KEYUP, 0);
		}
	}
	
	if (generateOriginalKeypress)
		return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
	else
		return 1;
}

bool keyboard::myKeyboard::SetHook()
{
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hDLLModule, 0);
	return (hKeyboardHook != NULL);
}

bool keyboard::myKeyboard::UnsetHook()
{
	if (!hKeyboardHook) return true;

	bool bResult = (UnhookWindowsHookEx(hKeyboardHook) != 0);
	hKeyboardHook = NULL;

	return bResult;
}