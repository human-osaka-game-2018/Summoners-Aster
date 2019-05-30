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
		m_rField.Update();

		if (m_rPlayers.Update(PHASE_KIND::END))
		{
			SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(PHASE_KIND::DRAW);
			SwitchEventMediatorBase<TurnStage>::GetRef().SendSwitchEvent(TURN_STAGE_KIND::UI_RENDERING);
			
			GameFramework& rGameFramework = GameFramework::GetRef();
			rGameFramework.OneShotStart(L"TURNEND");

			m_rRotationOrderMediator.FinalizeInEndPhaseEnd();
			m_rField.FinalizeInEndPhaseEnd();
		}

		m_rAbilityTextController.Update();
	}

	void EndPhase::Render()
	{
		m_rField.Render();
		m_rPlayers.Render();
		m_rField.RenderDummyButton();
		m_rRotationOrderMediator.Render(false);
		m_rAbilityTextController.Render();
	}
} // namespace summonersaster
