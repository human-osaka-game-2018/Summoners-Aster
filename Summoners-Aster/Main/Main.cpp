﻿#include <Windows.h>
#include <tchar.h>

#include <Window/WindowParam.h>
#include <Window/Window.h>

using WindowParam = gameframework::WindowParam;
using Window = gameframework::Window;
using RectSize = gameframework::RectSize;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	WindowParam::SetInstanceHandle(hInst);

	//デフォルトでは1280.0f 720.0f
	WindowParam::SetWindowSize(RectSize(1920.0f, 1080.0f));

	Window* pWindow = new Window(_T("Summoners'Aster"));

	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;
	}

	delete pWindow;

	return 0;
}