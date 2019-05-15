#include "BattleStep.h"

namespace summonersaster
{
	BattleStep::BattleStep()
	{

	}

	BattleStep::~BattleStep()
	{
		m_rTurn.ReleaseInstance();
	}

	void BattleStep::Initialize()
	{
		
	}

	void BattleStep::Finalize()
	{
		
	}

	void BattleStep::Update()
	{
		m_rTurn.Update();

		if (BattleInformation::Winner() == PLAYER_KIND::NON_SELECTING) return;

		SwitchEventMediatorBase<Step>::GetRef().SendSwitchEvent(STEP_KIND::RESULT);
	}

	void BattleStep::Render()
	{
		m_rTurn.Render();
	}
} // namespace summonersaster
