#ifndef CARD_TRANSPORTER_H
#define CARD_TRANSPORTER_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "Field.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

	class Card;
	class PP;

	class Hand
	{
	public:
		std::vector<Card*>* GetHand()
		{
			return &m_pCards;
		}

	private:
		std::vector<Card*> m_pCards;
	};

	/// <summary>
	/// フォロワーを召喚する際の当たり判定などのチェッククラス
	/// </summary>
	class CardTransporter :public Singleton<CardTransporter>
	{
	public:
		friend Singleton<CardTransporter>;

		CardTransporter();
		~CardTransporter();

		/// <summary>
		/// プレイヤーの手札PPの登録
		/// </summary>
		/// <param name="pHand">手札のポインタ</param>
		/// <param name="pPP">PPのポインタ</param>
		/// <param name="pKey">先行か後行かのキー</param>
		void Register(Hand* pHand, PP* pPP, const TCHAR* pKey);

		/// <summary>
		/// 召喚マスにぶつかった現在ターンのプレイヤーの手札を召喚する
		/// </summary>
		///	<remarks>
		/// PPが足りなかったら失敗
		/// </remarks>
		void TransportCollideFollower();

	private:
		struct PlayerSummonData
		{
		public:
			Hand* m_pHand = nullptr;
			PP* m_pPP = nullptr;
		};

		CardTransporter(CardTransporter& cardTransporter) = delete;

		CardTransporter& operator=(CardTransporter& cardTransporter) = delete;

		void TransportFollower(int handCardIndex, int transportFieldIndex);

		std::unordered_map<const TCHAR*, PlayerSummonData*> m_pHands;

		Vertices** m_pFollowerZones = nullptr;

		Field& m_rField = Field::CreateAndGetRef();
	};
}

#endif // !CARD_TRANSPORTER_H
