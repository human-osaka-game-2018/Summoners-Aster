#ifndef SCENE_EVENT_POST_OFFICE_H
#define SCENE_EVENT_POST_OFFICE_H

#include <vector>

#include <GameFramework.h>

#include "Scene/Scene.h"

namespace summonersaster
{
	/// <summary>
	/// シーン切り替え情報
	/// </summary>
	struct SceneSwitchEvent
	{
		Scene::KIND m_nextScene;

		/// <summary>
		/// シーンの初期化を行うべきかを判断する
		/// </summary>
		/// <remarks>
		/// 現在のシーンを初期化する必要が出てきた時に対応するため
		/// </remarks>
		bool m_shouldSwitch = false;
	};

	/// <summary>
	/// シーンに関するイベント伝達の仲介クラス
	/// </summary>
	class SceneEventPostOffice
	{
	public:
		/// <summary>
		/// イベントの受取先の登録
		/// </summary>
		/// <param name="pSceneSwitchEventPost">イベントを受け取るポインタ</param>
		static void RegisterReceiver(SceneSwitchEvent* pSceneSwitchEventPost);

		/// <summary>
		/// イベント受け取りの解除
		/// </summary>
		/// <param name="pSceneSwitchEventPost">イベントを受け取っているポインタ</param>
		static void UnregisterReceiver(SceneSwitchEvent* pSceneSwitchEventPost);

		/// <summary>
		/// 登録されている受取先全てにシーン切り替えイベントを送る
		/// </summary>
		/// <param name="nextScene">次からのシーン</param>
		static void SendSceneSwitchEvent(Scene::KIND nextScene);

	private:
		SceneEventPostOffice();
		~SceneEventPostOffice();

		static std::vector<SceneSwitchEvent*> m_pSceneSwitchEventPosts;
	};
} // namespace summonersaster

#endif //!SCENE_EVENT_POST_OFFICE_H
