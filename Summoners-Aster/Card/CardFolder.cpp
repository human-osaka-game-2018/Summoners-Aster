#include "CardFolder.h"

using namespace gameframework;

namespace summonersaster
{
	CardFolder::~CardFolder()
	{
		for (auto& card : m_pCards)
		{
			delete card.second;
		}

		m_pCards.clear();
	}

	void CardFolder::Register(Card* pCard)
	{
		m_pCards[pCard->Name()] = pCard;
		m_pCardsName.push_back(pCard->Name());
	}

	Card* CardFolder::CreateCopy(const tstring& cardName, PLAYER_KIND owner)
	{
		if (m_pCards.find(cardName) == m_pCards.end()) return nullptr;

		Card* pCardCopy = nullptr;
		m_pCards[cardName]->CreateCopy(&pCardCopy, owner);

		return pCardCopy;
	}

	CardFolder::CardFolder()
	{
		Register(new Follower(_T("カシオペア"), _T("Textures/FieldCard/kashiopea.png"), 2, 2, 3));
		Register(new Follower(_T("ペルセウス"), _T("Textures/FieldCard/perseus.png"), 1, 2, 1));
		Register(new Follower(_T("エンジェル"), _T("Textures/FieldCard/angel.png"), 3, 4, 4));
		Register(new Follower(_T("ヘラクレス"), _T("Textures/FieldCard/herakles.png"), 4, 6, 4));
		Register(new Follower(_T("アンドロメダ"), _T("Textures/FieldCard/andromeda.png"), 5, 6, 6));
		Register(new Weapon(_T("ウェポン"), _T("Textures/Battle_selectingCardFrame.png"), 1, 2, 2));
		Register(new Spell(_T("キノシタ"), _T("Textures/FieldCard/木下.jpg"), 2));
	}
} // namespace summonersaster
