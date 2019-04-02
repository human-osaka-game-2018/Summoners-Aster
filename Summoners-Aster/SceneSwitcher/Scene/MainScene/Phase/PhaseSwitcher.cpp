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
		m_kinds[_T("DRAW")] = new DrawPhase();
		m_kinds[_T("MAIN")] = new MainPhase();
		m_kinds[_T("END")]  = new EndPhase();
	}
} // namespace summonersaster
