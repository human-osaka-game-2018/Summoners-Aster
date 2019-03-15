#ifndef DIRECT_X_9_RENDERER_H
#define DIRECT_X_9_RENDERER_H

#include "Renderer.h"
#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX9の描画クラス
	/// </summary>
	/// <seealso cref="Renderer" />
	class DirectX9Renderer :public Renderer
	{
	public:
		DirectX9Renderer() 
		{
			m_pDirectXGraphicDevice->SetRenderState(D3DRS_ZENABLE, true);
		}

		~DirectX9Renderer() {};
		
		/// <summary>
		/// 描画の準備を行う
		/// </summary>
		void PrepareInFrame();
		
		/// <summary>
		/// 描画の終了処理を行う
		/// </summary>
		void FinishInFrame();

	private:
		DirectX9Renderer(const DirectX9Renderer& rhs) = delete;

		DirectX9Renderer& operator=(const DirectX9Renderer& rhs) = delete;
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_RENDERER_H
