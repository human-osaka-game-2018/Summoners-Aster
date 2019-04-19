#include "StepSwitcher.h"

namespace summonersaster
{
	StepSwitcher::~StepSwitcher()
	{

	}

	StepSwitcher::StepSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = STEP_KIND::PLAYERS_INFOMATION_RENDERING;
		CreateKindInstances();
		SwitchKind();
	}

	void StepSwitcher::CreateKindInstances()
	{
		m_kinds[STEP_KIND::PLAYERS_INFOMATION_RENDERING] = new PlayersInformationRenderingStep();
		m_kinds[STEP_KIND::BATTLE_PREPARING]			 = new BattlePreparingStep();
		m_kinds[STEP_KIND::BATTLE]						 = new BattleStep();
		m_kinds[STEP_KIND::RESULT]						 = new ResultStep();
	}
} // namespace summonersaster
