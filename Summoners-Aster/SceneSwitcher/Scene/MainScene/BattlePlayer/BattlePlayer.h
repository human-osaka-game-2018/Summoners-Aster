#ifndef BATTLE_PLAYER_H
#define BATTLE_PLAYER_H

#include <GameFramework.h>

#include "Scene/MainScene/Deck/Deck.h"
#include "Scene/MainScene/Hand/Hand.h"
#include "Scene/MainScene/Cemetery/Cemetery.h"
#include "Scene/MainScene/HP/HP.h"
#include "Scene/MainScene/MP/MP.h"

namespace summonersaster
{

class BattlePlayer
{
public:
	BattlePlayer(const char* deckName);
	~BattlePlayer();



	void Initialize();
	void Destroy();
	bool Update(const char* phase);
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
private:
	Hand* m_pHand = nullptr;
	Deck* m_pDeck = nullptr;
	Cemetery* m_pCemetery = nullptr;
	HP* m_pHP = nullptr;
	MP* m_pMP = nullptr;

	const char* USE_DECK_NAME;

	unsigned int m_RotationTickets;

	D3DXVECTOR2 m_TexturCenter = { 800.0f,700.0f };
	gameframework::RectSize m_PolygonSize;

	gameframework::Vertices* m_pRect = nullptr;
	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();

};
}
#endif
