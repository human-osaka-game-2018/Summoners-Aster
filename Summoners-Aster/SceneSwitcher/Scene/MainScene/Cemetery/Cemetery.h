#ifndef CEMETERY_H
#define CEMETERY_H

#include <vector>
#include "Scene/MainScene/BattleObject.h"

//仮カードクラス
class Card;
namespace summonersaster
{

class Cemetery :public BattleObject
{
public:
	Cemetery();
	~Cemetery();
	void Render();
	void Destroy();

	/// <summary>
	/// カードを受ける
	/// </summary>
	/// <param name="card">もらうカードクラスポインタ</param>
	void PreserveCard(Card* card);

	int GetQuantites()
	{
		return static_cast<int>(m_Cards.size());
	}

private:
	std::vector<Card*> m_Cards;

	D3DXVECTOR2 m_TexturCenter = { 1300.0f,300.0f };

};
}
#endif
