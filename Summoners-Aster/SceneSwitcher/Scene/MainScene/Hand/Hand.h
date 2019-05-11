#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Scene/MainScene/BattleObject.h"
#include "Card.h"
#include "MovableCard/MovableCard.h"

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

	explicit Hand(const D3DXVECTOR2& texturCenter = D3DXVECTOR2(990.0f, 800.0f));

	~Hand();
	void Render();
	void Update();
	void Destroy();
	/// <summary>
	/// カードの追加
	/// </summary>
	/// <param name="card">追加するカードクラスポインタ</param>
	/// <returns>ドロー結果</returns>
	RESULT AddCard(Card* card, const D3DXVECTOR3& cardCenter);

	inline int GetQuantites() const
	{
		return static_cast<int>(m_MovableCards.size());
	}

	/// <summary>
	/// カードを送る
	/// </summary>
	/// <param name="handNum">手札番号</param>
	/// <returns>送るカードクラスポインタ</returns>
	Card* SendCard(unsigned int handNum);

	inline std::vector<MovableCard*>* GetCards()
	{
		return &m_MovableCards;
	}

private:
	/// <summary>
	/// 表示モードの切り替えを判定する
	/// </summary>
	void CheckAndToggleModeChange();

	/// <summary>
	/// カードの入れ替え処理
	/// </summary>
	/// <param name="handCardAdditionalPosX">インデックス一つずれた時のｘ座標の差分</param>
	/// <param name="textureCenter">描画のベース位置</param>
	/// <returns>カードの入れ替えが発生たらtrue</returns>
	bool SwapCard(float handCardAdditionalPosX, const D3DXVECTOR2& textureCenter);

	std::vector<MovableCard*> m_MovableCards;

	MovableCard* pSeparatedSelectingCard = nullptr;

	bool m_isHandRemarksMode = false;

	const unsigned int MAX_CAPACITY = 9;

	D3DXVECTOR2 m_TexturCenter = { 0.0f, 0.0f };
};
}
#endif
