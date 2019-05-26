#include "SceneSwitcher.h"

namespace summonersaster
{
	SceneSwitcher::~SceneSwitcher()
	{
		GameFramework& rGameFramework = GameFramework::GetRef();

		rGameFramework.ReleaseAllTexture();
		rGameFramework.ReleaseAllFont();

	}

	SceneSwitcher::SceneSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = SCENE_KIND::TITLE;
		CreateKindInstances();
		SwitchKind();
	}

	void SceneSwitcher::CreateKindInstances()
	{
		m_kinds[SCENE_KIND::TITLE]  = new TitleScene();
		m_kinds[SCENE_KIND::HOME]   = new HomeScene();
		m_kinds[SCENE_KIND::MAIN]   = new MainScene();
		m_kinds[SCENE_KIND::DECKEDIT] = new DeckEditScene();
		m_kinds[SCENE_KIND::CARDSHOW] = new CardShow();

	}
} // namespace summonersaster
