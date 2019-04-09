#include "CardTransporter.h"

using namespace gameframework;

namespace summonersaster
{
	CardTransporter::CardTransporter()
	{
		Vertices** m_pFollowerZones = new Vertices*[m_rField.FIELD_FOLLOWERS_NUM];
	}

	CardTransporter::~CardTransporter()
	{
		delete[] m_pFollowerZones;
	}

	void CardTransporter::Register(Hand* pHand, PP* pPP, const TCHAR* pKey)
	{
		m_pHands.emplace(pKey, pHand, pPP);
	}

	void CardTransporter::TransportCollideFollower()
	{
		//m_rField.GetFollowerZones(m_pFollowerZones);
		//
		//std::vector<Card*>* pCurrentPlayerHand = m_pHands[現在のプレイヤー].pHand->GetHand();
		//
		//for (auto& pCard : *pCurrentPlayerHand)
		//{
		//	int handCardIndex = static_cast<int>(&pCard - &(*pCurrentPlayerHand)[0]);
		//
		//	for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
		//	{
		//		if (!m_pFollowerZones[fzi]) continue;
		//
		//		if (!Collides(pCard->GetVertices(), m_pFollowerZones[fzi])) continue;
		//
		//		TransportFollower(handCardIndex, fzi);
		//
		//		return;
		//	}
		//}
	}

	void CardTransporter::TransportFollower(int handCardIndex, int transportFieldIndex)
	{
		//std::vector<Card*>* pCurrentPlayerHand = m_pHands[現在のプレイヤー].pHand->GetHand();
		//
		//Card* pTransportedCard = (*pCurrentPlayerHand)[handCardIndex];
		//
		////PPがたりなかったらfalse 
		//if (!(*(m_pHands[現在のプレイヤー].pPP) -= *pTransportedCard)) return;
		//
		//m_rField.SetFollower(transportFieldIndex, pTransportedCard);
		//
		//pCurrentPlayerHand->erase(pCurrentPlayerHand->begin() + handCardIndex);
		//
		//pCurrentPlayerHand->shrink_to_fit();
	}
}