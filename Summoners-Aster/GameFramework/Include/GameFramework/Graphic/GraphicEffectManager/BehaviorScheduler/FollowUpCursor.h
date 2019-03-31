#ifndef FOLLOW_UP_CURSOR_H
#define FOLLOW_UP_CURSOR_H

#include <Windows.h>
#include <d3dx9.h>

#include "Behavior.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// マウスカーソル追従
	/// </summary>
	class FollowUpCursor :public Behavior
	{
	public:
		FollowUpCursor();

		virtual ~FollowUpCursor();

		/// <summary>
		/// 引数の矩形クラスに属性を付与する
		/// </summary>
		/// <param name="pVertices">矩形クラスのポインタ</param>
		virtual void Impart(Vertices* pVertices)override;

	protected:
		void GetPos(D3DXVECTOR3* pCursorPos);
	};
}

#endif //!FOLLOW_UP_CURSOR_H
