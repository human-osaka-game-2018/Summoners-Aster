#ifndef CARD_FOLDER_H
#define CARD_FOLDER_H

#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <unordered_map>
#include <iostream>
#include <locale> 
#include <codecvt> 
#include <fstream>
#include <cstdlib>
#include <algorithm>

#include <GameFramework.h>

#include "Card.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "Spell/Spell.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::tstring;
	using gameframework::tstringstream;
	using gameframework::RectSize;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::GameFramework;
	using gameframework::Singleton;

	class CardFolder :public Singleton<CardFolder>
	{
	public:
		friend Singleton<CardFolder>;

		~CardFolder();

		/// <summary>
		/// カードの原版に登録する
		/// </summary>
		/// <param name="pCard">登録するカード</param>
		void Register(Card* pCard);
		
		/// <summary>
		/// コピーカードの作成
		/// </summary>
		/// <param name="cardName">作成するカードの名前</param>
		/// <param name="owner">所有者</param>
		/// <returns>コピーカード</returns>
		Card* CreateCopy(const tstring& cardName, PLAYER_KIND owner);

		int GetQuantity()
		{
			return static_cast<int>(m_pCards.size());
		}

		tstring GetCardName(int index)
		{
			return m_pCardsName[index];
		}

	private:
		struct CardComponentData
		{
		public:
			int m_cardTypeTmp = 0;
			tstring m_cardName;
			int m_cost = 0;
			int m_attack = 0;
			int m_hP = 0;
			int m_activationTypeTmp = 0;
			int m_actionTypeTmp = 0;
			tstring m_cardTexturePath;
		};

		CardFolder();

		CardFolder(CardFolder& card) = delete;

		CardFolder& operator=(CardFolder& card) = delete;

		void LoadCardsData();

		void LoadCardData(std::string* pOneLine);

		void Register(tstringstream* pTypeConverter);

		std::unordered_map<tstring, Card*> m_pCards;
		std::vector <tstring> m_pCardsName;
	};
} // namespace summonersaster

#endif // !CARD_FOLDER_H
