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
	/// HPが0以下になったフォロワーを墓地へ送る
	/// </summary>
	void DestroyDeadFollower();

	/// <summary>
	/// フォロワーの召喚
	/// </summary>
	/// <param name="handCardIndex">召喚する手札の要素番号</param>
	/// <param name="transportFieldIndex">設置する要素番号</param>
	void Summon(int handCardIndex, int transportFieldIndex);

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

	FollowerOrderMediator& m_rFollowerOrderMediator = FollowerOrderMediator::CreateAndGetRef();
	RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();

	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
};
}
#endif
