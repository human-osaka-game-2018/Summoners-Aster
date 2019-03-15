#ifndef DIRECT_X_9_TEXTURE_H
#define DIRECT_X_9_TEXTURE_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"
#include "Texture.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	#ifdef DIRECT_X_VERSOIN_9

	/// <summary>
	/// DirectX9のテクスチャクラス
	/// </summary>
	class DirectX9Texture :public Texture
	{
	public:
		DirectX9Texture() {};

		DirectX9Texture(const TCHAR* pTexturePath)
		{
			Reset(pTexturePath);
		}

		~DirectX9Texture() {};

		/// <summary>
		/// テクスチャを再度作成
		/// </summary>
		/// <param name="pTexturePath">テクスチャのパス</param>
		void Reset(const TCHAR* pTexturePath);

	private:
		DirectX9Texture(const DirectX9Texture& rhs) = delete;

		DirectX9Texture& operator=(const DirectX9Texture& rhs) = delete;
	};

	#endif //DIRECT_X_VERSOIN_9
}

#endif //!DIRECT_X_9_TEXTURE_H
