#include "EndPhase.h"

namespace summonersaster
{
	EndPhase::EndPhase()
	{

	}

	EndPhase::~EndPhase()
	{

	}

	void EndPhase::Initialize()
	{
		
	}

	void EndPhase::Finalize()
	{
		
	}

	void EndPhase::Update()
	{
		if (m_rPlayer.Update(PHASE_KIND::END))
		{
			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::DRAW);
			SwitchEventMediatorBase<TurnStage>::GetRef().SendSwitchEvent(TURN_STAGE_KIND::UI_RENDERING);

			m_rRotationOrderMediator.FinalizeInEndPhaseEnd();
			m_rField.FinalizeInEndPhaseEnd();
		}
	}

	void EndPhase::Render()
	{
		m_rField.Render();
		m_rPlayer.Render();
		m_rRotationOrderMediator.Render(false);
	}
} // namespace summonersaster
