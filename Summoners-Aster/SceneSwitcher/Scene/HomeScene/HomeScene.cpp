#include "HomeScene.h"

namespace summonersaster
{
	HomeScene::HomeScene()
	{
		Initialize();
	}

	HomeScene::~HomeScene()
	{
		Finalize();
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
	}

	void HomeScene::Render()
	{
		m_taskScheduler.Render();
	}

} // namespace summonersaster
