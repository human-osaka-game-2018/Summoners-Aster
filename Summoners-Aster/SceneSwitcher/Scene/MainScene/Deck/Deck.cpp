﻿#include "Deck.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <fstream> 

using namespace gameframework;
namespace summonersaster
{
Deck::Deck(const tstring& deckName, const D3DXVECTOR2& texturCenter) :DECK_NAME(deckName), m_TexturCenter(texturCenter)
{
	D3DXVECTOR3 center = { m_TexturCenter.x, m_TexturCenter.y, 0.0f };
	m_pRect->SetCenter(center);
}

Deck::~Deck()
{
}

void Deck::Render()
{
	Color color;
	if (0 == m_Cards.size())
	color = (255, 255, 0, 0);
	
	m_pRect->SetRotationZ(-90.0f);
	SetVertex(D3DXVECTOR3(m_TexturCenter.x, m_TexturCenter.y, 0.01f), RectSize(100.0f, 141.0f),color);
	DrawTexture(_T("CARD_BACK"));
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

void Deck::Load(PLAYER_KIND owner)
{
	CardFolder& rCardFolder = CardFolder::CreateAndGetRef();

	m_Cards.resize(LIMIT_CAPACITY);
	std::string filename = "DeckDate/Deck.csv";
	std::ifstream readingFile;
	readingFile.open(filename, std::ios::in);

	for (int i = 0; i < LIMIT_CAPACITY; ++i)
	{
		std::string readingBuffer;
		if (!std::getline(readingFile, readingBuffer))
		{
			m_Cards.resize(i);
			break;
		}
		replace(readingBuffer.begin(), readingBuffer.end(), ',', '\0');
		const char* ch = readingBuffer.c_str();
		TCHAR tch[64];
		MultiByteToWideChar(CP_ACP, 0, ch, -1, tch, MultiByteToWideChar(CP_ACP, 0, ch, -1, nullptr, 0));
		m_Cards[i] = rCardFolder.CreateCopy(tch, owner);
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
