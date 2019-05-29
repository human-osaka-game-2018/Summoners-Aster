#ifndef ABILITY_EFFECT_H
#define ABILITY_EFFECT_H

#include <GameFramework.h>

#include "Part/SquareMoveToDest.h"
#include "Part/ScalingFlashSquare.h"
#include "Part/ScalingFlashAbsorbedSquare.h"

namespace summonersaster
{
	using gameframework::GraphicEffect;
	using gameframework::Degree;
	using gameframework::Vertices;

	/// <summary>
	/// フォロワーの攻撃時のエフェクト
	/// </summary>
	class AbilityEffect :public GraphicEffect
	{
	public:
		AbilityEffect(const D3DXVECTOR3& originPos, const D3DXVECTOR3& destPos, int requireFrameNum);

		virtual ~AbilityEffect();

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

#endif //!MOVING_EFFECT_H
