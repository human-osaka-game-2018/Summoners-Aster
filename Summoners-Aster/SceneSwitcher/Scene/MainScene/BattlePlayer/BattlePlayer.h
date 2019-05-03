#ifndef BATTLE_PLAYER_H
#define BATTLE_PLAYER_H

#include <tchar.h>

#include <GameFramework.h>

#include "CardTransporterBase.h"
#include "Deck/Deck.h"
#include "Hand/Hand.h"
#include "Cemetery/Cemetery.h"
#include "HP/HP.h"
#include "MP/MP.h"
#include "WeaponHolder/WeaponHolder.h"
#include "RotationTickets/RotationTickets.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "SummonEffect.h"
#include "BattleEnums.h"

namespace summonersaster
{
using gameframework::tstring;

class BattlePlayer :public CardTransporterBase
{
public:
	BattlePlayer(const TCHAR* pPlayerTextureKey, const tstring& deckName = _T("AllFollower"));
	~BattlePlayer();

	virtual void Initialize();
	virtual void Destroy();
	virtual bool Update(const tstring& phaseName);
	virtual void Render();

	/// <summary>
	/// デッキの末尾からカードを手札に入れる
	/// </summary>
	virtual void DrawCard();

	/// <summary>
	/// ゲーム開始時のドロー
	/// </summary>
	virtual void DrawAtFirst();

	/// <summary>
	/// 所持している手札をデッキに戻して同枚数引く
	/// </summary>
	virtual void Mulligan();

	/// <summary>
	/// HPを減らす
	/// </summary>
	/// <param name="damage">減らす量</param>
	virtual void Damaged(unsigned int damage);

	/// <summary>
	/// HPを増やす
	/// </summary>
	/// <param name="heal">増やす量</param>
	/// <remarks>初期値よりも増えない</remarks>
	virtual void Recover(unsigned int heal);

	/// <summary>
	/// 自分のカードを墓地へ送る
	/// </summary>
	/// <param name="pCard">カードのポインタ</param>
	virtual void SendCardToCemetery(Card* pCard);

	/// <summary>
	/// メインフェイズの始まりで行う初期化
	/// </summary>
	virtual void InitializeInMainPhaseStart();

	inline Hand* HHand()
	{
		return m_pHand;
	}

	inline Deck* HDeck()
	{
		return m_pDeck;
	}

	inline Cemetery* HCemetery()
	{
		return m_pCemetery;
	}

	inline HP* HHP()
	{
		return m_pHP;
	}

	inline MP* HMP()
	{
		return m_pMP;
	}

	inline RotationTickets* HRotationTickets()
	{
		return m_pRotationTickets;
	}

protected:
	virtual bool UpdateInBattlePreparing();
	virtual bool UpdateInDrawPhase();
	virtual bool UpdateInMainPhase();
	virtual bool UpdateInEndPhase();

	/// <summary>
	/// 召喚マスにぶつかった現在ターンのプレイヤーの手札を召喚する
	/// </summary>
	///	<remarks>
	/// MPが足りなかったら失敗
	/// </remarks>
	void TransportCollideFollower();
	void TransportCollideWeapon();

	/// <summary>
	/// 衝突しているカードをフィールドへ送る
	/// </summary>
	/// <param name="ppCard">カードのダブルポインタ</param>
	/// <returns>召喚したらtrue</returns>
	bool TransportCollideFollower(MovableCard** ppCard);

