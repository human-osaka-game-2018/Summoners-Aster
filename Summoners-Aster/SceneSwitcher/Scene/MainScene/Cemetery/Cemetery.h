﻿#ifndef CEMETERY_H
#define CEMETERY_H

#include <vector>

#include "Scene/MainScene/BattleObject.h"
#include "Card.h"

namespace summonersaster
{
class Cemetery :public BattleObject
{
public:
	Cemetery(const D3DXVECTOR2& texturCenter = D3DXVECTOR2(1480.0f, 530.0f));
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

	D3DXVECTOR2 m_TexturCenter = { 0.0f, 0.0f };
};
}
#endif
