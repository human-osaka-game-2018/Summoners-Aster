#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Card\Card.h"
#include "BattleInformation.h"

namespace summonersaster
{
	class Follower :public Card
	{
	public:
		Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, std::vector<Ability> abilities);
		Follower(const tstring& name, const tstring& texturePath, int cost, int attack, int hitPoint, PLAYER_KIND owner, const TCHAR* pTextureKey, std::vector<Ability> abilities);

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

		inline void RestoreAttack()
		{
			m_attack = m_originalAttack;
		}

		inline std::vector<Follower*>* GetTargegtFollowers() 
		{
			return &m_targetFollowers;
		}

		/// <summary>
		/// フォロワーとのダメージ判定を行う
		/// </summary>
		/// <param name="pFollower">攻撃する側のフォロワー</param>
		/// <returns>thisの参照</returns>
		Follower& operator-=(const Follower* pFollower);

		void Render(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType = RENDERING_TYPE::MIDDLE, const Degree& rotationZ = Degree(0))override;

	private:
		Follower(Follower& follower) = delete;

		Follower& operator=(Follower& follower) = delete;

		void InitializeStream();

		void RenderHP(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType);

		void RenderAttack(const D3DXVECTOR3& center, const RectSize& size, RENDERING_TYPE renderingType);

		Stream* m_pAttackStream = nullptr;
		Stream* m_pHPStream = nullptr;

		int m_hP = 0;
		int m_attack = 0;
		int m_originalAttack = 0;
		//!<効果対象となったフォロワーを保存する、破壊された時に元に戻すときなどに使う
		std::vector<Follower*> m_targetFollowers;
	};
} // namespace summonersaster

#endif // !FOLLOWER_H
