﻿#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "Scene/Scene.h"
#include "StepSwitcher.h"
#include "Field.h"
#include "BattlePlayer/BattlePlayer.h"

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

		StepSwitcher& m_rStepSwitcher = StepSwitcher::CreateAndGetRef();
		Field& m_rField = Field::CreateAndGetRef();
		BattlePlayer& m_rPlayer = BattlePlayer::CreateAndGetRef();
	};
} // namespace summonersaster

#endif // !MAIN_SCENE_H