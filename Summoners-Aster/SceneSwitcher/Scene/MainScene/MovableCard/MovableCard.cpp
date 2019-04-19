#include "MovableCard.h"

namespace summonersaster
{
	using namespace gameframework;

	Card* MovableCard::m_selectingInstance = nullptr;

	MovableCard::MovableCard(Card* pCard) :m_pCard(pCard)
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
		}
	}

	void MovableCard::Move(const D3DXVECTOR3& defaultCenter)
	{
		if (m_pCard != m_selectingInstance)
		{
			m_cardCenter = defaultCenter;

			return;
		}

		m_cardCenter += m_cursorMovemntByPrev;
	}
}
