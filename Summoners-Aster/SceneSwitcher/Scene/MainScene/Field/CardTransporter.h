#ifndef CARD_TRANSPORTER_H
#define CARD_TRANSPORTER_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "Field.h"
#include "BattleEnums.h"

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

	class CardHolder
	{
	public:
		std::vector<Card*>* GetCards()
		{
			return &m_pCards;
		}

	protected:
		std::vector<Card*> m_pCards;
	};

	class Hand :public CardHolder
	{
	
	};

	class Cemetary :public CardHolder
	{

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
		/// <param name="PLAYER_KIND">プレイヤーの種類</param>
		/// <param name="pHand">手札のポインタ</param>
		/// <param name="pCemetary">墓地のポインタ</param>
		/// <param name="pPP">PPのポインタ</param>
		void Register(PLAYER_KIND playerKind, Hand* pHand, Cemetary* pCemetary, PP* pPP);

		/// <summary>
		/// 召喚マスにぶつかった現在ターンのプレイヤーの手札を召喚する
		/// </summary>
		///	<remarks>
		/// PPが足りなかったら失敗
		/// </remarks>
		void TransportCollideFollower();

		/// <summary>
		/// HPが0以下になったフォロワーを墓地へ送る
		/// </summary>
		void DestroyDeadFollower();

	private:
		struct PlayerSummonData
		{
		public:
			Hand* m_pHand		  = nullptr;
			Cemetary* m_pCemetary = nullptr;
			PP* m_pPP = nullptr;
		};

		CardTransporter(CardTransporter& cardTransporter) = delete;

		CardTransporter& operator=(CardTransporter& cardTransporter) = delete;

		void TransportFollower(int handCardIndex, int transportFieldIndex);

		std::unordered_map<PLAYER_KIND, PlayerSummonData> m_playersSummonData;

		FollowerData* m_pFollowerZone = nullptr;

		Field& m_rField = Field::CreateAndGetRef();
	};
} // namespace summonersaster

#endif // !CARD_TRANSPORTER_H
