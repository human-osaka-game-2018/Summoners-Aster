#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <unordered_map>

#include <GameFramework.h>

#include "Scene/Scene.h"

using gameframework::Singleton;

namespace summonersaster
{
	/// <summary>
	/// シーンを切り替えるクラス
	/// </summary>
	class SceneSwitcher :public Singleton<SceneSwitcher>
	{
	public:
		friend Singleton<SceneSwitcher>;

		~SceneSwitcher();

		/// <summary>
		/// 現在のシーンの更新処理を行う
		/// </summary>
		/// <remarks>
		/// シーンを切り替える関数を呼ぶ
		/// </remarks>
		void Update();

		/// <summary>
		/// 現在のシーンの描画処理を行う
		/// </summary>
		void Render();

		/// <summary>
		/// 次のフレームから呼ばれるシーンを登録する
		/// </summary>
		/// <param name="nextScene">登録するシーン</param>
		void RegisterNextScene(Scene::KIND nextScene);

	private:
		SceneSwitcher();

		/// <summary>
		/// シーンを切り替える
		/// </summary>
		void SwitchScene();

		/// <summary>
		/// 現在のシーンの初期化処理を行う
		/// </summary>
		void InitializeCurrentScene();

		/// <summary>
		/// 現在のシーンの終了処理を行う
		/// </summary>
		void FinalizeCurrentScene();

		/// <summary>
		/// 全てのシーンのインスタンスを生成する
		/// </summary>
		void CreateSceneInstances();

		/// <summary>
		/// 全てのシーンのインスタンスを開放する
		/// </summary>
		void ReleaseSceneInstances();

		/// <summary>
		/// シーンの初期化を行うべきかを判断する
		/// </summary>
		/// <remarks>
		/// 現在のシーンを初期化する必要が出てきた時に対応するため
		/// </remarks>
		bool m_shouldInitialize = false;

		Scene::KIND m_currentScene = Scene::KIND::TITLE;
		Scene::KIND m_nextScene = Scene::KIND::TITLE;

		std::unordered_map<Scene::KIND, Scene*> m_pScenes;
	};
} // namespace summonersaster

#endif //!SCENE_SWITCHER_H
