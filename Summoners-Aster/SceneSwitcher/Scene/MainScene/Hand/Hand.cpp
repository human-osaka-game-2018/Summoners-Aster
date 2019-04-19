#include "Hand.h"

using namespace gameframework;

namespace summonersaster
{
Hand::Hand()
{
}


Hand::~Hand()
{
	Destroy();
}

void Hand::Update()
{
	float handCardAdditionalPosX = 650.0f / static_cast<float>(m_MovableCards.size() + 1);

	for (auto& movableCard : m_MovableCards)
	{
		int index = static_cast<int>(&movableCard - &m_MovableCards[0]);

		movableCard->Update(D3DXVECTOR3(m_TexturCenter.x + (handCardAdditionalPosX * index + 1), m_TexturCenter.y, 0.0f));
	}
}

void Hand::Render()
{
	for (auto& movableCard : m_MovableCards)
	{
		movableCard->Render(RectSize(100.f, 141.f));
	}
}

void Hand::Destroy()
{
	//外部からの読み込み時に動的確保するため
	for (auto& movableCard : m_MovableCards)
	{
		int index = static_cast<int>(&movableCard - &m_MovableCards[0]);

		delete movableCard->HCard();
		delete movableCard;
	}
	m_MovableCards.clear();
}

Hand::RESULT Hand::AddCard(Card* card)
{
	if (nullptr == card)
	{
		//死亡通知
		return DEAD;
	}
	m_MovableCards.push_back(new MovableCard(card));
	MovableCard::NeutralizeSelecting();
	if (MAX_CAPACITY < m_MovableCards.size())
	{
		return FLOOD;
	}
	return SUCCESS;
}

Card* Hand::SendCard(unsigned int handNum)
{
	if (handNum >= m_MovableCards.size()) return nullptr;
	Card* sendCard = m_MovableCards[handNum]->HCard();
	m_MovableCards.erase(m_MovableCards.begin() + handNum);
	MovableCard::NeutralizeSelecting();
	return sendCard;
}
}
