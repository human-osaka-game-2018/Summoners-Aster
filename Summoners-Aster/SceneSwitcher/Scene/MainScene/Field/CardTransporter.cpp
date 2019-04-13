#include "CardTransporter.h"

using namespace gameframework;

namespace summonersaster
{
	CardTransporter::CardTransporter()
	{
		m_rField.GetFollowerZone(&m_pFollowerZone);
	}

	CardTransporter::~CardTransporter()
	{
	
	}

	void CardTransporter::Register(PLAYER_KIND playerKind, Hand* pHand, Cemetary* pCemetary, PP* pPP)
	{
		m_playersSummonData.emplace(playerKind, pHand, pCemetary, pPP);
	}

	void CardTransporter::TransportCollideFollower()
	{
		//std::vector<Card*>* pCurrentPlayerHand = m_playersSummonData[現在のプレイヤー].pHand->GetCards();
		
		//for (auto& pCard : *pCurrentPlayerHand)
		{
			//int handCardIndex = static_cast<int>(&pCard - &(*pCurrentPlayerHand)[0]);
		
			for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
			{
				if (m_pFollowerZone[fzi].m_pFollower) continue;

				if (!m_pFollowerZone[fzi].m_isOpponentZone) continue;

				//if (!Collides(pCard->GetVertices(), m_pFollowerZone[fzi].m_pVertices)) continue;
		
				//TransportFollower(handCardIndex, fzi);
		
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
			//m_playersSummonData[pCard->GetOwner()].m_pCemetary->push_back(pCard);
		}
	}

	void CardTransporter::TransportFollower(int handCardIndex, int transportFieldIndex)
	{
		//std::vector<Card*>* pCurrentPlayerHand = m_playersSummonData[現在のプレイヤー].pHand->GetCards();
		
		//Card* pTransportedCard = (*pCurrentPlayerHand)[handCardIndex];
		
		//PPがたりなかったらfalse 
		//if (!(*m_playersSummonData[現在のプレイヤー].pPP -= *pTransportedCard)) return;
		
		//m_rField.SetFollower(transportFieldIndex, pTransportedCard);
		
		//pCurrentPlayerHand->erase(pCurrentPlayerHand->begin() + handCardIndex);
		
		//pCurrentPlayerHand->shrink_to_fit();
	}
} // namespace summonersaster
