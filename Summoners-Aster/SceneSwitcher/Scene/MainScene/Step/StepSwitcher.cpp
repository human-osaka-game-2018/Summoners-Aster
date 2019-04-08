#include "StepSwitcher.h"

namespace summonersaster
{
	StepSwitcher::~StepSwitcher()
	{

	}

	StepSwitcher::StepSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = _T("");
		CreateKindInstances();
		SwitchKind();
	}

	void StepSwitcher::CreateKindInstances()
	{
		//m_kinds[_T("DRAW")] = new DrawPhase();
		//m_kinds[_T("MAIN")] = new MainPhase();
		//m_kinds[_T("END")]  = new EndPhase();
	}
} // namespace summonersaster
