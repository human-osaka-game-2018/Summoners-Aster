﻿#include <Windows.h>
#include <tchar.h>

#include <GameFramework.h>

#include "SceneSwitcher.h"

using namespace gameframework;
using namespace summonersaster;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	WindowParam::SetInstanceHandle(hInst);

	//デフォルトでは1280.0f 720.0f
	WindowParam::SetWindowSize(RectSize(1600.0f, 900.0f));

	Window* pWindow = new Window(_T("Summoners'Aster"));

	//インスタンスが一つしかないものを自動開放するように登録
	SingletonHolder<Window>::Create(pWindow);

	//DirectXのデバイスを作成
	DirectXParam::Create();

	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	SceneSwitcher& sceneSwitcher = SceneSwitcher::CreateAndGetRef();

	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;

		if (!rGameFramework.CanStartNextFrame()) continue;

		rGameFramework.PrepareInFrame();
		sceneSwitcher.Update();
		sceneSwitcher.Render();

		rGameFramework.FinishInFrame();
	}
	sceneSwitcher.ReleaseInstance();
	return 0;
}
