#ifndef PLAYER_ICON_H
#define PLAYER_ICON_H

#include <tchar.h>

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class PlayerIcon :public Task
	{
	public:
		PlayerIcon(const TCHAR* pPlayerTextureKey, bool isOpponent);
		~PlayerIcon();

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
		PlayerIcon(PlayerIcon& playerIcon) = delete;

		PlayerIcon& operator=(PlayerIcon& playerIcon) = delete;

		void PerformPreStaging();
		void DisplayInformation();
		void PerformPostStaging();

		int m_frame = 0;

		const TCHAR* pPLAYER_TEXTURE_KEY;

		int m_preStagingTakesFrames  = 30;
		int m_displayInfoTakesFrames = 60;
		int m_postStagingTakesFrames = 30;

		bool m_isOpponent = false;

		D3DXVECTOR2 m_streamTopLeft;

		gameframework::Vertices* m_pVertices = nullptr;
		gameframework::Stream* m_pStream = nullptr;
	};
} // namespace summonersaster

#endif // !PLAYER_ICON_H
