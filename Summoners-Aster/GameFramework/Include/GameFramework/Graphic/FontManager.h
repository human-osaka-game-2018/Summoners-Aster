#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <tchar.h>
#include <map>

#include "Font.h"
#include "../GameFrameworkFactory.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{	
	/// <summary>
	/// フォントの管理クラス
	/// </summary>
	class FontManager
	{
	public:
		FontManager() {};

		~FontManager()
		{
			ReleaseAll();
		}
		
		/// <summary>
		/// フォントの作成
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void Create(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			if (Exists(pFontKey)) return;

			GameFrameworkFactory::Create(&m_fonts[pFontKey]);

			m_fonts[pFontKey]->Reset(scale, pFontName, thickness);
		}

		/// <summary>
		/// フォントを再読み込み
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void Reset(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_fonts[pFontKey]->Reset(scale, pFontName, thickness);
		}

		/// <summary>
		/// 指定したフォントの開放
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		inline void Release(const TCHAR* pFontKey)
		{
			if (!Exists(pFontKey)) return;

			m_fonts[pFontKey]->Release();

			m_fonts.erase(pFontKey);
		}

		/// <summary>
		/// フォントの全開放
		/// </summary>
		inline void ReleaseAll()
		{
			for (auto i : m_fonts)
			{
				i.second->Release();

				delete i.second;
			}

			m_fonts.clear();
		}

		/// <summary>
		/// フォントの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>フォントのポインタ</returns>
		inline LPFONT Get(const TCHAR* pFontKey)
		{
			if (!Exists(pFontKey)) return nullptr;

			return m_fonts[pFontKey]->Get();
		}

		/// <summary>
		/// フォントのサイズの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <param name="pFontSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetSize(const TCHAR* pFontKey, RectSize* pFontSize)
		{
			if (!Exists(pFontKey)) return;

			m_fonts[pFontKey]->GetSize(pFontSize);
		}

		/// <summary>
		/// フォントが存在しているか判断する
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool Exists(const TCHAR* pFontKey)
		{
			return (m_fonts.find(pFontKey) != m_fonts.end());
		}

	private:
		FontManager(const FontManager& rhs) = delete;

		FontManager& operator=(const FontManager& rhs) = delete;

		std::map<const TCHAR*, Font*> m_fonts;
	};
}

#endif //!FONT_MANAGER_H
