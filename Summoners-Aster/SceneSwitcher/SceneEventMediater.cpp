#include "SceneEventMediater.h"

namespace summonersaster
{
	std::vector<SceneSwitchEvent*> SceneEventMediater::m_pSceneSwitchEventPosts;

	void SceneEventMediater::RegisterReceiver(SceneSwitchEvent* pSceneSwitchEventPost)
	{
		m_pSceneSwitchEventPosts.push_back(pSceneSwitchEventPost);
	}

	void SceneEventMediater::UnregisterReceiver(SceneSwitchEvent* pSceneSwitchEventPost)
	{
		for (auto pPost : m_pSceneSwitchEventPosts)
		{
			int index = static_cast<int>(&pPost - &m_pSceneSwitchEventPosts[0]);

			//ポインタが同じじゃなかったら
			if (pPost != pSceneSwitchEventPost) continue;

			//要素を削除する
			m_pSceneSwitchEventPosts.erase(m_pSceneSwitchEventPosts.begin() + index);

			return;
		}
	}

	void SceneEventMediater::SendSceneSwitchEvent(Scene::KIND nextScene)
	{
		for (auto pPost : m_pSceneSwitchEventPosts)
		{
			pPost->m_nextScene = nextScene;
			pPost->m_shouldSwitch = true;
		}
	}

	SceneEventMediater::SceneEventMediater()
	{

	}

	SceneEventMediater::~SceneEventMediater()
	{

	}
} // namespace summonersaster