	/// <summary>
	/// フォロワーの召喚起動
	/// </summary>
	/// <param name="handCardIndex">召喚する手札の要素番号</param>
	/// <param name="transportFieldIndex">設置する要素番号</param>
	void ActivateSummon(int handCardIndex, int transportFieldIndex)
	{
		if (BattleInformation::IsExcecuting()) return;

		m_transportFieldIndex = transportFieldIndex;

		std::vector<MovableCard*>* pCards = m_pHand->GetCards();

		Follower** ppFollower = &m_pFollowerZone[m_transportFieldIndex].m_pFollower;

		if (!PayMPAndTransportCard(ppFollower, (*pCards)[handCardIndex]->HCard())) return;

		m_pFollowerZone[m_transportFieldIndex].m_isSummoned = true;

		m_pHand->SendCard(handCardIndex);

		BattleInformation::IsSummoning(true);

		m_rGameFramework.RegisterGraphicEffect(new SummonEffect(m_pFollowerZone[m_transportFieldIndex].m_pVertices->GetCenter()));

		m_effectTakesFrame = EFFECT_TAKES_FRAME_MAX;
	}

	void ActivateArm(int handCardIndex)
	{
		std::vector<MovableCard*>* pHandCards = m_pHand->GetCards();

		Card* pLocaledWeapon = m_pWeaponHolder->HWeapon();

		if (!PayMPAndTransportCard(m_pWeaponHolder->HHolder(), (*pHandCards)[handCardIndex]->HCard())) return;

		BattleInformation::IsArming(true);

		m_pHand->SendCard(handCardIndex);

		m_pCemetery->PreserveCard(pLocaledWeapon);

		m_effectTakesFrame = EFFECT_TAKES_FRAME_MAX;
	}

	void UpdateSummonRoutine()
	{
		if (!BattleInformation::IsSummoning() || BattleInformation::IsDestroying()) return;

		m_pFollowerZone[m_transportFieldIndex].m_pFollower->Rect().SetColor(0x00FFFFFF);

		if (m_effectTakesFrame < EFFECT_TAKES_FRAME_MAX / 2)
		{
			m_pFollowerZone[m_transportFieldIndex].m_pFollower->Rect().FadeIn(EFFECT_TAKES_FRAME_MAX / 2, 0, 255);
		}

		if (m_effectTakesFrame-- > 0) return;

		BattleInformation::IsSummoning(false);
	}

	void UpdateArmRoutine()
	{
		if (!BattleInformation::IsArming() || BattleInformation::IsDestroying()) return;

		if (m_effectTakesFrame == EFFECT_TAKES_FRAME_MAX)
		{
			m_rGameFramework.RegisterGraphicEffect(new SummonEffect(m_pWeaponHolder->HCollisionRect()->GetCenter()));
		}

		m_pWeaponHolder->HWeapon()->Rect().SetColor(0x00FFFFFF);

		if (m_effectTakesFrame < EFFECT_TAKES_FRAME_MAX / 2)
		{
			m_pWeaponHolder->HWeapon()->Rect().FadeIn(EFFECT_TAKES_FRAME_MAX / 2, 0, 255);
		}

		if (m_effectTakesFrame-- > 0) return;

		BattleInformation::IsArming(false);
	}

	/// <summary>
	/// 使用済みのカード等を墓地へ送る
	/// </summary>
	void DestroyWornOutCard()override;

	Hand* m_pHand = nullptr;
	Deck* m_pDeck = nullptr;
	HP* m_pHP = nullptr;
	WeaponHolder* m_pWeaponHolder = nullptr;
	RotationTickets* m_pRotationTickets = nullptr;

	const tstring& USE_DECK_NAME;

	const TCHAR* pPLAYER_TEXTURE_KEY;

	D3DXVECTOR2 m_TexturCenter = { 800.0f, 825.0f };
	gameframework::RectSize m_PolygonSize;

	gameframework::Vertices* m_pRect = nullptr;

	Field& m_rField = Field::CreateAndGetRef();
	FollowerData* m_pFollowerZone = nullptr;

	const int NO_SELECTING_INDEX = -1;
	int m_transportFieldIndex = NO_SELECTING_INDEX;

	const int EFFECT_TAKES_FRAME_MAX = 60;
	int m_effectTakesFrame = 0;

	FollowerOrderMediator& m_rFollowerOrderMediator = FollowerOrderMediator::CreateAndGetRef();
	RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();

	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
};
}
#endif
