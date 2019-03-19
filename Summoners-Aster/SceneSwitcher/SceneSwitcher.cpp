#include "SceneSwitcher.h"

namespace summonersaster
{
	SceneSwitcher::~SceneSwitcher()
	{
		ReleaseSceneInstances();
	}

	void SceneSwitcher::Update()
	{
		if (m_shouldInitialize)
		{
			SwitchScene();
		}

		m_pScenes[m_currentScene]->Update();
	}

	void SceneSwitcher::Render()
	{
		m_pScenes[m_currentScene]->Render();
	}

	void SceneSwitcher::RegisterNextScene(Scene::KINDS nextScene)
	{
		m_nextScene = nextScene;

		m_shouldInitialize = true;
	}

	SceneSwitcher::SceneSwitcher()
	{
		CreateSceneInstances();
		SwitchScene();
	}

	void SceneSwitcher::SwitchScene()
	{
		FinalizeCurrentScene();

		m_currentScene = m_nextScene;
		InitializeCurrentScene();

		m_shouldInitialize = false;
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
		/*m_pScenes[Scene::KINDS::TITLE]  = new TitleScene();
		m_pScenes[Scene::KINDS::HOME]   = new HomeScene();
		m_pScenes[Scene::KINDS::BATTLE] = new BattleScene();
		m_pScenes[Scene::KINDS::RESULT] = new ResultScene();*/
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
