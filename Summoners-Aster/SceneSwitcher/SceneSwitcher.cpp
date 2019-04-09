#include "SceneSwitcher.h"

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
		m_kinds[_T("MAIN")]   = new MainScene();
		//m_pScenes[Scene::KIND::RESULT] = new ResultScene();
	}
} // namespace summonersaster
