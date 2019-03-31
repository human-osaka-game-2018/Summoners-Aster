#ifndef SHAPE_H
#define SHAPE_H

#include <random>

#include "../../../Vertices.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Verticesクラスの形を変形するクラス
	/// </summary>
	class Shape
	{
	public:
		virtual ~Shape();

		/// <summary>
		/// 引数の矩形クラスの形を変形する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void ShapeVertices(Vertices* pVertices) = 0;

	protected:
		Shape();

		std::minstd_rand m_randEngine;
	};
}

#endif //!SHAPE_H
