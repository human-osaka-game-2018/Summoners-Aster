#ifndef FLASH_H
#define FLASH_H

#include <Windows.h>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 点滅
	/// </summary>
	class Flash :public Behavior
	{
	public:
		/// <param name="flashFrameMax">点滅にかかるカウント数</param>
		/// <param name="alphaMin">点滅のアルファ値の最大値</param>
		/// <param name="alphaMax">点滅のアルファ値の最小値</param>
		Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax);

		virtual ~Flash();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		int m_flashFrameMax = 0;
		BYTE m_alphaMin = 0;
		BYTE m_alphaMax = 0;
	};
}

#endif //!FLASH_H
