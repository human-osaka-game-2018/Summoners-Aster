#ifndef LOCALE_H
#define LOCALE_H

#include <Windows.h>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 設置
	/// </summary>
	class Locale :public Behavior
	{
	public:
		Locale(const D3DXVECTOR3& pos);

		virtual ~Locale();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		D3DXVECTOR3 m_pos = { 0.0f, 0.0f, 0.0f };
	};
}

#endif //!LOCALE_H
