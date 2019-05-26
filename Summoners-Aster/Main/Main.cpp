#include <Windows.h>
#include <tchar.h>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <GameFramework.h>

#include "Cursor.h"
#include "ClickEffect.h"
#include "HoldEffect.h"
#include "SummonEffect.h"
#include "SceneSwitcher.h"
#include "MovingEffect.h"

using namespace gameframework;
using namespace summonersaster;

void SoundsLoad();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	WindowParam::SetInstanceHandle(hInst);

	//デフォルトでは1280.0f 720.0f
	WindowParam::SetWindowSize(RectSize(1600.0f, 900.0f));

	Window* pWindow = new Window(_T("Summoners'Aster"));

	//インスタンスが一つしかないものを自動開放するように登録
	SingletonHolder<Window>::Create(pWindow);

	//DirectXのデバイスを作成
	DirectXParam::Create();

	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	SoundsLoad();

	rGameFramework.CreateTexture(_T("キラ十字円"), _T("Textures/キラ十字円.png"));
	rGameFramework.CreateTexture(_T("キラ十字"), _T("Textures/キラ十字.png"));
	rGameFramework.CreateTexture(_T("キラ十字不透明"), _T("Textures/キラ十字不透明.png"));
	rGameFramework.CreateTexture(_T("カーソル"), _T("Textures/カーソル.png"));
	rGameFramework.CreateTexture(_T("中空き円"), _T("Textures/中空き円.png"));
	rGameFramework.CreateTexture(_T("中空き円不透明"), _T("Textures/中空き円不透明.png"));
	rGameFramework.CreateTexture(_T("キラ"), _T("Textures/キラ.png"));
	rGameFramework.CreateTexture(_T("キラ不透明"), _T("Textures/キラ不透明.png"));
	rGameFramework.CreateTexture(_T("キラ星"), _T("Textures/キラ星.png"));
	rGameFramework.CreateTexture(_T("白正方形"), _T("Textures/白正方形.png"));
	rGameFramework.CreateTexture(_T("円"), _T("Textures/円.png"));
	SceneSwitcher& sceneSwitcher = SceneSwitcher::CreateAndGetRef();
	int frameCount = 0;


	gameframework::Cursor cursor;
	
	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;

		if (!rGameFramework.CanStartNextFrame()) continue;

		rGameFramework.PrepareInFrame();

		POINT cursorPoint = { 0, 0 };
		rGameFramework.CursorPos(&cursorPoint);

		if (rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			rGameFramework.RegisterGraphicEffect(new ClickEffect());
			//POINT cursorPoint = { 0, 0 };
			//rGameFramework.CursorPos(&cursorPoint);
			//D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);

			//rGameFramework.RegisterGraphicEffect(new MovingEffect(cursorPos, cursorPos + D3DXVECTOR3(500.0f, 0.0f, 0.0f), 30));
		}

		if (rGameFramework.MouseIsHeld(DirectX8Mouse::DIM_LEFT) && !((frameCount++) % 3))
		{
			POINT cursorPoint = { 0, 0 };
			rGameFramework.CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);

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

void SoundsLoad()
{
	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	rGameFramework.AddFile(L"Sounds/card-shuffle2.mp3", L"SHUFFLE", Sound::SE);
	rGameFramework.AddFile(L"Sounds/card-turn-over1.mp3", L"DRAW", Sound::SE);
	rGameFramework.AddFile(L"Sounds/magic-cure4.mp3", L"HOLY", Sound::SE);
	rGameFramework.AddFile(L"Sounds/magic-worp1.mp3", L"MOVE", Sound::SE);
	rGameFramework.AddSimultaneousFile(L"Sounds/shakin2.mp3", L"ATTACK", Sound::SE);
	rGameFramework.AddFile(L"Sounds/card-pick1.mp3", L"PICK_CARD", Sound::SE);
	rGameFramework.AddFile(L"Sounds/magic04.mp3", L"MAGIC", Sound::SE);
	rGameFramework.AddSimultaneousFile(L"Sounds/battle-start.wav", L"SUMMON", Sound::SE);
	rGameFramework.AddFile(L"Sounds/soubi-01.wav", L"ARMED", Sound::SE);
	rGameFramework.AddFile(L"Sounds/game_explosion3.mp3", L"DAMAGE", Sound::SE);
	rGameFramework.AddFile(L"Sounds/pasin.mp3", L"ERASE_FOLLOWER", Sound::SE);
	rGameFramework.AddFile(L"Sounds/error1.wav", L"ERROR", Sound::SE);
	rGameFramework.AddFile(L"Sounds/栄光のファンファーレ.mp3", L"WIN", Sound::SE);
	rGameFramework.AddFile(L"Sounds/st019.mp3", L"LOSE", Sound::SE);
	rGameFramework.AddFile(L"Sounds/ta_ta_return02 (audio-cutter.com).mp3", L"ROTATE", Sound::SE);
	rGameFramework.AddFile(L"Sounds/ta_ta_kira10.mp3", L"CLICK", Sound::SE);
	rGameFramework.AddFile(L"Sounds/ta_ta_kira06.mp3", L"WINDOW", Sound::SE);
	rGameFramework.AddFile(L"Sounds/se_maoudamashii_element_fire01.mp3", L"TURNEND", Sound::SE);
	rGameFramework.AddSimultaneousFile(L"Sounds/magic-attack-holy1.mp3", L"ABILITY", Sound::SE);

	rGameFramework.AddFile(L"Sounds/loop_136_short.wav", L"BATTLE", Sound::BGM);
	rGameFramework.AddFile(L"Sounds/loop_74.wav", L"EDIT", Sound::BGM);
	rGameFramework.AddFile(L"Sounds/loop_95.wav", L"HOME", Sound::BGM);
	rGameFramework.AddFile(L"Sounds/星間宇宙.mp3", L"TITLE", Sound::BGM);

	rGameFramework.SetVolume(50, Sound::BGM);
	rGameFramework.SetVolume(100, L"TITLE");

}
