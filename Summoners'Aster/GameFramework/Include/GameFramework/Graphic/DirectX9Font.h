#ifndef DIRECT_X_9_FONT_H
#define DIRECT_X_9_FONT_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../DirectXParam/DirectXGraphicDevice.h"
#include "Font.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>#ifdef DIRECT_X_VERSOIN_9
namespace gameframework
{	
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX9のフォントクラス
	/// </summary>
	class DirectX9Font :public Font
	{
	public:
		DirectX9Font() {};

		DirectX9Font(const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			Reset(scale, pFontName, thickness);
		}

		~DirectX9Font() {};

		/// <summary>
		///	フォントオブジェクトの再作成
		/// </summary>
		/// <param name="scale">文字の幅</param>
		/// <param name="pFontName">フォントの名前 MSゴシック等</param>
		/// <param name="thickness">文字の太さ</param>
		void Reset(const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0);

	private:
		DirectX9Font(const DirectX9Font& rhs) = delete;

		DirectX9Font& operator=(const DirectX9Font& rhs) = delete;
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_FONT_H
