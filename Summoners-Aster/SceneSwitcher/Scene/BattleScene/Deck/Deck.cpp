﻿#include "Deck.h"
#include <random>
#include <algorithm>

using namespace gameframework;
namespace summonersaster
{

Deck::Deck(const char* deckName):DECK_NAME(deckName)
{
}

Deck::~Deck()
{
}

void Deck::Render()
{
#ifdef _DEBUG
	for (int i = 0; i < m_Cards.size(); ++i)
	{
		SetString(L"%d", m_Cards[i]->ID);
		WriteWords(D3DXVECTOR2(i * (Card::DEBUG_WORD_WIGTH * 1.5f) + Card::DEBUG_WORD_WIGTH * 2, 800.f), _T("Debug_str"), DT_RIGHT, (0xFFAAAAAA));
	}
#endif
	Color color;
	if (0 == m_Cards.size())
		color = (255, 255, 0, 0);
	
	SetVertex(D3DXVECTOR3(m_TexturCenter.x, m_TexturCenter.y, 0.0f), RectSize(200.f, 260.f),color);
	DrowTexture(_T("TEAM_LOGO"));

	SetString(L"%d", static_cast<int>(m_Cards.size()));
	WriteWords(D3DXVECTOR2(m_TexturCenter.x + 150.f, m_TexturCenter.y), _T("INPUT_PROMPT"), DT_RIGHT, (0xFFAAAAAA));

}

void Deck::Destroy()
{
	//外部からの読み込み時に動的確保するため
	for (auto card : m_Cards)
	{
		delete card;
	}
	m_Cards.clear();
}

void Deck::Load()
{
	m_Cards.resize(LIMIT_CAPACITY);
	for (int i=0;i<LIMIT_CAPACITY;++i)
	{
		//m_Cards[i] = new Card(i);
	}
	//デッキ読み込み
	//読み込み枚数が規定枚数でない場合エラーを吐かせる
}

void Deck::Shuffle()
{
	//乱数生成してシャッフルする
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(m_Cards.begin(), m_Cards.end(), engine);
}

void Deck::AddCard(Card* card)
{
	m_Cards.emplace_back(card);
}

Card* Deck::SendCard()
{
	if (0 == m_Cards.size()) return nullptr;
	Card* sendCard = m_Cards.back();
	m_Cards.back() = nullptr;
	m_Cards.pop_back();
	return sendCard;
}
}
