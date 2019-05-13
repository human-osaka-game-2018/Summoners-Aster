#include "Hand.h"

using namespace gameframework;

namespace summonersaster
{
Hand::Hand(PLAYER_KIND playerKind, const D3DXVECTOR2& texturCenter) 
	:m_PlayerKind(playerKind), m_TexturCenter(texturCenter)
{
}

Hand::~Hand()
{
	Destroy();
}

void Hand::Update()
{
	float handCardAdditionalPosX = 650.0f / static_cast<float>(m_MovableCards.size() + 1);

	CheckAndToggleModeChange();

	D3DXVECTOR2 textureCenter = m_TexturCenter;

	if (m_IsHandRemarksMode)
	{
		handCardAdditionalPosX = 1000.0f / static_cast<float>(m_MovableCards.size() + 1);

		textureCenter.x = 800.0f - (handCardAdditionalPosX * 0.5f * (m_MovableCards.size() - 1));
		textureCenter.y = 850.0f;
	}

	SwapCard(handCardAdditionalPosX, textureCenter);

	for (auto& movableCard : m_MovableCards)
	{
		movableCard->Update(D3DXVECTOR3(textureCenter.x + handCardAdditionalPosX * 
				static_cast<int>(&movableCard - &m_MovableCards[0]),
			textureCenter.y, 0.0f));
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

Hand::RESULT Hand::AddCard(Card* card, const D3DXVECTOR3& cardCenter)
{
	D3DXVECTOR3 cardCenterZRepaired = cardCenter;
	cardCenterZRepaired.z = 0.0f;

	if (nullptr == card)
	{
		//死亡通知
		return DEAD;
	}
	m_MovableCards.push_back(new MovableCard(card, cardCenterZRepaired));
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

void Hand::CheckAndToggleModeChange()
{
	if (m_PlayerKind == PLAYER_KIND::OPPONENT) return;

	long scrollingAmount = GameFramework::GetRef().MouseWheelScrolling();
	
	if (scrollingAmount == 0) return;
	
	for (auto& movableCard : m_MovableCards)
	{
		m_IsHandRemarksMode = algorithm::Tertiary(scrollingAmount < 0, true, false);

		return;
	}
}

bool Hand::SwapCard(float handCardAdditionalPosX, const D3DXVECTOR2& textureCenter)
{
	for (auto& movableCard : m_MovableCards)
	{
		int index = static_cast<int>(&movableCard - &m_MovableCards[0]);

		if (!movableCard->IsSelectingCard()) continue;

		float posXDiff = movableCard->HCardCenter()->x - (textureCenter.x + handCardAdditionalPosX * index);

		int indexDiff = static_cast<int>(posXDiff + algorithm::Tertiary(posXDiff > 0, +1.0f, -1.0f) * (0.5f * handCardAdditionalPosX))
			/ static_cast<int>(handCardAdditionalPosX);

		int normalizedIndexDiff = min(max(indexDiff + index, 0), static_cast<int>(m_MovableCards.size()) - 1) - index;

		if (normalizedIndexDiff == 0) continue;

		MovableCard* pTmp = movableCard;

		m_MovableCards.erase(m_MovableCards.begin() + index);
		m_MovableCards.insert(m_MovableCards.begin() + index + normalizedIndexDiff, pTmp);

		return true;
	}

	return false;
};
}
