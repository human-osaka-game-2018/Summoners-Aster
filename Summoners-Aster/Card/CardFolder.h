#ifndef CARD_FOLDER_H
#define CARD_FOLDER_H

#include <Windows.h>
#include <tchar.h>
#include <unordered_map>

#include <GameFramework.h>

#include "Card.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "BattleEnums.h"

namespace summonersaster
{
	using gameframework::tstring;
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
		CardFolder();

		CardFolder(CardFolder& card) = delete;

		CardFolder& operator=(CardFolder& card) = delete;
			
		std::unordered_map<tstring, Card*> m_pCards;
		std::vector <tstring> m_pCardsName;
	};
} // namespace summonersaster

#endif // !CARD_FOLDER_H
