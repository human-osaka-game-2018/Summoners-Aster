#ifndef STREAM_H
#define STREAM_H

#include <d3dx9.h>

#include "../tstring.h"
#include "../Color.h"
#include "../algorithm.h"
#include "Graphic/Font.h"
#include "DirectXParam/DirectXGraphicDevice.h"
#include "DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 表示用文字列の基底クラス
	/// </summary>
	class Stream :public tstring
	{
	public:
		virtual ~Stream() {};

		inline void SetTopLeft(const D3DXVECTOR2& topLeft)
		{
			m_topLeft = topLeft;
		}

		inline void SetColor(const Color& color)
		{
			m_color = color;
		}

		inline void Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax)
		{
			m_color.m_alpha = static_cast<BYTE>(algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, alphaMin, alphaMax));
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
		}

		/// <summary>
		/// 描画を行う
		/// </summary>
		/// <param name="pFont">描画する際に扱うフォント</param>
		virtual void Render(const LPFONT pFont, UINT format) = 0;

		/// <summary>
		/// 文字列を代入する
		/// </summary>
		/// <param name="rhs">代入するTCHARのポインタ</param>
		/// <returns>thisの参照</returns>
		Stream& operator=(const TCHAR* rhs)
		{
			tstring* pThisString = static_cast<tstring*>(this);

			(*pThisString) = rhs;

			return *this;
		}

		/// <summary>
		/// 文字列を代入する
		/// </summary>
		/// <param name="rhs">代入する文字列</param>
		/// <returns>thisの参照</returns>
		Stream& operator=(const tstring& rhs)
		{
			tstring* pThisString = static_cast<tstring*>(this);

			(*pThisString) = rhs;

			return *this;
		}

	protected:
		Stream()
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		D3DXVECTOR2 m_topLeft = { 0.0f, 0.0f };
		Color m_color;
		int m_flashFrameCount = 0;

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;
	};
}

#endif //!STREAM_H
