#include "TitleScene.h"

namespace summonersaster
{
	TitleScene::TitleScene()
	{

	}

	TitleScene::~TitleScene()
	{

	}

	void TitleScene::Initialize()
	{
		m_taskScheduler.Register(new TeamLogo(), 0);
		m_taskScheduler.Register(new TitleBack(), 0, true);
		m_taskScheduler.Register(new GameTitle(), 0, true);
		m_taskScheduler.Register(new GameTitleStar(), 0, true);
		m_taskScheduler.Register(new InputPrompt(), 0, true);
	}

	void TitleScene::Finalize()
	{
		m_taskScheduler.ReleaseAll();
	}

	void TitleScene::Update()
	{
		m_taskScheduler.Update();
	}

	void TitleScene::Render()
	{
		m_taskScheduler.Render();
	}

} // namespace summonersaster
