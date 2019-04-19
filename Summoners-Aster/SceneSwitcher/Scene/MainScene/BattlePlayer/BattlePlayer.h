#ifndef BATTLE_PLAYER_H
#define BATTLE_PLAYER_H

#include <tchar.h>

#include <GameFramework.h>

#include "Deck/Deck.h"
#include "Hand/Hand.h"
#include "Cemetery/Cemetery.h"
#include "HP/HP.h"
#include "MP/MP.h"
#include "RotationTickets/RotationTickets.h"
#include "CardTransporter.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "BattleEnums.h"

namespace summonersaster
{
using gameframework::tstring;

using gameframework::Singleton;

//仮でSingleton化
class BattlePlayer :public Singleton<BattlePlayer>
{
public:
	friend Singleton<BattlePlayer>;

	BattlePlayer(const tstring& deckName = _T("AllFollower"));
	~BattlePlayer();

	void Initialize();
	void Destroy();
	bool Update(const tstring& phaseName);
	void Render();

	/// <summary>
	/// デッキの末尾からカードを手札に入れる
	/// </summary>
	void DrawCard();

	/// <summary>
	/// 手札から指定のカードを墓地に送る
	/// </summary>
	/// <param name="handNum">送る手札番号</param>
	void SendCardFromHandToGraveyard(unsigned int handNum);

	/// <summary>
	/// デッキの末尾からカードを墓地に送る
	/// </summary>
	void SendCardFromDeckToGraveyard();

	/// <summary>
	/// カードを墓地に送る
	/// </summary>
	/// <param name="card">送りたいカードクラスポインタ</param>
	void SendToGraveyard(Card* card);

	/// <summary>
	/// 手札からカードを送る
	/// </summary>
	/// <param name="handNum">送る手札番号</param>
	/// <returns>送られるカードクラスポインタ</returns>
	Card* SendFromHand(unsigned int handNum);

	/// <summary>
	/// デッキをシャッフルする
	/// </summary>
	void Shuffle();

	/// <summary>
	/// ゲーム開始時のドロー
	/// </summary>
	void DrawAtFirst();

	/// <summary>
	/// 所持している手札をデッキに戻して同枚数引く
	/// </summary>
	void Mulligan();

	/// <summary>
	/// 回転権を消費する
	/// </summary>
	/// <returns>消費できたらTRUE、できなければFALSEL</returns>
	bool RotateField();

	/// <summary>
	/// HPを減らす
	/// </summary>
	/// <param name="damage">減らす量</param>
	void Damaged(unsigned int damage);

	/// <summary>
	/// HPを増やす
	/// </summary>
	/// <param name="heal">増やす量</param>
	/// <remarks>初期値よりも増えない</remarks>
	void Recover(unsigned int heal);

	/// <summary>
	/// メインフェイズの始まりで行う初期化
	/// </summary>
	void InitializeInMainPhaseStart();

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

private:
	bool UpdateInBattlePreparing();
	bool UpdateInDrawPhase();
	bool UpdateInMainPhase();
	bool UpdateInEndPhase();

	Hand* m_pHand = nullptr;
	Deck* m_pDeck = nullptr;
	Cemetery* m_pCemetery = nullptr;
	HP* m_pHP = nullptr;
	MP* m_pMP = nullptr;
	RotationTickets* m_pRotationTickets = nullptr;

	const tstring& USE_DECK_NAME;

	D3DXVECTOR2 m_TexturCenter = { 800.0f, 910.0f };
	gameframework::RectSize m_PolygonSize;

	gameframework::Vertices* m_pRect = nullptr;

	CardTransporter& m_rCardTransporter = CardTransporter::CreateAndGetRef();
	FollowerOrderMediator& m_rFollowerOrderMediator = FollowerOrderMediator::CreateAndGetRef();
	RotationOrderMediator& m_rRotationOrderMediator = RotationOrderMediator::CreateAndGetRef();

	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
};
}
#endif
