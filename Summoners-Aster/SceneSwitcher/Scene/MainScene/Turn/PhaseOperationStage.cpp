#include "PhaseOperationStage.h"

namespace summonersaster
{
	PhaseOperationStage::PhaseOperationStage()
	{
		SwitchEventMediatorBase<Phase>::GetRef().RegisterReceiver(&m_phaseSwitchEventPost);

		GameFrameworkFactory::Create(&m_pTurnPlayerStream);

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);

		m_pTurnPlayerStream->SetTopLeft(D3DXVECTOR2(windowSize.m_width * 0.8f, windowSize.m_height * 0.75f));
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

		*m_pTurnPlayerStream = gameframework::algorithm::Tertiary(BattleInformation::CurrentPlayer() == PLAYER_KIND::PROPONENT, _T("YOUR"), _T("OPPONENT`S"));
		*m_pTurnPlayerStream += _T(" TURN");

		m_pTurnPlayerStream->Flash(180, 20, 200);

		m_pTurnPlayerStream->Render(GameFramework::GetRef().GetFont(_T("CARD_M")), DT_CENTER);
	}
} // namespace summonersaster
