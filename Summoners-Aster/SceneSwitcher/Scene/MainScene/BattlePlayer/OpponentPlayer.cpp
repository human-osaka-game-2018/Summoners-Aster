#include "OpponentPlayer.h"

namespace summonersaster
{
	using namespace gameframework;

	OpponentPlayer::OpponentPlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName)
		:BattlePlayer(pPlayerTextureKey, deckName)
	{
		m_PlayerKind = PLAYER_KIND::OPPONENT;

		m_TexturCenter = { 800.0f, 55.0f };
	}

	OpponentPlayer::~OpponentPlayer()
	{

	}

	void OpponentPlayer::Initialize()
	{
		m_pHand = new Hand(PLAYER_KIND::OPPONENT, D3DXVECTOR2(100.0f, 100));
		m_pDeck = new Deck(USE_DECK_NAME, D3DXVECTOR2(1529.0f, 260.0f));
		m_pDeck->Load(PLAYER_KIND::OPPONENT);
		m_pCemetery = new Cemetery(D3DXVECTOR2(1480.0f, 370.0f));

		D3DXVECTOR2 hpPos(800.0f, 110.0f);
		m_pHP = new HP(hpPos);
		m_pRotationTickets = new RotationTickets(D3DXVECTOR2(1.9f, 0.23f));
		m_pMP = new MP(D3DXVECTOR3(1435.0f, 100.0f, 0.9f));
		m_pWeaponHolder = new WeaponHolder(D3DXVECTOR3(1.15f, 0.2f, 0.9f));

		GameFrameworkFactory::Create(&m_pRect);

		m_pDeck->Shuffle();

		m_rFollowerOrderMediator.Register(PLAYER_KIND::OPPONENT, m_pRect, m_pHP, m_pWeaponHolder);
		m_rRotationOrderMediator.Register(PLAYER_KIND::OPPONENT, m_pRotationTickets);
	}

	void OpponentPlayer::SendCardToCemetery(Card* pCard)
	{
		if (!pCard) return;

		if (pCard->Owner() != PLAYER_KIND::OPPONENT) return;

		m_pCemetery->PreserveCard(pCard);
	}
}
