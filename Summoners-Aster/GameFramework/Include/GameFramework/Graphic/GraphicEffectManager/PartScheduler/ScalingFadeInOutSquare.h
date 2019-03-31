#ifndef SCALING_FADE_IN_OUT_SQUARE_H
#define SCALING_FADE_IN_OUT_SQUARE_H

#include <tchar.h>

#include "Part.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 拡大縮小点滅色遷移する正方形
	/// </summary>
	class ScalingFadeInOutSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="lifeFrameMax">生存フレーム</param>
		/// <param name="scalingAmount">一フレームに拡大する量</param>
		/// <param name="originColor">初めの色</param>
		/// <param name="destColor">終わりの色</param>
		ScalingFadeInOutSquare(const TCHAR* pTexturePath, int lifeFrameMax, float scalingAmount, Color originColor, Color destColor);

		~ScalingFadeInOutSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

	protected:
		ScalingFadeInOutSquare(const ScalingFadeInOutSquare& scalingFadeInOutCircle) = delete;

		ScalingFadeInOutSquare& operator=(const ScalingFadeInOutSquare& scalingFadeInOutCircle) = delete;

		const int LIFE_FRAME_MAX;
	};
}

#endif //!SCALING_FADE_IN_OUT_SQUARE_H
