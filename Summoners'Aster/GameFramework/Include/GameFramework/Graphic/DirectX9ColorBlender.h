#ifndef DIRECT_X_COLOR_9_BLENDER_H
#define DIRECT_X_COLOR_9_BLENDER_H

#include <d3dx9.h>

#include "ColorBlender.h"

#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// 色合成クラス
	/// </summary>
	class DirectX9ColorBlender :public ColorBlender
	{
	public:
		DirectX9ColorBlender() 
		{
			SetDefaultColorBlending();
		}

		~DirectX9ColorBlender() {};

		/// <summary>
		/// 色の合成を通常合成に変更する デフォルトでは通常合成になっている
		/// </summary>
		inline void ToDefaultBlendMode() const
		{
			m_pDirectXGraphicDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		/// <summary>
		/// 色の合成を加算合成に変更する
		/// </summary>
		inline void ToAddtionBlendMode() const
		{
			m_pDirectXGraphicDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		/// <summary>
		/// デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
		/// </summary>
		void SetDefaultColorBlending() const;

	private:
		DirectX9ColorBlender(const DirectX9ColorBlender& rhs) = delete;

		DirectX9ColorBlender& operator=(const DirectX9ColorBlender& rhs) = delete;
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_COLOR_9_BLENDER_H
