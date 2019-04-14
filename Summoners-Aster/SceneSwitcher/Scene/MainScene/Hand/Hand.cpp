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


void Hand::Render()
{
	for (int i = 0; i < m_Cards.size(); ++i)
	{
		SetVertex(D3DXVECTOR3(m_TexturCenter.x + 50 * i, m_TexturCenter.y, 0.0f),RectSize(200.f, 260.f),Color(255, i * 50 + 50, i * 50 + 50, i * 50 + 50));
		DrowTexture(_T("TEAM_LOGO"));
		SetString(L"%d", static_cast<int>(m_Cards.size()));
		WriteWords(D3DXVECTOR2(m_TexturCenter.x - 50.f , m_TexturCenter.y),_T("INPUT_PROMPT"), DT_CENTER);

#ifdef _DEBUG
		SetString(L"%d", m_Cards[i]->ID);
		WriteWords(D3DXVECTOR2(i * (Card::DEBUG_WORD_WIGTH * 1.5f) + Card::DEBUG_WORD_WIGTH * 2, 700.f),_T("Debug_str"), DT_RIGHT,(0xFF0000FF));
#endif

	}
}

void Hand::Destroy()
{
	//外部からの読み込み時に動的確保するため
	for (auto card : m_Cards)
	{
		delete card;
	}
	m_Cards.clear();

}

Hand::RESULT Hand::AddCard(Card* card)
{
	if (nullptr == card)
	{
		//死亡通知
		return DEAD;
	}
	m_Cards.emplace_back(card);
	if (MAX_CAPACITY < m_Cards.size())
	{
		return FLOOD;
	}
	return SUCCESS;
}

Card* Hand::SendCard(unsigned int handNum)
{
	if (handNum >= m_Cards.size()) return nullptr;
	Card* sendCard = m_Cards[handNum];
	m_Cards[handNum] = nullptr;
	m_Cards.erase(m_Cards.begin() + handNum);
	return sendCard;
}
}
