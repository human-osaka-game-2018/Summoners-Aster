#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "../../RectSize.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	using LPTEXTURE = LPDIRECT3DLPTEXTURE9;
	#elif defined DIRECT_X_VERSOIN_9
	using LPTEXTURE = LPDIRECT3DTEXTURE9;
	#else
	#error "DirectXのバージョンを定義してください"
	#endif

	/// <summary>
	/// テクスチャの基底クラス
	/// </summary>
	class Texture
	{
	public:
		virtual ~Texture()
		{
			Release();
		}

		inline void Release()
		{
			if (m_pTexture)
			{
				m_pTexture->Release();
			}

			m_pTexture = nullptr;
		}
		
		/// <summary>
		/// テクスチャを再度作成
		/// </summary>
		/// <param name="pTexturePath">テクスチャのパス</param>
		virtual void Reset(const TCHAR* pTexturePath) = 0;

		inline LPTEXTURE Get() const
		{
			return m_pTexture;
		}

		inline void GetSize(RectSize* pTextureSize) const
		{
			*pTextureSize = m_textureSize;
		}

	protected:
		Texture() {};

		LPTEXTURE m_pTexture = nullptr;

		RectSize m_textureSize;

	private:
		Texture(const Texture& rhs) = delete;

		Texture& operator=(const Texture& rhs) = delete;
	};
}

#endif //!TEXTURE_H
