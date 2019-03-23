#ifndef PLAYER_H
#define PLAYER_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class Player :public Task
	{
	public:
		Player();
		~Player();

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
		Player(Player& player) = delete;

		Player& operator=(Player& player) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !PLAYER_H


