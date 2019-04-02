#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene/Scene.h"
#include "TaskScheduler.h"
#include "TeamLogo.h"
#include "TitleBack.h"
#include "GameTitle.h"
#include "GameTitleStar.h"
#include "InputPrompt.h"

namespace summonersaster
{
	class TitleScene :public Scene
	{
	public:
		TitleScene();
		~TitleScene();

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
		TitleScene(TitleScene& titleScene) = delete;

		TitleScene& operator=(TitleScene& titleScene) = delete;

		TaskScheduler m_taskScheduler;
	};
} // namespace summonersaster

#endif // !TITLE_SCENE_H
