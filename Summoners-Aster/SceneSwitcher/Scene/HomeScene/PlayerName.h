#ifndef PLAYER_NAME_H
#define PLAYER_NAME_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class PlayerName :public Task
	{
	public:
		PlayerName();
		~PlayerName();

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
		PlayerName(PlayerName& playerName) = delete;

		PlayerName& operator=(PlayerName& playerName) = delete;

		gameframework::Vertices* m_pRect = nullptr;
		gameframework::Stream* m_pStream = nullptr;
	};
} // namespace summonersaster

#endif // !PLAYER_NAME_H

