﻿#ifndef HOME_SCENE_H
#define HOME_SCENE_H

#include "../Scene.h"
#include "TaskScheduler.h"
#include "HomeBack.h"
#include "MenuButton.h"
#include "PlayerName.h"
#include "ConnectButton.h"
#include "DeckButton.h"
#include "CPUButton.h"
#include "Player.h"

namespace summonersaster
{
	class HomeScene :public Scene
	{
	public:
		HomeScene();
		~HomeScene();

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
		HomeScene(HomeScene& homeScene) = delete;

		HomeScene& operator=(HomeScene& homeScene) = delete;

		TaskScheduler m_taskScheduler;
	};
} // namespace summonersaster

#endif // !HOME_SCENE_H