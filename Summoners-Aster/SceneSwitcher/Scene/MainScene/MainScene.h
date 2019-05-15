#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <vector>

#include "Scene/Scene.h"
#include "StepSwitcher.h"
#include "Field.h"
#include "BattlePlayer/BattlePlayer.h"
#include "FollowerOrderMediator.h"
#include "RotationOrderMediator.h"
#include "CardFolder.h"

namespace summonersaster
{
	class MainScene :public Scene
	{
	public:
		MainScene();
		~MainScene();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		void LoadResources();

		/// <summary>
		/// 更新を行う
		/// </summary>
		void Update()override;

		/// <summary>
		/// 描画を行う
		/// </summary>
		void Render()override;

	private:
		MainScene(MainScene& mainScene) = delete;

		MainScene& operator=(MainScene& mainScene) = delete;
	};
} // namespace summonersaster

#endif // !MAIN_SCENE_H
