﻿#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <map>

#include <Singleton.h>

#include "Scene/Scene.h"

using gameframework::Singleton;

class SceneSwitcher :public Singleton<SceneSwitcher>
{
public:
	friend Singleton<SceneSwitcher>;

	~SceneSwitcher();

	void Update();
	
	void Render();

	void RegisterNextScene(Scene::KINDS nextScene);

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

	Scene::KINDS m_currentScene = Scene::KINDS::TITLE;
	Scene::KINDS m_nextScene    = Scene::KINDS::TITLE;
	
	std::map<Scene::KINDS, Scene*> m_pScenes;
};

#endif //!SCENE_SWITCHER_H