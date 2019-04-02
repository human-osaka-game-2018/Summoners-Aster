#include "PhaseSwitcher.h"

namespace summonersaster
{
	PhaseSwitcher::~PhaseSwitcher()
	{

	}

	PhaseSwitcher::PhaseSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = _T("DRAW");
		CreateKindInstances();
		SwitchKind();
	}

	void PhaseSwitcher::CreateKindInstances()
	{
		//m_kinds[_T("TITLE")]  = new TitleScene();
		//m_kinds[_T("HOME")]   = new HomeScene();
		/*m_pScenes[Scene::KIND::BATTLE] = new BattleScene();
		m_pScenes[Scene::KIND::RESULT] = new ResultScene();*/
	}
} // namespace summonersaster
