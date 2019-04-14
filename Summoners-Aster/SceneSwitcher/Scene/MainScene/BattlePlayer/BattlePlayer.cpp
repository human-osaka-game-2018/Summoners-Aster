#include "BattlePlayer.h"

using namespace gameframework;


namespace summonersaster
{


BattlePlayer::BattlePlayer(const char* deckName):USE_DECK_NAME(deckName),m_RotationTickets(3)

{
	Initialize();
}


BattlePlayer::~BattlePlayer()
{
	Destroy();
}

void BattlePlayer::Initialize()
{

	m_pHand = new Hand();
	m_pDeck = new Deck(USE_DECK_NAME);
	m_pDeck->Load();
	m_pCemetery = new Cemetery();
	m_pHP = new HP();
	m_pMP = new MP();

	GameFrameworkFactory::Create(&m_pRect);
	m_rGameFramework.CreateTexture(_T("TEAM_LOGO"), _T("Textures/SINGULARITY.png"));
	m_rGameFramework.CreateFont(_T("INPUT_PROMPT"), RectSize(30, 50), _T("IPAex明朝"));
	m_rGameFramework.CreateFont(_T("Debug_str"), RectSize(Card::DEBUG_WORD_WIGTH*0.5, Card::DEBUG_WORD_WIGTH), _T("IPAex明朝"));

	Shuffle();
	DrawCard();
	DrawCard();
	DrawCard();

}

void BattlePlayer::Destroy()
{	
	delete m_pHand;
	delete m_pDeck;
	delete m_pCemetery;
	delete m_pHP;
	delete m_pMP;

	delete m_pRect;
	m_rGameFramework.ReleaseTexture(_T("TEAM_LOGO"));
	m_rGameFramework.ReleaseFont(_T("INPUT_PROMPT"));
	m_rGameFramework.ReleaseFont(_T("Debug_str"));

}

bool BattlePlayer::Update(const char* phase)
{
	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	if (rGameFramework.KeyboardIsPressed(DIK_G))
	{
		DrawCard();
	}
	if (rGameFramework.KeyboardIsPressed(DIK_S))
	{
		Shuffle();
	}
	if (rGameFramework.KeyboardIsPressed(DIK_M))
	{
		Mulligan();
	}
	if (rGameFramework.KeyboardIsPressed(DIK_P))
	{
		SendCardFromDeckToGraveyard();
	}
	if (rGameFramework.KeyboardIsPressed(DIK_1))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(0));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_2))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(1));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_3))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(2));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_4))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(3));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_5))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(4));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_6))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(5));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_7))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(6));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_8))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(7));
	}
	if (rGameFramework.KeyboardIsPressed(DIK_9))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(8));
	}

	return false;//仮
}

void BattlePlayer::Render()
{
	m_pRect->GetCenter() = { m_TexturCenter.x, m_TexturCenter.y, 0.0f };
	m_pRect->SetSize(RectSize(500.f, 300.f));

	m_pRect->Render(m_rGameFramework.GetTexture(_T("TEAM_LOGO")));
	
	m_pDeck->Render();
	m_pCemetery->Render();
	m_pHand->Render();
}

bool BattlePlayer::RotateField()
{
	if(0==m_RotationTickets) return false;
	--m_RotationTickets;
	return true;
}

void BattlePlayer::Damaged(unsigned int damage)
{
	m_pHP->Damaged(damage);
}
void BattlePlayer::Recover(unsigned int heal)
{
	m_pHP->Recover(heal);
}

void BattlePlayer::DrawCard()
{
	Hand::RESULT drawResult;
	if (Hand::FLOOD == (drawResult = m_pHand->AddCard(m_pDeck->SendCard())))
	{
		m_pCemetery->PreserveCard(m_pHand->SendCard(9));
	}
	if (Hand::DEAD == drawResult)
	{

	}
}

void BattlePlayer::SendCardFromHandToGraveyard(unsigned int handNum)
{
	m_pCemetery->PreserveCard(m_pHand->SendCard(handNum));
}

void BattlePlayer::SendCardFromDeckToGraveyard()
{
	m_pCemetery->PreserveCard(m_pDeck->SendCard());
}

void BattlePlayer::SendToGraveyard(Card* card)
{
	m_pCemetery->PreserveCard(card);
}

Card* BattlePlayer::SendFromHand(unsigned int handNum)
{
	return m_pHand->SendCard(handNum);
}

void BattlePlayer::Shuffle()
{
	m_pDeck->Shuffle();
}

void BattlePlayer::Mulligan()
{
	size_t handQuantities = m_pHand->GetQuantites();
	while(m_pHand->GetQuantites())
	{
		m_pDeck->AddCard(m_pHand->SendCard(0));
	}
	m_pDeck->Shuffle();
	for (int i = 0; i < handQuantities; ++i)
	{
		m_pHand->AddCard(m_pDeck->SendCard());
	}
}

}
