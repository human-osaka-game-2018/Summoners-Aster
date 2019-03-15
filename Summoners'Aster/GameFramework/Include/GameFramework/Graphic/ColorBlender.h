#ifndef COLOR_BLENDER_H
#define COLOR_BLENDER_H

#include <d3dx9.h>

#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// 色合成クラス
	/// </summary>
	class ColorBlender
	{
	public:
		virtual ~ColorBlender() {};

		/// <summary>
		/// 色の合成を通常合成に変更する デフォルトでは通常合成になっている
		/// </summary>
		virtual void ToDefaultBlendMode() const = 0;

		/// <summary>
		/// 色の合成を加算合成に変更する
		/// </summary>
		virtual void ToAddtionBlendMode() const = 0;

		/// <summary>
		/// デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
		/// </summary>
		virtual void SetDefaultColorBlending() const = 0;

	protected:
		ColorBlender()
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;

	private:
		ColorBlender(const ColorBlender& rhs) = delete;

		ColorBlender& operator=(const ColorBlender& rhs) = delete;
	};
}

#endif //!COLOR_BLENDER_H
