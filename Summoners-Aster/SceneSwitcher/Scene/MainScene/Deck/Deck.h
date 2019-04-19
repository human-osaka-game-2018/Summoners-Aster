#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Scene/MainScene/BattleObject.h"
#include "Card.h"
#include "Spell/Spell.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"

namespace summonersaster
{
class Deck :public BattleObject
{
public:
	Deck(const tstring& deckName);
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

	inline int GetQuantites() const
	{
		return static_cast<int>(m_Cards.size());
	}

	inline std::vector<Card*>* GetCards()
	{
		return &m_Cards;
	}

private:
	std::vector<Card*> m_Cards;
	const int LIMIT_CAPACITY = 40;
	const tstring& DECK_NAME;

	D3DXVECTOR2 m_TexturCenter = { 1529.0f, 640.0f };
};
}
#endif
