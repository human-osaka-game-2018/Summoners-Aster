#ifndef CARD_TRANSPORTER_BASE_H
#define CARD_TRANSPORTER_BASE_H

#include <Windows.h>
#include <vector>
#include <unordered_map>

#include <GameFramework.h>

#include "BattleEnums.h"
#include "Card.h"
#include "Follower/Follower.h"
#include "Weapon/Weapon.h"
#include "Spell/Spell.h"
#include "MovableCard/MovableCard.h"
#include "MP/MP.h"
#include "Cemetery/Cemetery.h"

namespace summonersaster
{
	using gameframework::Singleton;
	using gameframework::Vertices;
	using gameframework::GameFramework;

	/// <summary>
	/// カードを別クラスに転送する際の手助けをする
	/// </summary>
	class CardTransporterBase
	{
	public:
		friend Singleton<CardTransporterBase>;

		~CardTransporterBase();

	protected:
		CardTransporterBase();

		CardTransporterBase(CardTransporterBase& cardTransporterBase) = delete;

		CardTransporterBase& operator=(CardTransporterBase& cardTransporterBase) = delete;

		/// <summary>
		/// 使用済みのカード等を墓地へ送る
		/// </summary>
		virtual void DestroyWornOutCard() = 0;

		/// <summary>
		///	引数のカードと引数の矩形がぶつかっていた場合コストを支払いホルダーに配置する
		/// </summary>
		/// <param name="pVertices">当たり判定用の矩形</param>
		/// <param name="pCard">カードのポインタ</param>
		/// <param name="ppCardHolder">カードを配置する場所</param>
		void TransportCollidingCard(Vertices* pVertices, Card* pCard, Card** ppCardHolder);

		/// <summary>
		/// MPを支払い引数のカードを設置する
		/// </summary>
		/// <param name="pCard">カードのポインタ</param>
		/// <param name="ppCardHolder">カードを配置する場所</param>
		/// <returns>カードを設置することができたか</returns>
		template<class T>
		bool PayMPAndTransportCard(T** ppCardHolder, Card* pCard)
		{
			if (!IsSameType(pCard, typeid(T))) return false;

			if (!m_pMP->Paid(pCard->Cost())) return false;

			*ppCardHolder = static_cast<T*>(pCard);

			return true;
		}

		/// <summary>
		/// 引数の矩形が重なっていたらtrue
		/// </summary>
		/// <param name="pCard">カードのポインタ</param>
		/// <param name="pVertices">当たり判定用の矩形</param>
		/// <returns></returns>
		bool IsCollided(Card* pCard, Vertices* pVertices)const;

		/// <summary>
		/// 同じ型か
		/// </summary>
		/// <param name="pCard">カードのポインタ</param>
		/// <param name="cardType">調べたいカードの型</param>
		/// <returns>同じならtrue</returns>
		bool IsSameType(Card* pCard, const type_info& cardType);

		MP* m_pMP = nullptr;
		Cemetery* m_pCemetery = nullptr;
	};
} // namespace summonersaster

#endif // !CARD_TRANSPORTER_BASE_H
