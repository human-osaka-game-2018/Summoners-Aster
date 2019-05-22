#ifndef RESULT_STEP_H
#define RESULT_STEP_H

#include "Step.h"
#include "SwitchEventMediatorBase.h"
#include "TaskScheduler.h"
#include "Turn.h"
#include "Scene/Scene.h"

namespace summonersaster
{
	/// <summary>
	/// リザルトを表示するステップ
	/// </summary>
	class ResultStep :public Step
	{
	public:
		ResultStep();
		~ResultStep();

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
		ResultStep(ResultStep& resultStep) = delete;

		ResultStep& operator=(ResultStep& resultStep) = delete;

		void LoadResult();

		Stream* m_pStream = nullptr;
		Vertices* m_pVertices = nullptr;

		RectSize m_windowSize;

		static const int m_STAGING_TAKES_FRAME_MAX = 180;

		int m_stagingTakesFrames = m_STAGING_TAKES_FRAME_MAX;

		int m_periodOfFramesStagingEndToEnd = 240;

		Color m_stagingColor = 0;

		bool m_loadedResult = false;

		gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
	};
} // namespace summonersaster

#endif //!RESULT_STEP_H
