#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Card\Card.h"

namespace summonersaster
{
	class Follower :public Card
	{
	public:
		Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint);
		~Follower();

		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard) const override;

		inline int HP() const
		{
			return m_hP;
		}

		inline void HP(int hp)
		{
			m_hP = hp;
		}

		inline int Attack() const
		{
			return m_attack;
		}

		inline void Attack(int attack)
		{
			m_attack = attack;
		}

		/// <summary>
		/// フォロワーとのダメージ判定を行う
		/// </summary>
		/// <param name="pFollower">攻撃する側のフォロワー</param>
		/// <returns>thisの参照</returns>
		Follower& operator-=(const Follower* pFollower);

	private:
		Follower(Follower& follower) = delete;

		Follower& operator=(Follower& follower) = delete;

		int m_hP = 0;
		int m_attack = 0;
	};
} // namespace summonersaster

#endif // !FOLLOWER_H
