#ifndef MOVABLE_CARD_H
#define MOVABLE_CARD_H

#include <vector>

#include <d3dx9.h>

#include <Gameframework.h>

#include "Card.h"

namespace summonersaster
{
	using gameframework::DirectX8Mouse;
	using gameframework::RectSize;

	/// <summary>
	/// カードのラップマウスで動かすことができるようになる
	/// </summary>
	class MovableCard
	{
	public:
		/// <param name="pCard">ラップするカードのポインタ</param>
		explicit MovableCard(Card* pCard);

		~MovableCard();

		/// <summary>
		/// カードの位置等の設定
		/// </summary>
		/// <param name="defaultCenter">基底となる位置</param>
		void Update(const D3DXVECTOR3& defaultCenter);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="cardSize">カードのサイズ</param>
		void Render(const RectSize& cardSize);

		static inline void NeutralizeSelecting()
		{
			m_selectingInstance = nullptr;
		}

		inline Card* HCard()
		{
			return m_pCard;
		}

		inline void HCard(Card* pCard)
		{
			m_pCard = pCard;
		}

	private:
		MovableCard(MovableCard& movableCard) = delete;

		MovableCard& operator=(MovableCard& movableCard) = delete;

		void CalcCurosorMovementByPrev();

		void IdentifySelectingInstance();

		void NeutralizeSelectingWhenReleasedCard();

		void Move(const D3DXVECTOR3& defaultCenter);

		static Card* m_selectingInstance;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		POINT m_prevCursorPos = { 0, 0 };
		D3DXVECTOR3 m_cardCenter = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 m_cursorMovemntByPrev = { 0.0f, 0.0f, 0.0f };

		Card* m_pCard = nullptr;
	};
} // namespace summonersaster

#endif // !MOVABLE_CARD_H
