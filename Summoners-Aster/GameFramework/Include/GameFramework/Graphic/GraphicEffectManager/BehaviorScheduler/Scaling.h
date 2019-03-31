#ifndef SCALING_H
#define SCALING_H

#include <Windows.h>
#include <d3dx9.h>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 拡大縮小
	/// </summary>
	class Scaling :public Behavior
	{
	public:
		/// <param name="additionalAmount">1フレームに増加させる量</param>
		Scaling(float additionalAmount);

		virtual ~Scaling();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		float m_additionalAmount = 0.0f;
	};
}

#endif //!SCALING_H
