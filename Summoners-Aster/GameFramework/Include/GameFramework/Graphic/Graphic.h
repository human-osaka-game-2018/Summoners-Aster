#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <Windows.h>

#include "../GameFrameworkFactory.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "ColorBlender.h"
#include "FontManager.h"
#include "GraphicEffectManager/GraphicEffectManager.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// グラフィック関係の統括クラス
	/// </summary>
	class Graphic
	{
	public:
		Graphic()
		{
			GameFrameworkFactory::Create(&m_pRenderer);
			GameFrameworkFactory::Create(&m_pColorBlender);

			Part::SetGraphicHelper(m_pColorBlender, &m_textureManager);
		}

		~Graphic()
		{
			delete m_pRenderer;
		}

		/// <summary>
		/// 描画の準備を行う
		/// </summary>
		inline void PrepareInFrame()
		{
			m_pRenderer->PrepareInFrame();
		}

		/// <summary>
		/// 描画の終了処理を行う
		/// </summary>
		inline void FinishInFrame()
		{
			m_pRenderer->FinishInFrame();
		}

		/// <summary>
		/// テクスチャの作成
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_textureManager.Create(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// テクスチャを再読み込み
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void ResetTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_textureManager.Reset(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// 指定したテクスチャの開放
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		inline void ReleaseTexture(const TCHAR* pTextureKey)
		{
			m_textureManager.Release(pTextureKey);
		}

		/// <summary>
		/// テクスチャの全開放
		/// </summary>
		inline void ReleaseAllTexture()
		{
			m_textureManager.ReleaseAll();
		}

		/// <summary>
		/// テクスチャの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>テクスチャのポインタ</returns>
		inline LPTEXTURE GetTexture(const TCHAR* pTextureKey)
		{
			return m_textureManager.Get(pTextureKey);
		}

		/// <summary>
		/// テクスチャのサイズの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <param name="pTextureSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetTextureSize(const TCHAR* pTextureKey, RectSize* pTextureSize)
		{
			m_textureManager.GetSize(pTextureKey, pTextureSize);
		}

		/// <summary>
		/// テクスチャが存在しているか判断する
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool TextureExists(const TCHAR* pTextureKey)
		{
			return m_textureManager.Exists(pTextureKey);
		}

		/// <summary>
		/// 色の合成を通常合成に変更する デフォルトでは通常合成になっている
		/// </summary>
		inline void ToDefaultBlendMode() const
		{
			m_pColorBlender->ToDefaultBlendMode();
		}

		/// <summary>
		/// 色の合成を加算合成に変更する
		/// </summary>
		inline void ToAddtionBlendMode() const
		{
			m_pColorBlender->ToAddtionBlendMode();
		}

		/// <summary>
		/// デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
		/// </summary>
		inline void SetDefaultColorBlending() const
		{
			m_pColorBlender->SetDefaultColorBlending();
		}

		/// <summary>
		/// フォントの作成
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void CreateFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_fontManager.Create(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// フォントを再読み込み
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void ResetFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_fontManager.Reset(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// 指定したフォントの開放
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		inline void ReleaseFont(const TCHAR* pFontKey)
		{
			m_fontManager.Release(pFontKey);
		}

		/// <summary>
		/// フォントの全開放
		/// </summary>
		inline void ReleaseAllFont()
		{
			m_fontManager.ReleaseAll();
		}

		/// <summary>
		/// フォントの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>フォントのポインタ</returns>
		inline LPFONT GetFont(const TCHAR* pFontKey)
		{
			return m_fontManager.Get(pFontKey);
		}

		/// <summary>
		/// フォントのサイズの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <param name="pFontSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetFontSize(const TCHAR* pFontKey, RectSize* pFontSize)
		{
			m_fontManager.GetSize(pFontKey, pFontSize);
		}

		/// <summary>
		/// フォントが存在しているか判断する
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool FontExists(const TCHAR* pFontKey)
		{
			return m_fontManager.Exists(pFontKey);
		}

		/// <summary>
		/// エフェクトの登録
		/// </summary>
		/// <param name="pGraphicEffect">登録するエフェクトのポインタ</param>
		void RegisterEffect(GraphicEffect* pGraphicEffect)
		{
			m_graphicEffectManager.Register(pGraphicEffect);
		}

		/// <summary>
		/// エフェクトの全開放
		/// </summary>
		void ReleaseAllEffect()
		{
			m_graphicEffectManager.ReleaseAll();
		}

		/// <summary>
		/// 全てのエフェクトを更新する
		/// </summary>
		void UpdateEffects()
		{
			m_graphicEffectManager.Update();
		}

		/// <summary>
		/// 全てのエフェクトを描画する
		/// </summary>
		void RenderEffects()
		{
			m_graphicEffectManager.Render();
		}

	private:
		Graphic(const Graphic& rhs) = delete;

		Graphic& operator=(const Graphic& rhs) = delete;

		Renderer* m_pRenderer = nullptr;
		ColorBlender* m_pColorBlender = nullptr;
		TextureManager m_textureManager;
		FontManager m_fontManager;
		GraphicEffectManager m_graphicEffectManager;
	};
}

#endif //!GRAPHIC_H
