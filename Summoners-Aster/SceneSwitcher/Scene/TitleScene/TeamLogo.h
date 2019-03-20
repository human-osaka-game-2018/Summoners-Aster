#include <GameFramework.h>

#include "Task.h"

#ifndef TEAM_LOGO_H
#define TEAM_LOGO_H

namespace summonersaster
{
	class TeamLogo :public Task
	{
	public:
		TeamLogo();
		~TeamLogo();

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
		TeamLogo(TeamLogo& teamLogo) = delete;

		TeamLogo& operator=(TeamLogo& teamLogo) = delete;

		/// <summary>
		/// 白背景の描画
		/// </summary>
		void RenderWhiteBack();

		/// <reamarks>
		/// ここでm_frameLeftFinishTaskAfterEndStagingを減らす
		/// </reamarks>
		void FadeIn();

		/// <summary>
		/// 演出が完了してからタスクが完了するまでのフレーム数
		/// </summary>
		int m_frameLeftFinishTaskAfterEndStaging = 90;

		gameframework::Vertices* m_pWhiteBack = nullptr;
		gameframework::Vertices* m_pRect	   = nullptr;
	};
} // namespace summonersaster

#endif // !TEAM_LOGO_H
