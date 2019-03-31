#ifndef ROTATION_Z_H
#define ROTATION_Z_H

#include <Windows.h>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Z軸回転
	/// </summary>
	class RotationZ :public Behavior
	{
	public:
		RotationZ(Degree degree);

		virtual ~RotationZ();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		Degree m_degree;
	};
}

#endif //!ROTATION_Z_H
