#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Scene/BattleScene/BattleObject.h"

//仮カードクラス
class Card;
namespace summonersaster
{

class Deck :public BattleObject
{
public:
	Deck(const char* deckName);
	~Deck();
	void Render();
	void Destroy();

	/// <summary>
	/// デッキのロード
	/// </summary>
	void Load();

	/// <summary>
	/// シャッフル
	/// </summary>
	void Shuffle();

	/// <summary>
	/// デッキ末尾にカード追加
	/// </summary>
	/// <param name="card">もらうカードクラスポインタ</param>
	void AddCard(Card* card);

	/// <summary>
	/// 末尾からカードを送る
	/// </summary>
	/// <returns>送るカードクラスポインタ</returns>
	Card* SendCard();

	int GetQuantites()
	{
		return static_cast<int>(m_Cards.size());
	}
private:
	std::vector<Card*> m_Cards;
	const int LIMIT_CAPACITY = 40;
	const char* DECK_NAME;


	D3DXVECTOR2 m_TexturCenter = { 1300.0f,700.0f };

};
}
#endif
