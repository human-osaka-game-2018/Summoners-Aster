#ifndef SCALING_FALSH_SQUARE_H
#define SCALING_FALSH_SQUARE_H

#include <tchar.h>

#include <GameFramework.h>

#include "Behavior/Move.h"

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
	class ScalingFlashSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="diffuseAmount">拡散量</param>
		/// <param name="baseScale">基底のサイズ</param>
		/// <param name="additionDifferenceScale">大きさの誤差</param>
		/// <param name="scalingAmount">拡大量</param>
		/// <param name="startDelayFrame">何フレーム後に出現しだすか</param>
		/// <param name="occurencePos">発生位置</param>
		/// <param name="rotationZ">z軸での一フレームの回転量</param>
		/// <param name="requireFrameNum">エフェクトにかかるフレーム数</param>
		ScalingFlashSquare(const TCHAR* pTexturePath, float diffuseAmount, float baseScale, float additionDifferenceScale, 
			float scalingAmount, int startDelayFrame,
			Color originalColor, Color destColor, const D3DXVECTOR3& occurencePos, float rotationZ, int requireFrameNum);

		~ScalingFlashSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

		virtual void Render(bool isAdditionBlendMode)override;

	protected:
		ScalingFlashSquare(const ScalingFlashSquare& squareMoveToDest) = delete;

		ScalingFlashSquare& operator=(const ScalingFlashSquare& squareMoveToDest) = delete;

		const int FLASH_COUNT_MAX;
		int m_startDelayFrame = 0;
	};
}

#endif //!SCALING_FALSH_SQUARE_H
