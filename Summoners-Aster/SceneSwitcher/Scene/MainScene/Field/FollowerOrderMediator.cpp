#include "FollowerOrderMediator.h"

using namespace gameframework;

namespace summonersaster
{
	FollowerOrderMediator::FollowerOrderMediator()
	{
		m_rField.GetFollowerZone(&m_pFollowerZone);
	}

	FollowerOrderMediator::~FollowerOrderMediator()
	{

	}

	void FollowerOrderMediator::Register(PLAYER_KIND PlayerKind, Vertices* pPlayerIconVertices, HP* pHP)
	{
		m_playersAttackData.emplace(PlayerKind, pPlayerIconVertices, pHP);
	}

	void FollowerOrderMediator::ProcessFollowerOrders()
	{
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

	int FollowerOrderMediator::GetFieldFollowerIndexCursorRidden()
	{
		for (int i = 0; i < m_rField.FIELD_FOLLOWERS_NUM; ++i)
		{
			//フォロワー配置ゾーンをクリックしていない 他ゾーンを確認
			if (m_rGameFramework.IsCursorOnRect(*m_pFollowerZone[i].m_pVertices)) continue;

			return i;
		}

		return -1;
	}

	void FollowerOrderMediator::ActivateAbirity()
	{
		int index = GetFieldFollowerIndexCursorRidden();

		if (index < 0) return;

		if (!m_pFollowerZone[index].m_pFollower) return;

		//if (!m_pFollowerZone[index].m_pFollower->GetOwner() == 現在のプレイヤーじゃないほう) return;

		m_rField.ActivateAbirity(index);
	}

	void FollowerOrderMediator::SetIsSelectedAndAttackOrMove()
	{
		int index = GetFieldFollowerIndexCursorRidden();

		if (index < 0)
		{
			AttackPlayer();

			NeutralizeSelecting();

			return;
		}

		if (m_pFollowerZone[index].m_pFollower)
		{
			//if (m_pFollowerZone[index].m_pFollower->GetOwner() == 現在のプレイヤー)
			{
				SetIsSelected(m_pFollowerZone);

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

	void FollowerOrderMediator::AttackPlayer()
	{
		//Vertices* pNextTurnPlayer = m_playersAttackData[現在のプレイヤーじゃないほう].m_pPlayerIconVertices;
		//
		//if (!IsSelected())return;
		//
		//if (!m_rGameFramework.IsCursorOnRect(*pNextTurnPlayer)) return;

		//m_rField.AttackPlayer(pNextTurnPlayer[現在のプレイヤーじゃないほう].m_pHP);
		NeutralizeSelecting();
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
