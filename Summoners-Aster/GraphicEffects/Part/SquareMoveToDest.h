#ifndef SQUARE_MOVE_TO_DEST_H
#define SQUARE_MOVE_TO_DEST_H

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
	class SquareMoveToDest :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="diffuseAmount">拡散量</param>
		/// <param name="scalingAmount">拡大量</param>
		/// <param name="startDelayFrame">何フレーム後に出現しだすか</param>
		/// <param name="occurencePos">発生位置</param>
		/// <param name="destPos">到達位置</param>
		/// <param name="requireFrameNum">移動にかけるフレーム数</param>
		SquareMoveToDest(const TCHAR* pTexturePath, float diffuseAmount, float scalingAmount, int startDelayFrame,
			Color originalColor, Color destColor,
			const D3DXVECTOR3& occurencePos, const D3DXVECTOR3& destPos, int requireFrameNum);

		~SquareMoveToDest();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

		virtual void Render(bool isAdditionBlendMode)override;

	protected:
		SquareMoveToDest(const SquareMoveToDest& squareMoveToDest) = delete;

		SquareMoveToDest& operator=(const SquareMoveToDest& squareMoveToDest) = delete;

		const int FLASH_COUNT_MAX = 15;
		const int LIFE_LIMIT = 3 * FLASH_COUNT_MAX;
		int m_startDelayFrame = 0;
	};
}

#endif //!SQUARE_MOVE_TO_DEST_H
