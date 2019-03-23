#ifndef DECK_BUTTON_H
#define DECK_BUTTON_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class DeckButton :public Task
	{
	public:
		DeckButton();
		~DeckButton();

		/// <summary>
		/// 初期化する
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// リソースの読み込み
		/// </summary>
		void LoadResource()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		void Release()override;

		/// <summary>
		/// 描画
		/// </summary>
		void Render()override;

	private:
		DeckButton(DeckButton& deckButton) = delete;

		DeckButton& operator=(DeckButton& deckButton) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !DECK_BUTTON_H

