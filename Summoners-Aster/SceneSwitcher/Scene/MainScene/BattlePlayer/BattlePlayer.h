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
#include "BattleInformation.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "SummonEffect.h"
#include "BattleEnums.h"
#include "BattleInformation.h"
#include "Ability/AbilityExecutor.h"

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

	/// <summary>
	/// フォロワー召喚時の一連の処理
	/// </summary>
	/// <returns>終了したらtrue</returns>
	bool UpdateSummoningRoutine();

	/// <summary>
	/// 装備は生地の一連の処理
	/// </summary>
	/// <returns>終了したらtrue</returns>
	bool UpdateWeaponDestroyingRoutine();

	/// <summary>
	/// 装備時の一連の処理
	/// </summary>
	/// <returns>終了したらtrue</returns>
	bool UpdateArmingRoutine();

	/// <summary>
	/// スペルカードの一連の処理
	/// </summary>
	/// <returns>終了したらtrue</returns>
	bool UpdateSpellingRoutine();

	/// <summary>
	/// 使用済みのカード等を墓地へ送る
	/// </summary>
	void DestroyWornOutCard()override;

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

	inline WeaponHolder* HWeaponHolder()
	{
		return m_pWeaponHolder;
	}

	inline RotationTickets* HRotationTickets()
	{
		return m_pRotationTickets;
	}

	inline tstring HavingWeaponName()
	{
		return m_pWeaponHolder->HavingWeaponName();
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
	void CheckSpelling();

	/// <summary>
	/// 衝突しているカードをフィールドへ送る
	/// </summary>
	/// <param name="ppCard">カードのダブルポインタ</param>
	/// <returns>召喚したらtrue</returns>
	bool TransportCollideFollower(MovableCard** ppCard);

	/// <summary>
	/// バトルアクションの呼び出し制御
	/// </summary>
	/// <param name="pCallable">呼べるかどうかのフラグ</param>
	/// <param name="pFuncName">関数名</param>
	/// <returns>呼び出した関数の戻り値</returns>
	/// <remarks>この関数内でフラグをfalseにし一度しか呼ばないようにする</remarks>
	bool CallOnce(bool* pCallable, const TCHAR* pFuncName);

	/// <summary>
	/// フォロワーの召喚起動
	/// </summary>
	/// <param name="handCardIndex">召喚する手札の要素番号</param>
	/// <param name="transportFieldIndex">設置する要素番号</param>
	void ActivateSummoning(int handCardIndex, int transportFieldIndex);

	/// <summary>
	/// フォロワーの召喚
	/// </summary>
	/// <returns>召喚できたらtrue</returns>
	bool Summon();

	/// <summary>
	/// 装備破壊の起動
	/// </summary>
	void ActivateWeaponDestroying();

	/// <summary>
	/// 装備の起動
	/// </summary>
	/// <param name="handCardIndex">装備するカードの手札でのインデックス</param>
	void ActivateArming(int handCardIndex);

	/// <summary>
	/// スペルカードの起動
	/// </summary>
	/// <param name="handCardIndex">発動するカードの手札でのインデックス</param>
	void ActivateSpelling(int handCardIndex);

	/// <summary>
	/// スペルカードの発動
	/// </summary>
	bool Spell();

	/// <summary>
	/// 装備
	/// </summary>
	/// <returns>装備できたらtrue</returns>
	bool Arm();

	PLAYER_KIND m_PlayerKind = PLAYER_KIND::PROPONENT;

	Hand* m_pHand = nullptr;
	Deck* m_pDeck = nullptr;
	HP* m_pHP = nullptr;
	WeaponHolder* m_pWeaponHolder = nullptr;
	RotationTickets* m_pRotationTickets = nullptr;

	const tstring& USE_DECK_NAME;

	const TCHAR* pPLAYER_TEXTURE_KEY;

	D3DXVECTOR2 m_TexturCenter = { 800.0f, 845.0f };
	gameframework::RectSize m_PolygonSize;

	gameframework::Vertices* m_pRect = nullptr;

	Field& m_rField = Field::CreateAndGetRef();
	FollowerData* m_pFollowerZone = nullptr;

	Card* m_pWeaponTmp = nullptr;
	MovableCard* m_pSpellTmp = nullptr;

	const int NO_SELECTING_INDEX = -1;
	int m_TransportingFieldIndex = NO_SELECTING_INDEX;
	int m_SelectingHandIndex = NO_SELECTING_INDEX;

	const int EFFECT_TAKES_FRAME_MAX = 60;
	int m_EffectTakesFrame = 0;

	const D3DXVECTOR3 WINDOW_CENTER = { 800.0f, 450.0f, 0.0f };

	FollowerOrderMediator& m_rFollowerOrderMediator = FollowerOrderMediator::CreateAndGetRef();
	RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();

	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
};
}
#endif
