#include "CardTransporter.h"

using namespace gameframework;

namespace summonersaster
{
	CardTransporter::CardTransporter()
	{

	}

	CardTransporter::~CardTransporter()
	{
	
	}

	void CardTransporter::Register(PLAYER_KIND playerKind, Hand* pHand, Cemetery* pCemetary, MP* pMP)
	{
		//std::piecewise_constructはキーと値を無名の型(tuple)として与えるという宣言
		m_playersSummonData.emplace(std::piecewise_construct,
			std::forward_as_tuple(playerKind),
			std::forward_as_tuple(pHand, pCemetary, pMP));
	}

	void CardTransporter::TransportCollideFollower()
	{
		if (!GameFramework::GetRef().MouseIsReleased(DirectX8Mouse::DIM_LEFT)) return;

		m_rField.GetFollowerZone(&m_pFollowerZone);

		std::vector<MovableCard*>* pCurrentPlayerHand = m_playersSummonData[PLAYER_KIND::PROPONENT].m_pHand->GetCards();
		
		for (auto& pCard : *pCurrentPlayerHand)
		{
			int handCardIndex = static_cast<int>(&pCard - &(*pCurrentPlayerHand)[0]);
		
			for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
			{
				if (m_pFollowerZone[fzi].m_pFollower) continue;

				if (m_pFollowerZone[fzi].m_isOpponentZone) continue;

				if (!collision::Collides(pCard->HCard()->Rect(), *m_pFollowerZone[fzi].m_pVertices)) continue;
		
				TransportFollower(handCardIndex, fzi);
		
				return;
			}
		}
	}

	void CardTransporter::DestroyDeadFollower()
	{
		std::vector<Card*> pCemetary;

		m_rField.DestroyDeadFollower(&pCemetary);

		for (auto& pCard : pCemetary)
		{
			m_playersSummonData[pCard->Owner()].m_pCemetary->PreserveCard(pCard);
		}
	}

	CardTransporter::PlayerSummonData::PlayerSummonData()
	{

	}

	CardTransporter::PlayerSummonData::PlayerSummonData(Hand* pHand, Cemetery* pCemetery, MP* pMP)
		:m_pHand(pHand), m_pCemetary(pCemetery), m_pMP(pMP)
	{

	}

	void CardTransporter::TransportFollower(int handCardIndex, int transportFieldIndex)
	{
		std::vector<MovableCard*>* pCards = m_playersSummonData[PLAYER_KIND::PROPONENT].m_pHand->GetCards();

		//MPがたりなかったらfalse 
		if (!(m_playersSummonData[PLAYER_KIND::PROPONENT].m_pMP->Paid((*pCards)[handCardIndex]->HCard()->Cost()))) return;

		//handCardIndexが指し示すカードは絶対的にフォロワーでありdynamic_castは重いのでstatic_cast
		Follower* pFollower = static_cast<Follower*>(m_playersSummonData[PLAYER_KIND::PROPONENT].m_pHand->SendCard(handCardIndex));

		m_rField.SetFollower(transportFieldIndex, pFollower);
	}
} // namespace summonersaster
