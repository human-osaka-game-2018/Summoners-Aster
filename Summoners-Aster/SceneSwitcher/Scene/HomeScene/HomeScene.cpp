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
	}

	void HomeScene::Initialize()
	{
		m_taskScheduler.Register(new HomeBack(), 0, true);
		m_taskScheduler.Register(new MenuButton(), 0, true);
		m_taskScheduler.Register(new PlayerName(), 0, true);
		m_taskScheduler.Register(new ConnectButton(), 0, true);
		m_taskScheduler.Register(new DeckButton(), 0, true);
		m_taskScheduler.Register(new CPUButton(), 0, true);
		m_taskScheduler.Register(new Player(), 0, true);
	}

	void HomeScene::Finalize()
	{
		m_taskScheduler.ReleaseAll();
	}

	void HomeScene::Update()
	{
		m_taskScheduler.Update();
		gameframework::GameFramework& rGameFramework = gameframework::GameFramework::CreateAndGetRef();

		if (rGameFramework.KeyboardIsPressed(DIK_F))
		{
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(_T("TITLE"));
		}
	}

	void HomeScene::Render()
	{
		m_taskScheduler.Render();
	}

} // namespace summonersaster
