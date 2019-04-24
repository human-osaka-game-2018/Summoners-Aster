#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <tchar.h>
#include <map>

#include "Texture.h"
#include "../GameFrameworkFactory.h"
#include "../DirectXParam/DirectXGraphicDevice.h"
#include "../DirectXParam/DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// テクスチャの管理クラス
	/// </summary>
	class TextureManager
	{
	public:
		TextureManager() 
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDeveice);
		}

		~TextureManager() 
		{
			ReleaseAll();
		}
		
		/// <summary>
		/// テクスチャの作成
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void Create(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			if (Exists(pTextureKey)) return;

			GameFrameworkFactory::Create(&m_textures[pTextureKey]);

			m_textures[pTextureKey]->Reset(pTexturePath);
		}

		/// <summary>
		/// テクスチャを再読み込み
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void Reset(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			if (!Exists(pTextureKey)) return;

			m_textures[pTextureKey]->Reset(pTexturePath);
		}

		/// <summary>
		/// 指定したテクスチャの開放
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		inline void Release(const TCHAR* pTextureKey)
		{
			if (!Exists(pTextureKey)) return;

			m_textures[pTextureKey]->Release();

			m_textures.erase(pTextureKey);
		}

		/// <summary>
		/// テクスチャの全開放
		/// </summary>
		inline void ReleaseAll()
		{
			for (auto i : m_textures)
			{
				i.second->Release();

				delete i.second;
			}

			m_textures.clear();
		}

		/// <summary>
		/// テクスチャの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>テクスチャのポインタ</returns>
		inline LPTEXTURE Get(const TCHAR* pTextureKey)
		{
			if (!Exists(pTextureKey)) return nullptr;

			return m_textures[pTextureKey]->Get();
		}

		/// <summary>
		/// テクスチャのサイズの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <param name="pTextureSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetSize(const TCHAR* pTextureKey, RectSize* pTextureSize)
		{
			if (!Exists(pTextureKey)) return;

			m_textures[pTextureKey]->GetSize(pTextureSize);
		}

		/// <summary>
		/// テクスチャが存在しているか判断する
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool Exists(const TCHAR* pTextureKey)
		{
			return (m_textures.find(pTextureKey) != m_textures.end());
		}

	private:
		TextureManager(const TextureManager& rhs) = delete;

		TextureManager& operator=(const TextureManager& rhs) = delete;

		LPDIRECT3DDEVICE m_pDirectXGraphicDeveice = nullptr;

		std::map<const TCHAR*, Texture*> m_textures;
	};
}

#endif //!TEXTURE_MANAGER_H
