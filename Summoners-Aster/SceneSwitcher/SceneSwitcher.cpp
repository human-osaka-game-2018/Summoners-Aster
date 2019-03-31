﻿#include "SceneSwitcher.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/HomeScene/HomeScene.h"

namespace summonersaster
{
	SceneSwitcher::~SceneSwitcher()
	{
		//SceneEventMediater::UnregisterReceiver(&m_sceneSwitchEventPost);
		ReleaseSceneInstances();
	}

	void SceneSwitcher::Update()
	{
		if (m_sceneSwitchEventPost.m_shouldSwitch)
		{
			SwitchScene();
		}

		m_pScenes[m_currentScene]->Update();
	}

	void SceneSwitcher::Render()
	{
		m_pScenes[m_currentScene]->Render();
	}

	SceneSwitcher::SceneSwitcher()
	{
		CreateSceneInstances();
		SwitchScene();
		SceneEventMediater::RegisterReceiver(&m_sceneSwitchEventPost);
	}

	void SceneSwitcher::SwitchScene()
	{
		FinalizeCurrentScene();

		m_currentScene = m_sceneSwitchEventPost.m_nextScene;
		InitializeCurrentScene();

		m_sceneSwitchEventPost.m_shouldSwitch = false;
	}

	void SceneSwitcher::InitializeCurrentScene()
	{
		m_pScenes[m_currentScene]->Initialize();
	}

	void SceneSwitcher::FinalizeCurrentScene()
	{
		m_pScenes[m_currentScene]->Finalize();
	}

	void SceneSwitcher::CreateSceneInstances()
	{
		m_pScenes[Scene::KIND::TITLE]  = new TitleScene();
		m_pScenes[Scene::KIND::HOME]   = new HomeScene();
		/*m_pScenes[Scene::KIND::BATTLE] = new BattleScene();
		m_pScenes[Scene::KIND::RESULT] = new ResultScene();*/
	}

	void SceneSwitcher::ReleaseSceneInstances()
	{
		for (auto pScene : m_pScenes)
		{
			pScene.second->Finalize();

			delete pScene.second;
		}
	}
} // namespace summonersaster
