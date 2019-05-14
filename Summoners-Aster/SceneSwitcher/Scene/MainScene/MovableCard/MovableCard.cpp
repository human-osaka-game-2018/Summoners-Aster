#include "MovableCard.h"

namespace summonersaster
{
	using namespace gameframework;

	Card* MovableCard::m_selectingInstance = nullptr;

	MovableCard::MovableCard(Card* pCard, const D3DXVECTOR3& cardCenter, int returningTakesFramesMax)
		:m_pCard(pCard), m_cardCenter(cardCenter), m_returningTakesFramesMax(returningTakesFramesMax)
	{

	}

	MovableCard::~MovableCard()
	{

	}

	void MovableCard::Update(const D3DXVECTOR3& defaultCenter)
	{
		CalcCurosorMovementByPrev();
		IdentifySelectingInstance();
		NeutralizeSelectingWhenReleasedCard();
		Move(defaultCenter);
	}

	void MovableCard::Render(const RectSize& cardSize)
	{
		m_pCard->Render(m_cardCenter, cardSize);
	}

	void MovableCard::CalcCurosorMovementByPrev()
	{
		POINT currentCursorPos = { 0, 0 };
		m_rGameFramework.CursorPos(&currentCursorPos);

		m_cursorMovemntByPrev.x = static_cast<float>(currentCursorPos.x - m_prevCursorPos.x);
		m_cursorMovemntByPrev.y = static_cast<float>(currentCursorPos.y - m_prevCursorPos.y);

		m_prevCursorPos = currentCursorPos;
	}

	void MovableCard::IdentifySelectingInstance()
	{
		if (!m_canOperated) return;

		if (m_rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			if (!m_rGameFramework.IsCursorOnRect(m_pCard->Rect())) return;

			m_selectingInstance = m_pCard;
		}
	}

	void MovableCard::NeutralizeSelectingWhenReleasedCard()
	{
		if (m_rGameFramework.MouseIsReleased(DirectX8Mouse::DIM_LEFT))
		{
			NeutralizeSelecting();

			CreateReturningMovement();
		}
	}

	void MovableCard::CreateReturningMovement()
	{
		m_returningMovement = (m_defaultCenter - m_cardCenter) / static_cast<float>(m_returningTakesFramesMax);

		m_returningTakesFrames = m_returningTakesFramesMax;
	}

	void MovableCard::Move(const D3DXVECTOR3& defaultCenter)
	{
		if (m_defaultCenter != defaultCenter)
		{
			m_defaultCenter = defaultCenter;

			CreateReturningMovement();
		}

		if (m_pCard != m_selectingInstance)
		{
			if (m_returningTakesFrames-- <= 0) return;

			m_cardCenter += m_returningMovement;

			return;
		}

		m_cardCenter += m_cursorMovemntByPrev;
	}
}
