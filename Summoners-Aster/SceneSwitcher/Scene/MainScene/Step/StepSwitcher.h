#ifndef STEP_SWITCHER_H
#define STEP_SWITCHER_H

#include <unordered_map>

#include <GameFramework.h>

#include "Step.h"
#include "SwitcherBase.h"

namespace summonersaster
{
	using gameframework::Singleton;

	/// <summary>
	/// シーンを切り替えるクラス
	/// </summary>
	class StepSwitcher :public Singleton<StepSwitcher>, public SwitcherBase<Step>
	{
	public:
		friend Singleton<StepSwitcher>;

		~StepSwitcher();

	private:
		StepSwitcher();

		/// <summary>
		/// 全てのシーンのインスタンスを生成する
		/// </summary>
		void CreateKindInstances()override;
	};
} // namespace summonersaster

#endif //!STEP_SWITCHER_H
