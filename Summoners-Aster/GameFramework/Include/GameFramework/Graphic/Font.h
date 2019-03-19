#ifndef FONT_H
#define FONT_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../../RectSize.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	using LPFONT = LPD3DXFONT;
	#elif defined DIRECT_X_VERSOIN_9
	using LPFONT = LPD3DXFONT;
	#else
	#error "DirectXのバージョンを定義してください"
	#endif

	/// <summary>
	/// フォントの基底クラス
	/// </summary>
	class Font
	{
	public:
		virtual ~Font()
		{
			Release();
		}

		inline void Release()
		{
			if (m_pFont)
			{
				m_pFont->Release();
			}

			m_pFont = nullptr;
		}
		
		/// <summary>
		///	フォントオブジェクトの再作成
		/// </summary>
		/// <param name="scale">文字の幅</param>
		/// <param name="pFontName">フォントの名前 MSゴシック等</param>
		/// <param name="thickness">文字の太さ</param>
		virtual void Reset(const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0) = 0;

		inline LPFONT Get() const
		{
			return m_pFont;
		}

		inline void GetSize(RectSize* pFontSize) const
		{
			*pFontSize = m_fontSize;
		}

	protected:
		Font() 
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;

		LPFONT m_pFont = nullptr;

		RectSize m_fontSize;

	private:
		Font(const Font& rhs) = delete;

		Font& operator=(const Font& rhs) = delete;
	};
}

#endif //!FONT_H
