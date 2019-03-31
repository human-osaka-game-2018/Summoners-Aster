#ifndef GRAPHIC_EFFECT_H
#define GRAPHIC_EFFECT_H

#include <vector>

#include "PartScheduler/PartScheduler.h"
#include "PartScheduler/Part.h"
#include "PartScheduler/DiffuseDifferenceSquare.h"
#include "PartScheduler/FollowUpCursorSquare.h"
#include "PartScheduler/ScalingFadeInOutSquare.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// グラフィックエフェクト
	/// </summary>
	class GraphicEffect
	{
	public:
		virtual ~GraphicEffect();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 全てのパーツを描画する
		/// </summary>
		void Render();

		inline bool IsEnd()const
		{
			return m_isEnd;
		}

	protected:
		GraphicEffect(const GraphicEffect& graphicEffect) = delete;

		/// <param name="isAdditionBlendMode">描画する際に加算で行うか</param>
		GraphicEffect(bool isAdditionBlendMode = true);

		GraphicEffect& operator=(const GraphicEffect& graphicEffect) = delete;

		void UpdateParts();

		/// <summary>
		/// エフェクトの現在の生存フレーム数
		/// </summary>
		int m_lifeFrame = 0;
		bool m_isEnd = false;

		/// <summary>
		/// 加算で描画を行うか
		/// </summary>
		bool m_isAdditionBlendMode = true;

		PartScheduler m_partScheduler;
	};
}

#endif //!GRAPHIC_EFFECT_H
