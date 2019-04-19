#include "PhaseSwitcher.h"

namespace summonersaster
{
	PhaseSwitcher::~PhaseSwitcher()
	{

	}

	PhaseSwitcher::PhaseSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = PHASE_KIND::DRAW;
		CreateKindInstances();
		SwitchKind();
	}

	void PhaseSwitcher::CreateKindInstances()
	{
		m_kinds[PHASE_KIND::DRAW] = new DrawPhase();
		m_kinds[PHASE_KIND::MAIN] = new MainPhase();
		m_kinds[PHASE_KIND::END]  = new EndPhase();
	}
} // namespace summonersaster
