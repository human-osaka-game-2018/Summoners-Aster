#ifndef ATTACK_EFFECT_H
#define ATTACK_EFFECT_H

#include <GameFramework.h>

#include "Part/SquareMoveToDest.h"

namespace summonersaster
{
	using gameframework::GraphicEffect;
	using gameframework::Degree;
	using gameframework::Vertices;

	/// <summary>
	/// フォロワーの攻撃時のエフェクト
	/// </summary>
	class AttackEffect :public GraphicEffect
	{
	public:
		AttackEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum);

		virtual ~AttackEffect();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update()override;

	protected:
		int m_requireFrameNum;
		D3DXVECTOR3 m_originPos = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 m_destPos = { 0.0f, 0.0f, 0.0f };
	};
}

#endif //!ATTACK_EFFECT_H
