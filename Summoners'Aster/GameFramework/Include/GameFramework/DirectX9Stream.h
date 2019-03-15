#ifndef DIRECT_X_9_STREAM_H
#define DIRECT_X_9_STREAM_H

#include <d3dx9.h>

#include "../tstring.h"
#include "../Color.h"
#include "../algorithm.h"
#include "Graphic/Font.h"
#include "Stream.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX9の表示用文字列のクラス
	/// </summary>
	class DirectX9Stream :public Stream
	{
	public:
		DirectX9Stream() {};

		DirectX9Stream(const D3DXVECTOR2& topLeft)
		{
			m_topLeft = topLeft;
		}

		DirectX9Stream(const D3DXVECTOR2& topLeft, const Color& color)
		{
			m_topLeft = topLeft;
			m_color = color;
		}

		~DirectX9Stream() {};

		/// <summary>
		/// 描画を行う
		/// </summary>
		/// <param name="pFont">描画する際に扱うフォント</param>
		void Render(const LPFONT pFont, UINT format);
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_STREAM_H
