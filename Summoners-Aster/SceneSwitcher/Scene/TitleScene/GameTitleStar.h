#include <GameFramework.h>

#include "Task.h"

#ifndef GAME_TITLE_STAR_H
#define GAME_TITLE_STAR_H

namespace summonersaster
{
	class GameTitleStar :public Task
	{
	public:
		GameTitleStar();
		~GameTitleStar();

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
		GameTitleStar(GameTitleStar& gameTitleStar) = delete;

		GameTitleStar& operator=(GameTitleStar& gameTitleStar) = delete;

		void FadeIn();

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !GAME_TITLE_STAR_H
