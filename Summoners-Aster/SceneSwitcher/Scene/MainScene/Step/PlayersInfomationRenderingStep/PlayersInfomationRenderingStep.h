#ifndef PLAYERS_INFOMATION_RENDERING_STEP_H
#define PLAYERS_INFOMATION_RENDERING_STEP_H

#include "Step.h"
#include "SwitchEventMediatorBase.h"
#include "TaskScheduler.h"
#include "PlayerIcon.h"

namespace summonersaster
{
	/// <summary>
	/// プレイヤーの情報を表示するステップ
	/// </summary>
	class PlayersInfomationRenderingStep :public Step
	{
	public:
		PlayersInfomationRenderingStep();
		~PlayersInfomationRenderingStep();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// 更新を行う
		/// </summary>
		void Update()override;

		/// <summary>
		/// 描画を行う
		/// </summary>
		void Render()override;

	private:
		PlayersInfomationRenderingStep(PlayersInfomationRenderingStep& playersInfomationRenderingStep) = delete;

		PlayersInfomationRenderingStep& operator=(PlayersInfomationRenderingStep& playersInfomationRenderingStep) = delete;

		PlayerIcon* m_pOpponentIcon;
		PlayerIcon* m_pProponentIcon;
	};
} // namespace summonersaster

#endif //!PLAYERS_INFOMATION_RENDERING_STEP_H
