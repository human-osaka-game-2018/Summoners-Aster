#ifndef BUTTON_H
#define BUTTON_H

#include <tchar.h>

#include <GameFramework.h>

namespace summonersaster
{
	using gameframework::RectSize;
	using gameframework::Color;
	using gameframework::Vertices;
	using gameframework::Stream;

	/// <summary>
	/// ボタンクラス
	/// </summary>
	class Button
	{
	public:
		/// <param name="pressColor">押されている間の色</param>
		/// <param name="isCircle">	当たり判定の取り方が円か</param>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="fontSize">一文字のサイズ</param>
		/// <param name="pFontName">フォントの名前</param>
		/// <remarks>フォントのキーがnullptrなら文字を使わない</remarks>
		Button(Color pressColor = 0xFF888888, bool isCircle = false, 
			const TCHAR* pFontKey = nullptr, const RectSize& fontSize = RectSize(0.0f, 0.0f), const TCHAR* pFontName = nullptr);

		~Button();

		/// <summary>
		/// 初期化する
		/// </summary>
		void Initialize();

		/// <summary>
		/// リソースの読み込み
		/// </summary>
		void LoadResource();

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize();

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		void Release();

		bool IsUnderCursor();

		bool IsClicked();

		bool IsHeld();

		bool IsReleased();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pTexture">フレームのテクスチャ</param>
		void Render(const gameframework::LPTEXTURE pTexture);

		inline Vertices& GetFrame()
		{
			return *m_pVertices;
		}

		inline Stream& GetStream()
		{
			return *m_pStream;
		}

		inline const RectSize& GetFontSize() const
		{
			return FONT_SIZE;
		}

		/// <summary>
		/// タスクが終了しているか
		/// </summary>
		/// <returns>終了していたらtrue</returns>
		inline bool IsFinished()const
		{
			return m_isFinished;
		}

	protected:
		Button(Button& button) = delete;

		Button& operator=(Button& button) = delete;

		void RenderFrame(const gameframework::LPTEXTURE pTexture);

		void RenderStream();

		bool m_isCircle = false;

		const TCHAR* pFONT_KEY;
		const TCHAR* pFONT_NAME;
		const RectSize FONT_SIZE;

		Color m_pressColor = 0xFF888888;

		/// <summary>
		/// 終了しているか
		/// </summary>
		bool m_isFinished = false;

		Stream* m_pStream = nullptr;
		Vertices* m_pVertices = nullptr;

		gameframework::RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f,0.0f };

		gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
	};
} // namespace summonersaster

#endif // !BUTTON_H
