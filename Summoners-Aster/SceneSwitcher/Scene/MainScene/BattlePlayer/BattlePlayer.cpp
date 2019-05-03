#include "BattlePlayer.h"
#include "Ability/CardAbilityMediator.h"
using namespace gameframework;

namespace summonersaster
{
BattlePlayer::BattlePlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName)
	:pPLAYER_TEXTURE_KEY(pPlayerTextureKey), USE_DECK_NAME(deckName)
{

}

BattlePlayer::~BattlePlayer()
{
	Destroy();
}

void BattlePlayer::Initialize()
{
	m_pHand = new Hand();
	m_pDeck = new Deck(USE_DECK_NAME);
	m_pDeck->Load(PLAYER_KIND::PROPONENT);
	m_pCemetery = new Cemetery();
	m_pHP = new HP(m_TexturCenter);
	m_pMP = new MP(D3DXVECTOR3(470.0f, 800.0f, 0.9f));
	m_pWeaponHolder = new WeaponHolder(D3DXVECTOR3(0.85f, 2.0f, 0.9f));
	m_pRotationTickets = new RotationTickets(3, D3DXVECTOR2(0.68f, 1.92f));

	GameFrameworkFactory::Create(&m_pRect);

	m_pDeck->Shuffle();

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
}

bool BattlePlayer::Update(const tstring& phase)
{
	if (phase == STEP_KIND::BATTLE_PREPARING) return UpdateInBattlePreparing();

	if (phase == PHASE_KIND::DRAW) return UpdateInDrawPhase();

	if (phase == PHASE_KIND::MAIN) return UpdateInMainPhase();

	m_pHand->Update();

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

	DestroyWornOutCard();

	return true;
}

bool BattlePlayer::UpdateInMainPhase()
{
	TransportCollideFollower();
	TransportCollideWeapon();

	m_rFollowerOrderMediator.ProcessFollowerOrders();
	m_rRotationOrderMediator.ProcessRotationOrders();

	m_pHand->Update();

	UpdateSummonRoutine();

	UpdateArmRoutine();

	DestroyWornOutCard();

	return true;
}

bool BattlePlayer::UpdateInEndPhase()
{
	m_pHand->Update();

	DestroyWornOutCard();

	return true;
}

void BattlePlayer::Render()
{
	m_pRect->GetCenter() = { m_TexturCenter.x, m_TexturCenter.y, 0.89f };
	m_pRect->SetSize(RectSize(150.0f, 150.f));

	m_pRect->Render(m_rGameFramework.GetTexture(pPLAYER_TEXTURE_KEY));
	
	m_pHP->Render();
	m_pMP->Render();
	m_pRotationTickets->Render();
	m_pDeck->Render();
	m_pCemetery->Render();
	m_pWeaponHolder->Render();
	m_pHand->Render();
}

void BattlePlayer::Damaged(unsigned int damage)
{
	m_pHP->Damaged(damage);
}
void BattlePlayer::Recover(unsigned int heal)
{
	m_pHP->Recover(heal);
}

void BattlePlayer::SendCardToCemetery(Card* pCard)
{
	if (!pCard) return;

	if (pCard->Owner() != PLAYER_KIND::PROPONENT) return;

	m_pCemetery->PreserveCard(pCard);
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

void BattlePlayer::TransportCollideFollower()
{
	m_rField.GetFollowerZone(&m_pFollowerZone);

	for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
	{
		m_pFollowerZone[fzi].m_pVertices->GetColor() = 0xAA000000;
	}

	if (BattleInformation::IsExcecuting()) return;

	for (auto& pCard : *m_pHand->GetCards())
	{
		if (TransportCollideFollower(&pCard)) return;
	}
}

void BattlePlayer::TransportCollideWeapon()
{
	std::vector<MovableCard*>* pHandCards = m_pHand->GetCards();

	Color weaponHolderColor = 0xAA000000;

	for (auto& pCard : *pHandCards)
	{
		if (pCard->HCard()->CARD_TYPE != Card::TYPE::WEAPON) continue;

		if (!IsCollided(pCard->HCard(), m_pWeaponHolder->HCollisionRect())) continue;

		weaponHolderColor = 0xAAFF8800;

		if (!GameFramework::GetRef().MouseIsReleased(DirectX8Mouse::DIM_LEFT)) break;

		ActivateArm(static_cast<int>(&pCard - &(*m_pHand->GetCards())[0]));

		break;
	}

	m_pWeaponHolder->HCollisionRect()->SetColor(weaponHolderColor);
}

bool BattlePlayer::TransportCollideFollower(MovableCard** ppCard)
{
	int handCardIndex = static_cast<int>(ppCard - &(*m_pHand->GetCards())[0]);

	for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
	{
		if ((*ppCard)->HCard()->CARD_TYPE != Card::TYPE::FOLLOWER) continue;

		//フォロワーが召喚できる場所か
		if (m_pFollowerZone[fzi].m_pFollower || m_pFollowerZone[fzi].m_isOpponentZone ||
			!IsCollided((*ppCard)->HCard(), m_pFollowerZone[fzi].m_pVertices)) continue;

		m_pFollowerZone[fzi].m_pVertices->GetColor() = 0xAAFF8800;

		if (!GameFramework::GetRef().MouseIsReleased(DirectX8Mouse::DIM_LEFT)) break;

		Summon(handCardIndex, fzi);
		CardAbilityMediator::Activator(Ability::ActivationEvent::SUMMONED, &m_pFollowerZone[fzi]);
		
		return true;
	}

	return false;
}

void BattlePlayer::DestroyDeadFollower()
{
	std::vector<Card*> pCemetary;

	m_rField.DestroyDeadFollower(&pCemetary);

	for (auto& pCard : pCemetary)
	{
		m_pCemetery->PreserveCard(pCard);
	}
}

void BattlePlayer::Summon(int handCardIndex, int transportFieldIndex)
{
	std::vector<MovableCard*>* pCards = m_pHand->GetCards();

	Follower** ppFollower = &m_pFollowerZone[transportFieldIndex].m_pFollower;

	if (!PayMPAndTransportCard(ppFollower, (*pCards)[handCardIndex]->HCard())) return;
	CardAbilityMediator::Activator(Ability::SUMMON);
	m_pHand->SendCard(handCardIndex);
	CardAbilityMediator::Register(&m_pFollowerZone[transportFieldIndex]);
	m_pFollowerZone[transportFieldIndex].m_isSummoned = true;
}

void BattlePlayer::DestroyWornOutCard()
{
	if (BattleInformation::IsExcecuting()) return;

	Card* pWeapon = m_pWeaponHolder->HWeapon();

	if (!pWeapon) return;

	if (!pWeapon->ShouldDestroyed()) return;

	m_pCemetery->PreserveCard(pWeapon);

	m_pWeaponHolder->HWeapon(nullptr);
}
}
