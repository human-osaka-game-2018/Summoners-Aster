#include "StepSwitcher.h"

namespace summonersaster
{
	StepSwitcher::~StepSwitcher()
	{

	}

	StepSwitcher::StepSwitcher()
	{
		m_switchEventPost.m_nextKind = m_currentKind = _T("PLAYERS_INFOMATION_RENDERING_STEP");
		CreateKindInstances();
		SwitchKind();
	}

	void StepSwitcher::CreateKindInstances()
	{
		m_kinds[_T("PLAYERS_INFOMATION_RENDERING_STEP")] = new PlayersInformationRenderingStep();
		m_kinds[_T("BATTLE_PREPARING_STEP")]			 = new BattlePreparingStep();
		m_kinds[_T("BATTLE_STEP")]						 = new BattleStep(); 
		m_kinds[_T("RESULT_STEP")]						 = new ResultStep();
	}
} // namespace summonersaster
