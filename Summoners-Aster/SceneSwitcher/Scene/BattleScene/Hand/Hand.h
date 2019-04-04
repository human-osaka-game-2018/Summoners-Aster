#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Scene/BattleScene/BattleObject.h"
//仮カードクラス
class Card;
namespace summonersaster
{

class Hand :public BattleObject
{
public:
	enum RESULT
	{
		SUCCESS,
		FLOOD,
		DEAD,
	};

	Hand();
	~Hand();
	void Render();
	void Destroy();
	/// <summary>
	/// カードの追加
	/// </summary>
	/// <param name="card">追加するカードクラスポインタ</param>
	/// <returns>ドロー結果</returns>
	RESULT AddCard(Card* card);

	int GetQuantites()
	{
		return static_cast<int>(m_Cards.size());
	}

	/// <summary>
	/// カードを送る
	/// </summary>
	/// <param name="handNum">手札番号</param>
	/// <returns>送るカードクラスポインタ</returns>
	Card* SendCard(unsigned int handNum);
private:
	std::vector<Card*> m_Cards;
	const unsigned int MAX_CAPACITY = 9;

	D3DXVECTOR2 m_TexturCenter = { 500.0f,600.0f };

};
}
#endif
