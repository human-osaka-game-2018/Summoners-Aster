#ifndef CURSOR_H
#define CURSOR_H

#include <GameFramework.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// マウスカーソル
	/// </summary>
	class Cursor :public GraphicEffect
	{
	public:
		Cursor();

		~Cursor();

		/// <summary>
		/// 全てのパーツを更新する
		/// </summary>
		virtual void Update()override;
	};
}

#endif //!CURSOR_H
