#ifndef FOLLOW_UP_CURSOR_SQUARE_H
#define FOLLOW_UP_CURSOR_SQUARE_H

#include <tchar.h>

#include "Part.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// カーソル追従正方形
	/// </summary>
	class FollowUpCursorSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="size">サイズ</param>
		FollowUpCursorSquare(const TCHAR* pTexturePath, float size);

		~FollowUpCursorSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

	protected:
		FollowUpCursorSquare(const FollowUpCursorSquare& scalingFadeInOutCircle) = delete;

		FollowUpCursorSquare& operator=(const FollowUpCursorSquare& scalingFadeInOutCircle) = delete;
	};
}

#endif //!FOLLOW_UP_CURSOR_SQUARE_H
