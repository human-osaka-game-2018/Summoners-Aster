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
	m_pHand = new Hand(PLAYER_KIND::PROPONENT);
	m_pDeck = new Deck(USE_DECK_NAME);
	m_pDeck->Load(PLAYER_KIND::PROPONENT);
	m_pCemetery = new Cemetery();

	D3DXVECTOR2 hpPos(800.0f, 900.0f);
	m_pHP = new HP(hpPos);
	m_pRotationTickets = new RotationTickets(D3DXVECTOR2(0.23f, 1.785f));
	m_pMP = new MP(D3DXVECTOR3(100.0f, 800.0f, 0.9f));
	m_pWeaponHolder = new WeaponHolder(D3DXVECTOR3(0.85f, 1.8f, 0.9f));

	GameFrameworkFactory::Create(&m_pRect);

	m_pDeck->Shuffle();

	m_rFollowerOrderMediator.Register(PLAYER_KIND::PROPONENT, m_pRect, m_pHP, m_pWeaponHolder);
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

	return true;//仮
}

bool BattlePlayer::UpdateInBattlePreparing()
{

	DrawAtFirst();

	//ここでマリガンの確認UIを出す
	//Mulligan();

	return true;
}

bool BattlePlayer::UpdateInDrawPhase()
{
	DrawCard();

	DestroyWornOutCard();

	return true;
}

bool BattlePlayer::UpdateInMainPhase()
{
	TransportCollideFollower();
	TransportCollideWeapon();
	CheckSpelling();

	m_rFollowerOrderMediator.ProcessFollowerOrders();
	m_rRotationOrderMediator.ProcessRotationOrders();

	DestroyWornOutCard();

	return !BattleInformation::IsWaitingAction();
}

bool BattlePlayer::UpdateInEndPhase()
{
	DestroyWornOutCard();

	return true;
}

void BattlePlayer::Render()
{
	m_pRect->GetCenter() = { m_TexturCenter.x, m_TexturCenter.y, 0.89f };
	m_pRect->SetSize(RectSize(125.0f, 125.f));

	m_pRect->Render(m_rGameFramework.GetTexture(pPLAYER_TEXTURE_KEY));
	m_pRect->Render(m_rGameFramework.GetTexture(_T("PLAYER_FRAME")));
	
	m_pCemetery->Render();
	m_pHP->Render();
	m_pRotationTickets->Render();
	m_pMP->Render();
	m_pDeck->Render();
	m_pWeaponHolder->Render();
	m_pHand->Render();

	if (m_pSpellTmp)
	{
		m_pSpellTmp->Render(RectSize(135.0f, 1.4f * 135.0f));
	}
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
	m_rGameFramework.OneShotStart(L"DRAW");
	Hand::RESULT drawResult;
	if (Hand::FLOOD == (drawResult = m_pHand->AddCard(m_pDeck->SendCard(), m_pDeck->GetCenter())))
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
	m_rGameFramework.OneShotStart(L"SHUFFLE");
	const int FIRST_HAND_CARDS_MAX = 3;

	while (SoundLib::Stopped != m_rGameFramework.GetStatus(L"SHUFFLE"));
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
		m_pHand->AddCard(m_pDeck->SendCard(), m_pHand->GetCenter());
	}
}

void BattlePlayer::InitializeInMainPhaseStart()
{
	m_pMP->IncreaseCapacity();
	m_pMP->RenewUsablePoints();
}

bool BattlePlayer::UpdateSummoningRoutine()
{
	static bool isRoutineStart = true;

	if (!CallOnce(&isRoutineStart, _T("Summon"))) return isRoutineStart = true;

	m_pFollowerZone[m_TransportingFieldIndex].m_pFollower->Rect().SetColor(0x00FFFFFF);

	if (m_EffectTakesFrame <= EFFECT_TAKES_FRAME_MAX / 2)
	{
		m_pFollowerZone[m_TransportingFieldIndex].m_pFollower->Rect().FadeIn(EFFECT_TAKES_FRAME_MAX / 2, 0, 255);
	}

	if (--m_EffectTakesFrame > 0) return false;

	return isRoutineStart = true;
}

bool BattlePlayer::UpdateWeaponDestroyingRoutine()
{
	static bool isRoutineStart = true;

	CallOnce(&isRoutineStart, _T("DestroyWeapon"));

	Vertices& rCard = m_pWeaponHolder->HWeapon()->Rect();

	rCard.FadeOut(EFFECT_TAKES_FRAME_MAX, 255, 0);

	if (m_EffectTakesFrame-- > 0) return false;

	m_pCemetery->PreserveCard(m_pWeaponHolder->LeaveCard());

	return isRoutineStart = true;
}

