#ifndef SCALING_FALSH_ABSORBED_SQUARE_H
#define SCALING_FALSH_ABSORBED_SQUARE_H

#include <tchar.h>

#include <GameFramework.h>

#include "Behavior/Move.h"
#include "Behavior/LocaleOnCircumference.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace summonersaster
{
	using gameframework::Part;
	using gameframework::Color;

	/// <summary>
	/// 任意の場所へ移動する矩形
	/// </summary>
	class ScalingFlashAbsorbedSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="diffuseAmount">拡散量</param>
		/// <param name="scalingAmount">拡大量</param>
		/// <param name="startDelayFrame">何フレーム後に出現しだすか</param>
		/// <param name="occurencePos">発生位置</param>
		/// <param name="destPos">到達位置</param>
		/// <param name="requireFrameNum">移動にかけるフレーム数</param>
		ScalingFlashAbsorbedSquare(const TCHAR* pTexturePath, float diffuseAmount, float scalingAmount, int startDelayFrame,
			Color originalColor, Color destColor, 
			float radius, float radiusDifference, const D3DXVECTOR3& destPos, int requireFrameNum);

		~ScalingFlashAbsorbedSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

		virtual void Render(bool isAdditionBlendMode)override;

	protected:
		ScalingFlashAbsorbedSquare(const ScalingFlashAbsorbedSquare& scalingFlashAbsorbedSquare) = delete;

		ScalingFlashAbsorbedSquare& operator=(const ScalingFlashAbsorbedSquare& scalingFlashAbsorbedSquare) = delete;

		const int LIFE_LIMIT;
		int m_startDelayFrame = 0;
	};
}

#endif //!SCALING_FALSH_ABSORBED_SQUARE_H
