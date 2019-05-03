#ifndef SUMMON_EFFECT_H
#define SUMMON_EFFECT_H

#include <GameFramework.h>

#include "Part/ScalingFlashSquare.h"

namespace summonersaster
{
	using gameframework::GraphicEffect;
	using gameframework::Degree;
	using gameframework::Vertices;

	/// <summary>
	/// フォロワーの攻撃時のエフェクト
	/// </summary>
	class SummonEffect :public GraphicEffect
	{
	public:
		SummonEffect(const D3DXVECTOR3& occurencePos);

		virtual ~SummonEffect();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update()override;
	};
}

#endif //!SUMMON_EFFECT_H
