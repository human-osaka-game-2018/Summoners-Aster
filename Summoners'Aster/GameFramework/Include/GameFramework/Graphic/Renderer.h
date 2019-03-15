#ifndef RENDERER_H
#define RENDERER_H

#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 描画クラスの基底クラス
	/// </summary>
	class Renderer
	{
	public:
		virtual ~Renderer() {};

		/// <summary>
		/// 描画の準備を行う
		/// </summary>
		virtual void PrepareInFrame() = 0;

		/// <summary>
		/// 描画の終了処理を行う
		/// </summary>
		virtual void FinishInFrame() = 0;

	protected:
		Renderer() 
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;

	private:
		Renderer(const Renderer& rhs) = delete;

		Renderer& operator=(const Renderer& rhs) = delete;
	};
}

#endif //!RENDERER_H
