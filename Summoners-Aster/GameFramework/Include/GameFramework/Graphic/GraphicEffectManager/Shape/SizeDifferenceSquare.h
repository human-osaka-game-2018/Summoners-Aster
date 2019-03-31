#ifndef SIZE_DIFFERENCE_SQUARE_H
#define SIZE_DIFFERENCE_SQUARE_H

#include <random>

#include "Shape.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 誤差あり正方形
	/// </summary>
	class SizeDifferenceSquare :public Shape
	{
	public:
		/// <param name="sideSize">一片の長さ</param>
		/// <param name="differenceSize">一片の+方向での長さの誤差</param>
		SizeDifferenceSquare(float sideSize, float differenceSize);

		virtual ~SizeDifferenceSquare();

		/// <summary>
		/// 引数の矩形クラスの形を変形する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void ShapeVertices(Vertices* pVertices)override;

	protected:
		float m_sideSize = 0.0f;
	};
}

#endif //!SIZE_DIFFERENCE_SQUARE_H
