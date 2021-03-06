﻿#include "CardFolder.h"

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

	void CardFolder::RenderCard(const tstring& cardName, const D3DXVECTOR3& center, const RectSize& size)
	{
		(*this)[cardName].Render(center, size, Card::RENDERING_TYPE::LARGE);
	}

	CardFolder::CardFolder()
	{
		LoadCardsData();
	}

	void CardFolder::LoadCardsData()
	{
		std::ifstream ifs("Resources/CardsData.csv");

		std::string oneLine;

		while (std::getline(ifs, oneLine))
		{
			LoadCardData(&oneLine);
		}
	}

	void CardFolder::LoadCardData(std::string* pOneLine)
	{
		std::replace(pOneLine->begin(), pOneLine->end(), ',', ' ');
		
		tstringstream typeConverter;

		#ifdef _UNICODE // UNICODE
		{
			int bufferSize = static_cast<int>(sizeof(TCHAR) * pOneLine->size());
			TCHAR* pOneLineBuff = new TCHAR[bufferSize];

			//-1を指定するとNULLまでが長さになる
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pOneLine->c_str(), -1, pOneLineBuff, bufferSize);

			typeConverter << pOneLineBuff;

			delete[] pOneLineBuff;
		}
		#else // MULTIBYTE
		{
			typeConverter << oneLine;
		}
		#endif

		Register(&typeConverter);
	}

	void CardFolder::Register(tstringstream* pTypeConverter)
	{
		CardComponentData cardComponentData;
		
		(*pTypeConverter) >> cardComponentData.m_cardTypeTmp >> cardComponentData.m_cardName >>
			cardComponentData.m_cost >> cardComponentData.m_attack >> cardComponentData.m_hP >>
			cardComponentData.m_activationTypeTmp >> cardComponentData.m_actionTypeTmp >>
			cardComponentData.m_cardTexturePath;
	
		std::vector<Ability> abilitiesTmp;
		while (cardComponentData.m_activationTypeTmp != -1 && cardComponentData.m_actionTypeTmp != -1)
		{
			//正常に読み込めた情報でAbility構造体をつくる
			Ability abilityTmp(static_cast<Ability::ActivationEvent>(cardComponentData.m_activationTypeTmp),
				static_cast<Ability::Execute>(cardComponentData.m_actionTypeTmp));
			//それをVectorに詰め、このVectorを渡すことで、複数効果持ちのカードを実現する
			abilitiesTmp.push_back(abilityTmp);

			//読み込めないときを検出するために-1を詰める
			cardComponentData.m_activationTypeTmp = -1;
			cardComponentData.m_actionTypeTmp = -1;

			//ここでpTypeConverterから値を受け取れなければ-1のままになる
			(*pTypeConverter) >> cardComponentData.m_activationTypeTmp >> cardComponentData.m_actionTypeTmp;
		}

		Card::TYPE cardType = static_cast<Card::TYPE>(cardComponentData.m_cardTypeTmp);
		switch (cardType)
		{
		case Card::TYPE::FOLLOWER:
			Register(new Follower(cardComponentData.m_cardName, cardComponentData.m_cardTexturePath,
				cardComponentData.m_cost, cardComponentData.m_attack, cardComponentData.m_hP, abilitiesTmp));

			break;

		case Card::TYPE::SPELL:
			Register(new Spell(cardComponentData.m_cardName, cardComponentData.m_cardTexturePath,
				cardComponentData.m_cost, abilitiesTmp));

			break;

		case Card::TYPE::WEAPON:
			Register(new Weapon(cardComponentData.m_cardName, cardComponentData.m_cardTexturePath,
				cardComponentData.m_cost, cardComponentData.m_hP, abilitiesTmp));

			break;
		}
	}
} // namespace summonersaster
