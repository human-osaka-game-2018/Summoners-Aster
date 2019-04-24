#include "Hand.h"

using namespace gameframework;

namespace summonersaster
{
Hand::Hand(const D3DXVECTOR2& texturCenter) :m_TexturCenter(texturCenter)
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
	RectSize cardSize;
	cardSize.m_height = 1.4f * (cardSize.m_width = 135.0f);

	for (auto& movableCard : m_MovableCards)
	{
		movableCard->Render(cardSize);
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
	delete m_MovableCards[handNum];
	m_MovableCards.erase(m_MovableCards.begin() + handNum);
	MovableCard::NeutralizeSelecting();
	return sendCard;
}
}
