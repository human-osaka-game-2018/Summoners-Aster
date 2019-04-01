#include "SceneSwitcher.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/HomeScene/HomeScene.h"

namespace summonersaster
{
	SceneSwitcher::~SceneSwitcher()
	{

	}

	SceneSwitcher::SceneSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = _T("TITLE");
		CreateKindInstances();
		SwitchKind();
	}

	void SceneSwitcher::CreateKindInstances()
	{
		m_kinds[_T("TITLE")]  = new TitleScene();
		m_kinds[_T("HOME")]   = new HomeScene();
		/*m_pScenes[Scene::KIND::BATTLE] = new BattleScene();
		m_pScenes[Scene::KIND::RESULT] = new ResultScene();*/
	}
} // namespace summonersaster
