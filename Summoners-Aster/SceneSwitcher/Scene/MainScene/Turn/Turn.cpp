#include "Turn.h"

namespace summonersaster
{
	using namespace gameframework;

	Turn::~Turn()
	{

	}

	Turn::Turn()
	{
		m_switchEventPost.m_nextKind = m_currentKind = TURN_STAGE_KIND::UI_RENDERING;
		CreateKindInstances();
		SwitchKind();
	}

	void Turn::Update()
	{
		if (m_switchEventPost.m_shouldSwitch)
		{
			if (m_switchEventPost.m_nextKind == TURN_STAGE_KIND::UI_RENDERING)
			{
				IncrementTurn();
			}

			SwitchKind();
		}

		m_kinds[m_currentKind]->Update();
	}

	void Turn::CreateKindInstances()
	{
		m_kinds[TURN_STAGE_KIND::UI_RENDERING] = new TurnUIRenderingStage();
		m_kinds[TURN_STAGE_KIND::PHASE_OPERATION] = new PhaseOperationStage();
	}

	void Turn::IncrementTurn()
	{
		BattleInformation::CurrentPlayer(
			algorithm::Tertiary(BattleInformation::CurrentPlayer() == PLAYER_KIND::OPPONENT, PLAYER_KIND::PROPONENT, PLAYER_KIND::OPPONENT));

		if ((BattleInformation::CurrentPlayer() == BattleInformation::StartPlayer()))
		{
			++m_turnNum;

			BattleInformation::Turn(m_turnNum);
		}
	}
} // namespace summonersaster
