#include <Windows.h>
#include <tchar.h>

#include <GameFramework.h>

#include "Cursor.h"
#include "ClickEffect.h"
#include "HoldEffect.h"
#include "SummonEffect.h"
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
	int frameCount = 0;

	rGameFramework.CreateTexture(_T("キラ十字円"), _T("Textures/キラ十字円.png"));
	rGameFramework.CreateTexture(_T("カーソル"), _T("Textures/カーソル.png"));
	rGameFramework.CreateTexture(_T("中空き円"), _T("Textures/中空き円.png"));
	rGameFramework.CreateTexture(_T("キラ"), _T("Textures/キラ.png"));
	rGameFramework.CreateTexture(_T("キラ星"), _T("Textures/キラ星.png"));
	rGameFramework.CreateTexture(_T("白正方形"), _T("Textures/白正方形.png"));
	rGameFramework.CreateTexture(_T("円"), _T("Textures/円.png"));

	gameframework::Cursor cursor;

	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;

		if (!rGameFramework.CanStartNextFrame()) continue;

		rGameFramework.PrepareInFrame();

		if (rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			rGameFramework.RegisterGraphicEffect(new ClickEffect());
		}

		if (rGameFramework.MouseIsHeld(DirectX8Mouse::DIM_LEFT) && !((frameCount++) % 3))
		{
			POINT cursorPoint = { 0, 0 };
			rGameFramework.CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);
			//rGameFramework.RegisterGraphicEffect(new SummonEffect(cursorPos));

			rGameFramework.RegisterGraphicEffect(new HoldEffect());
		}

		sceneSwitcher.Update();
		sceneSwitcher.Render();

		rGameFramework.UpdateGraphicEffects();
		rGameFramework.RenderGraphicEffects();

		cursor.Update();
		cursor.Render();

		rGameFramework.FinishInFrame();
	}

	sceneSwitcher.ReleaseInstance();

	return 0;
}
