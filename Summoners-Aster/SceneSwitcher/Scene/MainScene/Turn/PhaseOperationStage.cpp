#include "PhaseOperationStage.h"

namespace summonersaster
{
	PhaseOperationStage::PhaseOperationStage()
	{
		SwitchEventMediatorBase<Phase>::GetRef().RegisterReceiver(&m_phaseSwitchEventPost);
	}

	PhaseOperationStage::~PhaseOperationStage()
	{
		SwitchEventMediatorBase<Phase>::GetRef().UnregisterReceiver(&m_phaseSwitchEventPost);
		rPhaseSwitcher.ReleaseInstance();
	}

	void PhaseOperationStage::Initialize()
	{
		
	}

	void PhaseOperationStage::Finalize()
	{
		
	}

	void PhaseOperationStage::Update()
	{
		rPhaseSwitcher.Update();

		BattleActionExecutor::Update();

		if (m_phaseSwitchEventPost.m_nextKind == _T("DRAW"))
		{
			if (!m_phaseSwitchEventPost.m_shouldSwitch) return;

			SwitchEventMediatorBase<TurnStage>::GetRef().SendSwitchEvent(TURN_STAGE_KIND::UI_RENDERING);
		}
	}

	void PhaseOperationStage::Render()
	{
		rPhaseSwitcher.Render();
	}
} // namespace summonersaster
