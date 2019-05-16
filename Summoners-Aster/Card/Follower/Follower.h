#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Card\Card.h"
#include "BattleInformation.h"

namespace summonersaster
{
	class Follower :public Card
	{
	public:
		Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, const Ability& ability);
		Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, const Ability& ability);

		~Follower();

		/// <summary>
		/// 自身のコピーを動的確保する
		/// </summary>
		/// <param name="ppCard">コピーされるカードのポインタのポインタ</param>
		void CreateCopy(Card** ppCard, PLAYER_KIND owner) const override;

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

		void Render(const D3DXVECTOR3& center, const RectSize& size, const Degree& rotationZ = Degree(0))override;

	private:
		Follower(Follower& follower) = delete;

		Follower& operator=(Follower& follower) = delete;

		void InitializeStream()
		{
			gameframework::GameFrameworkFactory::Create(&m_pAttackStream);
			gameframework::GameFrameworkFactory::Create(&m_pHPStream);
		}

		void RenderHP(const D3DXVECTOR3& center, const RectSize& size);

		void RenderAttack(const D3DXVECTOR3& center, const RectSize& size);

		Stream* m_pAttackStream = 0;
		Stream* m_pHPStream = 0;

		int m_hP = 0;
		int m_attack = 0;
	};
} // namespace summonersaster

#endif // !FOLLOWER_H
