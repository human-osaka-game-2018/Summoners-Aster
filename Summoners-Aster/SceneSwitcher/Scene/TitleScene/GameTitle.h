#ifndef GAME_TITLE_H
#define GAME_TITLE_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class GameTitle :public Task
	{
	public:
		GameTitle();
		~GameTitle();

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
		GameTitle(GameTitle& gameTitle) = delete;

		GameTitle& operator=(GameTitle& gameTitle) = delete;

		/// <summary>
		/// 左から右に文字を増やしていく
		/// </summary>
		void Stage();

		gameframework::Vertices* m_pRect = nullptr;

		gameframework::RectSize m_textureUVsSize = { 0.0f, 1.0f };
	};
} // namespace summonersaster

#endif // !GAME_TITLE_H
