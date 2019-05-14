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
		explicit MovableCard(Card* pCard, const D3DXVECTOR3& cardCenter, int returningTakesFramesMax = 15);

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

		inline D3DXVECTOR3* HCardCenter()
		{
			return &m_cardCenter;
		}

		inline bool IsSelectingCard() const
		{
			return m_selectingInstance == m_pCard;
		}

		inline bool ReturningTakesFramesMax(int returningTakesFramesMax)
		{
			m_returningTakesFramesMax = returningTakesFramesMax;
		}

		static bool IsSelecting()
		{
			return m_selectingInstance != nullptr;
		}
		
		inline void CanOperated(bool canOperated)
		{
			m_canOperated = canOperated;
		}

	private:
		MovableCard(MovableCard& movableCard) = delete;

		MovableCard& operator=(MovableCard& movableCard) = delete;

		void CalcCurosorMovementByPrev();

		void IdentifySelectingInstance();

		void NeutralizeSelectingWhenReleasedCard();

		void CreateReturningMovement();

		void Move(const D3DXVECTOR3& defaultCenter);

		static Card* m_selectingInstance;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		POINT m_prevCursorPos = { 0, 0 };
		D3DXVECTOR3 m_defaultCenter = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 m_cardCenter = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 m_cursorMovemntByPrev = { 0.0f, 0.0f, 0.0f };

		int m_returningTakesFramesMax = 1;
		int m_returningTakesFrames = m_returningTakesFramesMax;
		D3DXVECTOR3 m_returningMovement = { 0.0f, 0.0f, 0.0f };

		bool m_canOperated = true;

		Card* m_pCard = nullptr;
	};
} // namespace summonersaster

#endif // !MOVABLE_CARD_H
