#include "HomeScene.h"
#include <GameFramework.h>
#include "SwitchEventMediatorBase.h"

namespace summonersaster
{
	HomeScene::HomeScene()
	{
	}

	HomeScene::~HomeScene()
	{
		m_taskScheduler.ReleaseAll();

		delete m_pMenuButton;
		delete m_pDeckButton;
		delete m_pCPUButton;
		delete m_pConnectButton;
		delete m_pMenuWindow;

		GameFramework& rGameFramework = GameFramework::GetRef();

		rGameFramework.ReleaseAllTexture();
		rGameFramework.ReleaseAllFont();

	}

	void HomeScene::Initialize()
	{
		Load();
	}

	void HomeScene::LoadResources()
	{
		m_taskScheduler.Register(new HomeBack(), 0, true);
		m_taskScheduler.Register(new PlayerName(), 0, true);
		m_taskScheduler.Register(new Player(), 0, true);
		m_pMenuButton = new MenuButton();
		m_pDeckButton = new DeckButton();
		m_pCPUButton = new CPUButton();
		m_pConnectButton = new ConnectButton();
		m_pMenuWindow = new MenuWindow();
		m_rGameFramework.LoopStart(L"HOME");
		isLoadEnd = true;

	}

	void HomeScene::Finalize()
	{
		m_rGameFramework.Stop(L"HOME");
		delete m_pMenuButton;
		m_pMenuButton = nullptr;
		delete m_pDeckButton;
		m_pDeckButton = nullptr;
		delete m_pCPUButton;
		m_pCPUButton = nullptr;
		delete m_pConnectButton;
		m_pConnectButton = nullptr;
		delete m_pMenuWindow;
		m_pMenuWindow = nullptr;

	}

	void HomeScene::Update()
	{
		m_taskScheduler.Update();
		gameframework::GameFramework& rGameFramework = gameframework::GameFramework::CreateAndGetRef();

		//if (rGameFramework.KeyboardIsPressed(DIK_D))
		//{
		//	SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::MAIN);
		//}
		//if (rGameFramework.KeyboardIsPressed(DIK_F))
		//{
		//	SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::TITLE);
		//}
		//if (rGameFramework.KeyboardIsPressed(DIK_G))
		//{
		//	SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND:: DECKEDIT);
		//}
		if (m_pConnectButton->IsClicked())
		{
			rGameFramework.OneShotStart(L"CLICK");
			HWND hwnd;
			gameframework::WindowParam::GetWindowHandle(&hwnd);

			ShowCursor(true);
			MessageBox(hwnd, _T("工事中"), _T("ERRROR"), MB_OK);
			ShowCursor(false);

			OutputDebugString(L"通信対戦\n");
		}
		if (m_pCPUButton->IsClicked())
		{
			rGameFramework.OneShotStart(L"CLICK");

			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::MAIN);
			OutputDebugString(L"CPU対戦\n");
		}
		if (m_pDeckButton->IsClicked())
		{
			rGameFramework.OneShotStart(L"CLICK");

			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::DECKEDIT);
			OutputDebugString(L"デッキ編成\n");
		}
		m_pMenuWindow->Update();
		if (m_pMenuButton->IsClicked() && !m_pMenuWindow->GetActive())
		{
			rGameFramework.OneShotStart(L"WINDOW");
			OutputDebugString(L"メニュー\n");
			m_pMenuWindow->ToggleActive();
		}
	}

	void HomeScene::Render()
	{
		m_taskScheduler.Render();
		m_pMenuButton->Render();
		m_pDeckButton->Render();
		m_pCPUButton->Render();
		m_pConnectButton->Render();
		m_pMenuWindow->Render();
	}

} // namespace summonersaster
