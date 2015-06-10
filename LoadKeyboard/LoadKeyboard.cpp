// LoadKeyboard.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "KeyboardHook.h" 
#pragma comment(lib, "KeyboardHook.lib")

int _tmain(int argc, _TCHAR* argv[])
{
		MSG msg;

		if (keyboard::myKeyboard::SetHook()) printf("Hooked.\n"); else printf("Failed to hook");

		while (GetMessage(&msg, NULL, NULL, NULL)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		printf("Unhooking...");
		keyboard::myKeyboard::UnsetHook();
		return 0;

}

