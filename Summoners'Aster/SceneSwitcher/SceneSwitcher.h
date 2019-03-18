#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <map>

#include <Singleton.h>

#include "Scene/Scene.h"

using gameframework::Singleton;

class SceneSwitcher :public Singleton<SceneSwitcher>
{
public:
	friend Singleton<SceneSwitcher>;

	~SceneSwitcher()
	{
		ReleaseSceneInstances;
	}

	inline void Update()
	{
		if (m_shouldInitialize)
		{
			SwitchScene();
		}

		m_pScenes[m_currentScene]->Update();
	}

	inline void Render()
	{
		m_pScenes[m_currentScene]->Render();
	}

	inline void RegisterNextScene(Scene::KINDS nextScene)
	{
		m_nextScene = nextScene;

		m_shouldInitialize = true;
	}

private:
	SceneSwitcher()
	{
		CreateSceneInstances();
		SwitchScene();
	}

	inline void SwitchScene()
	{
		FinalizeCurrentScene();

		m_currentScene = m_nextScene;
		InitializeCurrentScene();

		m_shouldInitialize = false;
	}

	inline void InitializeCurrentScene()
	{
		m_pScenes[m_currentScene]->Initialize();
	}

	inline void FinalizeCurrentScene()
	{
		m_pScenes[m_currentScene]->Finalize();
	}

	inline void CreateSceneInstances()
	{
		m_pScenes[Scene::KINDS::TITLE]  = new TitleScene();
		m_pScenes[Scene::KINDS::HOME]   = new HomeScene();
		m_pScenes[Scene::KINDS::BATTLE] = new TitleScene();
		m_pScenes[Scene::KINDS::RESULT] = new ResultScene();
	}

	inline void ReleaseSceneInstances()
	{
		for(auto pScene : m_pScenes)
		{
			pScene.second->Finalize();

			delete pScene.second;
		}
	}

	// <summary>
	// シーンの初期化を行うべきかを判断する
	// </summary>
	// <remarks>
	// 現在のシーンを初期化する必要が出てきた時に対応するため
	// </remarks>
	bool m_shouldInitialize = false;

	Scene::KINDS m_currentScene = Scene::KINDS::TITLE;
	Scene::KINDS m_nextScene    = Scene::KINDS::TITLE;
	
	std::map<Scene::KINDS, Scene*> m_pScenes;
};

#endif //!SCENE_SWITCHER_H
