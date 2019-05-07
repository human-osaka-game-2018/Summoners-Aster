#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <unordered_map>

#include <GameFramework.h>

#include "Scene/Scene.h"
#include "SwitcherBase.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/HomeScene/HomeScene.h"
#include "Scene/MainScene/MainScene.h"
#include "Scene/DeckEditScene/DeckEditScene.h"

namespace summonersaster
{
	using gameframework::Singleton;

	/// <summary>
	/// シーンを切り替えるクラス
	/// </summary>
	class SceneSwitcher :public Singleton<SceneSwitcher>, public SwitcherBase<Scene>
	{
	public:
		friend Singleton<SceneSwitcher>;

		~SceneSwitcher();

	private:
		SceneSwitcher();

		/// <summary>
		/// 全てのシーンのインスタンスを生成する
		/// </summary>
		void CreateKindInstances()override;
	};
} // namespace summonersaster

#endif //!SCENE_SWITCHER_H