bool BattlePlayer::UpdateArmingRoutine()
{
	static bool isRoutineStart = true;

	if (!CallOnce(&isRoutineStart, _T("Arm"))) return isRoutineStart = true;

	m_pWeaponHolder->HWeapon()->Rect().SetColor(0x00FFFFFF);

	if (m_EffectTakesFrame < EFFECT_TAKES_FRAME_MAX / 2)
	{
		m_pWeaponHolder->HWeapon()->Rect().FadeIn(EFFECT_TAKES_FRAME_MAX / 2, 0, 255);
	}

	if (m_EffectTakesFrame-- > 0) return false;

	return isRoutineStart = true;
}

bool BattlePlayer::UpdateSpellingRoutine()
{
	static int movingWaitingFrame = 0;

	if (movingWaitingFrame++ < 15) return false;

	static bool isRoutineStart = true;

	if (!CallOnce(&isRoutineStart, _T("Spell"))) return isRoutineStart = true;

	m_pSpellTmp->Update(WINDOW_CENTER);

	if (m_EffectTakesFrame < EFFECT_TAKES_FRAME_MAX / 2)
	{
		m_pSpellTmp->HCard()->Rect().FadeOut(EFFECT_TAKES_FRAME_MAX / 2, 255, 0);
	}

	if (m_EffectTakesFrame-- > 0) return false;

	m_pCemetery->PreserveCard(m_pSpellTmp->HCard());

	//効果が複数あるときのためにfor文で回す
	std::vector<Ability> abilities = m_pSpellTmp->HCard()->Abilities();
	for (auto ability : abilities)
	{
		AbilityExecutor::Execute(m_pSpellTmp->HCard(), ability.execute);
	}

	delete m_pSpellTmp;
	m_pSpellTmp = nullptr;

	movingWaitingFrame = 0;

	return isRoutineStart = true;
}

void BattlePlayer::DestroyWornOutCard()
{
	if (BattleInformation::IsWaitingAction()) return;

	Card* pWeapon = m_pWeaponHolder->HWeapon();

	if (!pWeapon) return;

	if (!pWeapon->ShouldDestroyed()) return;

	BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::WEAPON_DESTROYING, m_PlayerKind };
	BattleInformation::PushQueBack(actionInformation);
}

void BattlePlayer::TransportCollideFollower()
{
	m_rField.GetFollowerZone(&m_pFollowerZone);

	for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
	{
		m_pFollowerZone[fzi].m_pVertices->GetColor() = 0xAA000000;
	}

	if (BattleInformation::IsWaitingAction()) return;

	for (auto& pCard : *m_pHand->GetCards())
	{
		if (TransportCollideFollower(&pCard)) return;
	}
}

void BattlePlayer::TransportCollideWeapon()
{
	std::vector<MovableCard*>* pHandCards = m_pHand->GetCards();

	if (BattleInformation::IsWaitingAction()) return;

	Color weaponHolderColor = 0xAA000000;
	Color weaponColor = 0xFFFFFFFF;

	for (auto& pCard : *pHandCards)
	{
		if (pCard->HCard()->CARD_TYPE != Card::TYPE::WEAPON) continue;

		if (!m_rGameFramework.IsCursorOnRect(pCard->HCard()->Rect())) continue;

		if (!IsCollided(pCard->HCard(), m_pWeaponHolder->HCollisionRect())) continue;

		if (!m_pMP->CanPay(pCard->HCard())) continue;

		weaponHolderColor = 0xAAFF8800;
		weaponColor = 0xFFFF8800;

		if (!GameFramework::GetRef().MouseIsReleased(DirectX8Mouse::DIM_LEFT)) break;

		weaponHolderColor = 0xAA000000;
		weaponColor = 0xFFFFFFFF;

		ActivateArming(static_cast<int>(&pCard - &(*m_pHand->GetCards())[0]));

		break;
	}

	m_pWeaponHolder->HCollisionRect()->SetColor(weaponHolderColor);

	if (!m_pWeaponHolder->HWeapon()) return;

	m_pWeaponHolder->HWeapon()->Rect().SetColor(weaponColor);
}

void BattlePlayer::CheckSpelling()
{
	if (BattleInformation::IsWaitingAction()) return;

	auto pHandCards = m_pHand->GetCards();

	for (auto& handCard : *pHandCards)
	{
		int index = static_cast<int>(&handCard - &(*pHandCards)[0]);

		if (handCard->HCard()->CARD_TYPE != Card::TYPE::SPELL) continue;

		if (!m_rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_RIGHT)) continue;

		if (!m_rGameFramework.IsCursorOnRect(handCard->HCard()->Rect())) continue;

		if (!m_pMP->CanPay(handCard->HCard())) continue;

		ActivateSpelling(index);
	}
}

