#ifndef GAME_FRAMEWORK_H
#define GAME_FRAMEWORK_H

#include "../Singleton.h"

#include "Graphic/Graphic.h"
#include "Input/Input.h"
#include "TimerManager.h"
#include "../Collision.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	class GameFramework :public Singleton<GameFramework>
	{
	public:
		friend class Singleton<GameFramework>;

		~GameFramework() {};

		/// <summary>
		/// フレームでの開始の準備を行う
		/// </summary>
		inline void PrepareInFrame()
		{
			m_graphic.PrepareInFrame();
			m_input.PrepareInFrame();
		}

		/// <summary>
		/// フレームでの終了処理を行う
		/// </summary>
		inline void FinishInFrame()
		{
			m_graphic.FinishInFrame();
			m_input.FinishInFrame();
		}

		/// <summary>
		/// マウスカーソルが矩形の上にあるか
		/// </summary>
		/// <param name="vertices">矩形クラス</param>
		/// <returns>上にあればtrue</returns>
		inline bool IsCursorOnRect(Vertices& vertices)
		{
			POINT cursorPoint;
			CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);

			return collision::IsInner(vertices, cursorPos);
		}

		/// <summary>
		/// テクスチャの作成
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_graphic.CreateTexture(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// テクスチャを再読み込み
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void ResetTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_graphic.ResetTexture(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// 指定したテクスチャの開放
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		inline void ReleaseTexture(const TCHAR* pTextureKey)
		{
			m_graphic.ReleaseTexture(pTextureKey);
		}

		/// <summary>
		/// テクスチャの全開放
		/// </summary>
		inline void ReleaseAllTexture()
		{
			m_graphic.ReleaseAllTexture();
		}

		/// <summary>
		/// テクスチャの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>テクスチャのポインタ</returns>
		inline LPTEXTURE GetTexture(const TCHAR* pTextureKey)
		{
			return m_graphic.GetTexture(pTextureKey);
		}

		/// <summary>
		/// テクスチャのサイズの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <param name="pTextureSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetTextureSize(const TCHAR* pTextureKey, RectSize* pTextureSize)
		{
			m_graphic.GetTextureSize(pTextureKey, pTextureSize);
		}

		/// <summary>
		/// テクスチャが存在しているか判断する
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool TextureExists(const TCHAR* pTextureKey)
		{
			return m_graphic.TextureExists(pTextureKey);
		}

		/// <summary>
		/// 色の合成を通常合成に変更する デフォルトでは通常合成になっている
		/// </summary>
		inline void ToDefaultBlendMode() const
		{
			m_graphic.ToDefaultBlendMode();
		}

		/// <summary>
		/// 色の合成を加算合成に変更する
		/// </summary>
		inline void ToAddtionBlendMode() const
		{
			m_graphic.ToAddtionBlendMode();
		}

		/// <summary>
		/// デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
		/// </summary>
		inline void SetDefaultColorBlending() const
		{
			m_graphic.SetDefaultColorBlending();
		}

		/// <summary>
		/// フォントの作成
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void CreateFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_graphic.CreateFont(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// フォントを再読み込み
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void ResetFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_graphic.ResetFont(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// 指定したフォントの開放
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		inline void ReleaseFont(const TCHAR* pFontKey)
		{
			m_graphic.ReleaseFont(pFontKey);
		}

		/// <summary>
		/// フォントの全開放
		/// </summary>
		inline void ReleaseAllFont()
		{
			m_graphic.ReleaseAllFont();
		}

		/// <summary>
		/// フォントの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>フォントのポインタ</returns>
		inline LPFONT GetFont(const TCHAR* pFontKey)
		{
			return m_graphic.GetFont(pFontKey);
		}

		/// <summary>
		/// フォントのサイズの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <param name="pFontSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetFontSize(const TCHAR* pFontKey, RectSize* pFontSize)
		{
			m_graphic.GetFontSize(pFontKey, pFontSize);
		}

		/// <summary>
		/// フォントが存在しているか判断する
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool FontExists(const TCHAR* pFontKey)
		{
			return m_graphic.FontExists(pFontKey);
		}

		/// <summary>
		/// エフェクトの登録
		/// </summary>
		/// <param name="pGraphicEffect">登録するエフェクトのポインタ</param>
		void RegisterGraphicEffect(GraphicEffect* pGraphicEffect)
		{
			m_graphic.RegisterEffect(pGraphicEffect);
		}

		/// <summary>
		/// エフェクトの全開放
		/// </summary>
		void ReleaseAllGraphicEffect()
		{
			m_graphic.ReleaseAllEffect();
		}

		/// <summary>
		/// 全てのエフェクトを更新する
		/// </summary>
		void UpdateGraphicEffects()
		{
			m_graphic.UpdateEffects();
		}

		/// <summary>
		/// 全てのエフェクトを描画する
		/// </summary>
		void RenderGraphicEffects()
		{
			m_graphic.RenderEffects();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool MouseIsPressed(int key) const
		{
			return m_input.MouseIsPressed(key);
		}

		inline bool MouseIsHeld(int key) const
		{
			return m_input.MouseIsHeld(key);
		}

		inline bool MouseIsReleased(int key) const
		{
			return m_input.MouseIsReleased(key);
		}

		inline bool MouseIsNeutral(int key) const
		{
			return m_input.MouseIsNeutral(key);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool MouseAnyKeyIsPressed() const
		{
			return m_input.MouseAnyKeyIsPressed();
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			m_input.CursorPos(pPos);
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long MouseWheelScrolling() const
		{
			return m_input.MouseWheelScrolling();
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool KeyboardIsPressed(int key) const
		{
			return m_input.KeyboardIsPressed(key);
		}

		inline bool KeyboardIsHeld(int key) const
		{
			return m_input.KeyboardIsHeld(key);
		}

		inline bool KeyboardIsReleased(int key) const
		{
			return m_input.KeyboardIsReleased(key);
		}

		inline bool KeyboardIsNeutral(int key) const
		{
			return m_input.KeyboardIsNeutral(key);
		}

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool KeyboardAnyKeyIsPressed() const
		{
			return m_input.KeyboardAnyKeyIsPressed();
		}

		/// <summary>
		/// FPSの設定を行う
		/// </summary>
		/// <param name="fPS">設定したい一秒間でのフレーム数</param>
		/// <remarks>FPSを設定していなかった場合60fps</remarks>
		inline void SetFPS(int fPS)
		{
			m_timerManager.SetFPS(fPS);
		}

		/// <summary>
		/// 次のフレームに進んでいいかを判断する
		/// </summary>
		/// <returns>進んでもよければtrue</returns>
		/// <remarks>ここで一フレームにかかった時間を取得する</remarks>
		inline bool CanStartNextFrame()
		{
			return m_timerManager.CanStartNextFrame();
		}

		/// <summary>
		/// 一フレームにかかった時間(秒)を取得する
		/// </summary>
		/// <returns>経過時間(秒)</returns>
		inline float DeltaTime_sec() const
		{
			return m_timerManager.DeltaTime_sec();
		}

		/// <summary>
		/// タイマーの作成を行う
		/// </summary>
		/// <param name="pKey">生成するタイマーにつける識別キー</param>
		inline void CreateTimer(const TCHAR* pKey)
		{
			m_timerManager.Create(pKey);
		}

		/// <summary>
		/// 引数に渡されたキーのタイマーの開放
		/// </summary>
		/// <param name="pKey">開放したいタイマーのキー</param>
		inline void ReleaseTimer(const TCHAR* pKey)
		{
			m_timerManager.Release(pKey);
		}

		/// <summary>
		/// 引数に渡されたキーのタイマーが存在しているか
		/// </summary>
		/// <param name="pKey">調べたいタイマーの識別キー</param>
		/// <returns>存在していればtrue</returns>
		inline bool TimerExists(const TCHAR* pKey) const
		{
			return m_timerManager.Exists(pKey);
		}

		/// <summary>
		/// 時間の計測開始
		/// </summary>
		/// <param name="pKey">計測開始するタイマーのキー</param>
		inline void StartTimer(const TCHAR* pKey)
		{
			m_timerManager.Start(pKey);
		}

		/// <summary>
		/// 時間計測の一時停止
		/// </summary>
		/// <param name="pKey">一時停止するタイマーのキー</param>
		inline void PauseTimer(const TCHAR* pKey)
		{
			m_timerManager.Pause(pKey);
		}

		/// <summary>
		/// 時間計測のリスタート
		/// </summary>
		/// <param name="pKey">計測を再スタートさせるタイマーのキー</param>
		inline void RestartTimer(const TCHAR* pKey)
		{
			m_timerManager.Restart(pKey);
		}

		/// <summary>
		/// 時間計測の初期化
		/// </summary>
		/// <param name="pKey">初期化したいタイマーのキー</param>
		/// <remarks>計測開始時間を現在の開始時間にする</remarks>
		void ResetTimer(const TCHAR* pKey)
		{
			m_timerManager.Reset(pKey);
		}

		/// <summary>
		/// 計測時間を返す(秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_sec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_sec(pKey);
		}

		/// <summary>
		/// 計測時間を返す(ミリ秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_msec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_msec(pKey);
		}

		/// <summary>
		/// 計測時間を返す(マイクロ秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_µsec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_µsec(pKey);
		}

		/// <summary>
		/// 現在計測が止まっているかを返す
		/// </summary>
		/// <param name="pKey">止まっているかを調べるタイマーのキー</param>
		/// <returns>止まっていればtrue</returns>
		inline bool IsTimerRunning(const TCHAR* pKey)
		{
			return m_timerManager.IsRunning(pKey);
		}

	private:
		GameFramework() :m_timerManager(TimerManager::CreateAndGetRef())
		{};

		GameFramework(const GameFramework& rhs) = delete;

		GameFramework& operator=(const GameFramework& rhs) = delete;

		Graphic m_graphic;
		Input m_input;
		TimerManager& m_timerManager;
	};
}

#endif //!GAME_FRAMEWORK_H
