#ifndef CARD_TRANSPORTER_H
#define CARD_TRANSPORTER_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "Field.h"
#include "BattleEnums.h"
#include "Card.h"
#include "MovableCard/MovableCard.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "Hand/Hand.h"
#include "MP/MP.h"
#include "Cemetery/Cemetery.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::Degree;
	using gameframework::RectSize;
	using gameframework::GameFramework;
	using gameframework::GameFrameworkFactory;

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
		/// プレイヤーの手札MPの登録
		/// </summary>
		/// <param name="PLAYER_KIND">プレイヤーの種類</param>
		/// <param name="pHand">手札のポインタ</param>
		/// <param name="pCemetary">墓地のポインタ</param>
		/// <param name="pMP">MPのポインタ</param>
		void Register(PLAYER_KIND playerKind, Hand* pHand, Cemetery* pCemetary, MP* pMP);

		/// <summary>
		/// 召喚マスにぶつかった現在ターンのプレイヤーの手札を召喚する
		/// </summary>
		///	<remarks>
		/// MPが足りなかったら失敗
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
			PlayerSummonData();
			PlayerSummonData(Hand* pHand, Cemetery* pCemetery, MP* pMP);
			Hand* m_pHand		  = nullptr;
			Cemetery* m_pCemetary = nullptr;
			MP* m_pMP = nullptr;
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
