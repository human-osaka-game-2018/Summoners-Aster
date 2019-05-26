#include "TitleScene.h"

#include <GameFramework.h>

#include "SwitchEventMediatorBase.h"

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
		Load();
	}

	void TitleScene::Finalize()
	{
		m_rGameFramework.Stop(L"TITLE");
		m_taskScheduler.ReleaseAll();
	}

	void TitleScene::LoadResources()
	{
		m_taskScheduler.Register(new TeamLogo(), 0);
		m_taskScheduler.Register(new TitleBack(), 0, true);
		m_taskScheduler.Register(new GameTitle(), 0, true);
		m_taskScheduler.Register(new GameTitleStar(), 0, true);
		m_taskScheduler.Register(new InputPrompt(), 0, true);
		isLoadEnd = true;

	}

	void TitleScene::Update()
	{
		m_taskScheduler.Update();

		if(m_rGameFramework.KeyboardIsPressed(DIK_P))
		{
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::CARDSHOW);
		}
	}

	void TitleScene::Render()
	{
		m_taskScheduler.Render();
	}

} // namespace summonersaster