bool BattlePlayer::TransportCollideFollower(MovableCard** ppCard)
{
	int handCardIndex = static_cast<int>(ppCard - &(*m_pHand->GetCards())[0]);

	for (int fzi = 0; fzi < m_rField.FIELD_FOLLOWERS_NUM; ++fzi)
	{
		if ((*ppCard)->HCard()->CARD_TYPE != Card::TYPE::FOLLOWER) continue;

		if (!m_rGameFramework.IsCursorOnRect((*ppCard)->HCard()->Rect())) continue;

		//フォロワーが召喚できる場所か
		if (m_pFollowerZone[fzi].m_pFollower || m_pFollowerZone[fzi].m_isOpponentZone ||
			!IsCollided((*ppCard)->HCard(), m_pFollowerZone[fzi].m_pVertices)) continue;

		if (!m_pMP->CanPay((*ppCard)->HCard())) continue;

		m_pFollowerZone[fzi].m_pVertices->GetColor() = 0xAAFF8800;

		if (!GameFramework::GetRef().MouseIsReleased(DirectX8Mouse::DIM_LEFT)) break;

		CardAbilityMediator::Activator(Ability::ActivationEvent::SUMMONED, &m_pFollowerZone[fzi]);
			
		ActivateSummoning(handCardIndex, fzi);

		return true;
	}

	return false;
}

bool BattlePlayer::CallOnce(bool* pCallable, const TCHAR* pFuncName)
{
	if (!(*pCallable)) return true;

	(*pCallable) = false;

	if (pFuncName == _T("Summon")) return Summon();

	if (pFuncName == _T("Arm")) return Arm();

	if (pFuncName == _T("Spell")) return Spell();

	if (pFuncName == _T("DestroyWeapon")) m_EffectTakesFrame = EFFECT_TAKES_FRAME_MAX;

	return true;
}

void BattlePlayer::ActivateSummoning(int handCardIndex, int transportFieldIndex)
{
	BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::SUMMONING, m_PlayerKind };

	BattleInformation::PushQueBack(actionInformation);

	m_TransportingFieldIndex = transportFieldIndex;
	m_SelectingHandIndex = handCardIndex;
}

bool BattlePlayer::Summon()
{
	std::vector<MovableCard*>* pCards = m_pHand->GetCards();

	Follower** ppFollower = &m_pFollowerZone[m_TransportingFieldIndex].m_pFollower;

	if (!PayMPAndTransportCard(ppFollower, (*pCards)[m_SelectingHandIndex]->HCard())) return false;
	m_rGameFramework.OneShotSimultaneous(L"SUMMON");

	m_pFollowerZone[m_TransportingFieldIndex].m_isSummoned = true;

	m_pHand->SendCard(m_SelectingHandIndex);

	m_rGameFramework.RegisterGraphicEffect(new SummonEffect(m_pFollowerZone[m_TransportingFieldIndex].m_pVertices->GetCenter()));

	m_EffectTakesFrame = EFFECT_TAKES_FRAME_MAX;

	return true;
}

void BattlePlayer::ActivateWeaponDestroying()
{
	if (!m_pWeaponHolder->HWeapon()) return;

	BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::WEAPON_DESTROYING, m_PlayerKind };
	BattleInformation::PushQueBack(actionInformation);
}

void BattlePlayer::ActivateArming(int handCardIndex)
{
	if (m_pWeaponHolder->HWeapon())
	{
		ActivateWeaponDestroying();
	}

	m_SelectingHandIndex = handCardIndex;

	m_pWeaponTmp = m_pHand->SendCard(m_SelectingHandIndex);

	if (!m_pMP->CanPay(m_pWeaponTmp)) return;

	BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::ARMING, m_PlayerKind };
	BattleInformation::PushQueBack(actionInformation);
}

bool BattlePlayer::Arm()
{
	std::vector<MovableCard*>* pHandCards = m_pHand->GetCards();

	if (!PayMPAndTransportCard(m_pWeaponHolder->HHolder(), m_pWeaponTmp)) return false;
	m_rGameFramework.OneShotStart(L"ARMED");

	m_rGameFramework.RegisterGraphicEffect(new SummonEffect(m_pWeaponHolder->HCollisionRect()->GetCenter()));

	m_pWeaponHolder->HWeapon()->Rect().SetColor(0x00FFFFFF);

	m_EffectTakesFrame = EFFECT_TAKES_FRAME_MAX;

	return true;
}

void BattlePlayer::ActivateSpelling(int handCardIndex)
{
	m_SelectingHandIndex = handCardIndex;

	m_pSpellTmp = m_pHand->SendMovableCard(m_SelectingHandIndex);
	m_pSpellTmp->CanOperated(false);

	BattleInformation::ActionInformation actionInformation = { BattleInformation::ACTION_KIND::SPELLING, m_PlayerKind };
	BattleInformation::PushQueBack(actionInformation);
}

bool BattlePlayer::Spell()
{
	if (!m_pMP->Paid(m_pSpellTmp->HCard()->Cost())) return false;
	m_rGameFramework.OneShotStart(L"MAGIC");

	m_rGameFramework.RegisterGraphicEffect(new SummonEffect(WINDOW_CENTER));

	m_EffectTakesFrame = EFFECT_TAKES_FRAME_MAX;

	return true;
}
}
