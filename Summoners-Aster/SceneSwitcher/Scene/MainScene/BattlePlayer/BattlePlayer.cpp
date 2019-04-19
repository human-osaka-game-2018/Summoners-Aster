#include "BattlePlayer.h"

using namespace gameframework;

namespace summonersaster
{
BattlePlayer::BattlePlayer(const tstring& deckName)
	:USE_DECK_NAME(deckName)
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
	m_pRotationTickets = new RotationTickets(3);

	GameFrameworkFactory::Create(&m_pRect);
	m_rGameFramework.CreateTexture(_T("CARD_BACK"), _T("Textures/Battle_cardBack.png"));
	m_rGameFramework.CreateFont(_T("INPUT_PROMPT"), RectSize(30, 50), _T("IPAex明朝"));

	RectSize debugFontSize;
	debugFontSize.m_width = 0.5f * (debugFontSize.m_height = 20);
	m_rGameFramework.CreateFont(_T("Debug_str"), debugFontSize, _T("IPAex明朝"));

	Shuffle();

	m_rCardTransporter.Register(PLAYER_KIND::PROPONENT, m_pHand, m_pCemetery, m_pMP);
	m_rFollowerOrderMediator.Register(PLAYER_KIND::PROPONENT, m_pRect, m_pHP);
	m_rRotationOrderMediator.Register(PLAYER_KIND::PROPONENT, m_pRotationTickets);
}

void BattlePlayer::Destroy()
{	
	delete m_pHand;
	delete m_pDeck;
	delete m_pCemetery;
	delete m_pHP;
	delete m_pMP;
	delete m_pRotationTickets;

	delete m_pRect;
	m_rGameFramework.ReleaseTexture(_T("TEAM_LOGO"));
	m_rGameFramework.ReleaseFont(_T("INPUT_PROMPT"));
	m_rGameFramework.ReleaseFont(_T("Debug_str"));
}

bool BattlePlayer::Update(const tstring& phase)
{
	if (phase == STEP_KIND::BATTLE_PREPARING) return UpdateInBattlePreparing();

	if (phase == PHASE_KIND::DRAW) return UpdateInDrawPhase();

	if (phase == PHASE_KIND::MAIN) return UpdateInMainPhase();

	m_pHand->Update();

	//GameFramework& rGameFramework = GameFramework::CreateAndGetRef();
	//if (rGameFramework.KeyboardIsPressed(DIK_G))
	//{
	//	DrawCard();
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_S))
	//{
	//	Shuffle();
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_M))
	//{
	//	Mulligan();
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_P))
	//{
	//	SendCardFromDeckToGraveyard();
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_1))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(0));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_2))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(1));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_3))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(2));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_4))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(3));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_5))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(4));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_6))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(5));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_7))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(6));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_8))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(7));
	//}
	//if (rGameFramework.KeyboardIsPressed(DIK_9))
	//{
	//	m_pCemetery->PreserveCard(m_pHand->SendCard(8));
	//}

	return true;//仮
}

bool BattlePlayer::UpdateInBattlePreparing()
{
	DrawAtFirst();

	//ここでマリガンの確認UIを出す
	//Mulligan();

	m_pHand->Update();

	return true;
}

bool BattlePlayer::UpdateInDrawPhase()
{
	DrawCard();

	m_pHand->Update();

	return true;
}

bool BattlePlayer::UpdateInMainPhase()
{
	m_rCardTransporter.TransportCollideFollower();
	m_rFollowerOrderMediator.ProcessFollowerOrders();
	m_rRotationOrderMediator.ProcessRotationOrders();

	m_pHand->Update();

	return true;
}

bool BattlePlayer::UpdateInEndPhase()
{
	m_pHand->Update();

	return true;
}

void BattlePlayer::Render()
{
	m_pRect->GetCenter() = { m_TexturCenter.x, m_TexturCenter.y, 0.0f };
	m_pRect->SetSize(RectSize(180.0f, 210.f));

	m_pRect->Render(m_rGameFramework.GetTexture(_T("カシオペア")));
	
	m_pDeck->Render();
	m_pCemetery->Render();
	m_pHand->Render();
	m_pMP->Render();
	m_pRotationTickets->Render();
}

bool BattlePlayer::RotateField()
{
	if(0== m_pRotationTickets->RetentionNum()) return false;
	m_pRotationTickets->RetentionNum();
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

void BattlePlayer::DrawAtFirst()
{
	if (m_pHand->GetQuantites() > 0) return;

	const int FIRST_HAND_CARDS_MAX = 3;

	for (int i = 0; i < FIRST_HAND_CARDS_MAX; ++i)
	{
		DrawCard();
	}
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

void BattlePlayer::InitializeInMainPhaseStart()
{
	m_pMP->IncreaseCapacity();
	m_pMP->RenewUsablePoints();
}
}
