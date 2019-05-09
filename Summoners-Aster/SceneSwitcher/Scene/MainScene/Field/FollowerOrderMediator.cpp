#include "FollowerOrderMediator.h"

using namespace gameframework;

namespace summonersaster
{
	FollowerOrderMediator::FollowerOrderMediator()
	{
		
	}

	FollowerOrderMediator::~FollowerOrderMediator()
	{

	}

	void FollowerOrderMediator::Register(PLAYER_KIND PlayerKind, Vertices* pPlayerIconVertices, HP* pHP)
	{
		m_playersAttackData.emplace(std::piecewise_construct,
			std::forward_as_tuple(PlayerKind),
			std::forward_as_tuple(pPlayerIconVertices, pHP));
	}

	void FollowerOrderMediator::ProcessFollowerOrders()
	{
		if (BattleInformation::IsWaitingAction()) return;

		m_rField.GetFollowerZone(&m_pFollowerZone);

		if (m_rGameFramework.MouseIsPressed(gameframework::DirectX8Mouse::DIM_RIGHT))
		{
			ActivateAbirity();

			return;
		}

		if (m_rGameFramework.MouseIsPressed(gameframework::DirectX8Mouse::DIM_LEFT))
		{
			SetIsSelectedAndAttackOrMove();

			return;
		}
	}

	bool FollowerOrderMediator::UpdateAttackingPlayerRoutine()
	{
		static bool isRoutineStart = true;

		PLAYER_KIND notCurrentPlayer =
			algorithm::Tertiary(BattleInformation::CurrentPlayer() ==
				PLAYER_KIND::OPPONENT, PLAYER_KIND::PROPONENT, PLAYER_KIND::OPPONENT);

		if (isRoutineStart)
		{
			FollowerData* pFollowerDatas = nullptr;
			m_rField.GetFollowerZone(&pFollowerDatas);

			m_rGameFramework.RegisterGraphicEffect(
				new AttackEffect(pFollowerDatas[m_attackingFollowerIndex].m_pVertices->GetCenter(),
					m_playersAttackData[notCurrentPlayer].m_pPlayerIconVertices->GetCenter(),
					ATTACK_EFFECT_TAKES_FRAMES));

			m_attackEffectFramesLeft = ATTACK_EFFECT_TAKES_FRAMES + ATTACK_EFFECT_SPACE_TAKES_FRAMES;

			isRoutineStart = false;
		}

		if (m_attackEffectFramesLeft-- > 0) return false;

		//現在のプレイヤーじゃないほう
		m_rField.AttackPlayer(m_attackingFollowerIndex, m_playersAttackData[notCurrentPlayer].m_pHP);

		return isRoutineStart = true;
	}

	FollowerOrderMediator::PlayerAttackData::PlayerAttackData()
	{

	}

	FollowerOrderMediator::PlayerAttackData::PlayerAttackData(Vertices* pVertices, HP* pHP)
		:m_pPlayerIconVertices(pVertices), m_pHP(pHP)
	{

	}

	int FollowerOrderMediator::GetFieldFollowerIndexCursorRidden()
	{
		for (int i = 0; i < m_rField.FIELD_FOLLOWERS_NUM; ++i)
		{
			//フォロワー配置ゾーンをクリックしていない 他ゾーンを確認
			if (!m_rGameFramework.IsCursorOnRect(*m_pFollowerZone[i].m_pVertices)) continue;

			return i;
		}

		return -1;
	}

	void FollowerOrderMediator::ActivateAbirity()
	{
		int index = GetFieldFollowerIndexCursorRidden();

		if (index < 0) return;

		if (!m_pFollowerZone[index].m_pFollower) return;

		//現在のプレイヤーじゃなかったら
		if (m_pFollowerZone[index].m_pFollower->Owner() != BattleInformation::CurrentPlayer()) return;

		m_rField.ActivateAbirity(index);
	}

	void FollowerOrderMediator::SetIsSelectedAndAttackOrMove()
	{
		if (BattleInformation::IsWaitingAction()) return;

		int index = GetFieldFollowerIndexCursorRidden();

		if (index < 0)
		{
			ActivateAttackingPlayer();

			NeutralizeSelecting();

			return;
		}

		if (m_pFollowerZone[index].m_pFollower)
		{
			//現在のプレイヤーだったら
			if (m_pFollowerZone[index].m_pFollower->Owner() == BattleInformation::CurrentPlayer())
			{
				SetIsSelected(&m_pFollowerZone[index]);

				return;
			}
		}

		//現状何も選ばれていなかった場合 この後の処理は行えないので終了
		if (!IsSelected()) return;

		int selectedIndex = GetSelectingFollowerIndex();

		m_rField.AttackOrMove(selectedIndex, index);

		//攻撃か移動が行われたので選択を解除するため
		NeutralizeSelecting();
	}

	void FollowerOrderMediator::ActivateAttackingPlayer()
	{
		PLAYER_KIND notCurrentPlayer = 
			algorithm::Tertiary(BattleInformation::CurrentPlayer() == 
				PLAYER_KIND::OPPONENT, PLAYER_KIND::PROPONENT, PLAYER_KIND::OPPONENT);

		//現在のプレイヤーじゃないほう
		Vertices* pNextTurnPlayer = m_playersAttackData[notCurrentPlayer].m_pPlayerIconVertices;
		
		if (!IsSelected())return;
		
		if (!m_rGameFramework.IsCursorOnRect(*pNextTurnPlayer)) return;

		if (!m_rField.CanTakeAction(GetSelectingFollowerIndex())) return;

		m_attackingFollowerIndex = GetSelectingFollowerIndex();

		BattleInformation::PushQueBack(ActionInformation(BattleInformation::ACTION_KIND::ATTACKING_PLAYER,
			BattleInformation::CurrentPlayer()));
	}

	bool FollowerOrderMediator::IsSelected()
	{
		for (int i = 0; i < m_rField.FIELD_FOLLOWERS_NUM; ++i)
		{
			if (m_pFollowerZone[i].m_isSelected) return true;
		}

		return false;
	}

	void FollowerOrderMediator::SetIsSelected(FollowerData* pSelectedData)
	{
		if (pSelectedData->m_isSelected)
		{
			pSelectedData->m_isSelected = false;

			return;
		}

		NeutralizeSelecting();
		pSelectedData->m_isSelected = true;
	}

	void FollowerOrderMediator::NeutralizeSelecting()
	{
		for (int i = 0; i < m_rField.FIELD_FOLLOWERS_NUM; ++i)
		{
			m_pFollowerZone[i].m_isSelected = false;
		}
	}

	int FollowerOrderMediator::GetSelectingFollowerIndex()
	{
		for (int i = 0; i < m_rField.FIELD_FOLLOWERS_NUM; ++i)
		{
			if (m_pFollowerZone[i].m_isSelected) return i;
		}

		return -1;
	}
} // namespace summonersaster
