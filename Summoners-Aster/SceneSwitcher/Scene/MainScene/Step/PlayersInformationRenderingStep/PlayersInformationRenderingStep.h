#ifndef PLAYERS_INFORMATION_RENDERING_STEP_H
#define PLAYERS_INFORMATION_RENDERING_STEP_H

#include "Step.h"
#include "SwitchEventMediatorBase.h"
#include "TaskScheduler.h"
#include "PlayerIcon.h"

namespace summonersaster
{
	/// <summary>
	/// プレイヤーの情報を表示するステップ
	/// </summary>
	class PlayersInformationRenderingStep :public Step
	{
	public:
		PlayersInformationRenderingStep();
		~PlayersInformationRenderingStep();

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
		PlayersInformationRenderingStep(PlayersInformationRenderingStep& playersInformationRenderingStep) = delete;

		PlayersInformationRenderingStep& operator=(PlayersInformationRenderingStep& playersInformationRenderingStep) = delete;

		void LoadPlayersInformation();

		PlayerIcon* m_pOpponentIcon;
		PlayerIcon* m_pProponentIcon;

		bool m_isLoadedPlayersInfo = false;
	};
} // namespace summonersaster

#endif //!PLAYERS_INFORMATION_RENDERING_STEP_H
