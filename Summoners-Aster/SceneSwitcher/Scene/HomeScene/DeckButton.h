#ifndef DECK_BUTTON_H
#define DECK_BUTTON_H

#include <GameFramework.h>

#include "Button.h"

namespace summonersaster
{
	class DeckButton :public Button
	{
	public:
		DeckButton(Color pressColor = 0xFF888888, bool isCircle = false,
			const TCHAR* pFontKey = nullptr, const RectSize& fontSize = RectSize(0.0f, 0.0f), const TCHAR* pFontName = nullptr);
		~DeckButton();

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

		void Render();


	private:
		/// <summary>
		/// 描画
		/// </summary>
		void RenderFrame();
		DeckButton(DeckButton& deckButton) = delete;

		DeckButton& operator=(DeckButton& deckButton) = delete;

	};
} // namespace summonersaster

#endif // !DECK_BUTTON_H

