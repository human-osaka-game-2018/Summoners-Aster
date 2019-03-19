#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <unordered_map>

#include <GameFramework.h>

#include "Scene/Scene.h"

using gameframework::Singleton;

namespace summonersaster
{
	class SceneSwitcher :public Singleton<SceneSwitcher>
	{
	public:
		friend Singleton<SceneSwitcher>;

		~SceneSwitcher();

		void Update();

		void Render();

		void RegisterNextScene(Scene::KIND nextScene);

	private:
		SceneSwitcher();

		void SwitchScene();

		void InitializeCurrentScene();

		void FinalizeCurrentScene();

		void CreateSceneInstances();

		void ReleaseSceneInstances();

		// <summary>
		// シーンの初期化を行うべきかを判断する
		// </summary>
		// <remarks>
		// 現在のシーンを初期化する必要が出てきた時に対応するため
		// </remarks>
		bool m_shouldInitialize = false;

		Scene::KIND m_currentScene = Scene::KIND::TITLE;
		Scene::KIND m_nextScene = Scene::KIND::TITLE;

		std::unordered_map<Scene::KIND, Scene*> m_pScenes;
	};
} // namespace summonersaster

#endif //!SCENE_SWITCHER_H
