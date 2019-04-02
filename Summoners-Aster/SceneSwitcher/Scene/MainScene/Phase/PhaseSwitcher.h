#ifndef PHASE_SWITCHER_H
#define PHASE_SWITCHER_H

#include <unordered_map>

#include <GameFramework.h>

#include "Phase.h"
#include "SwitcherBase.h"

namespace summonersaster
{
	using gameframework::Singleton;

	/// <summary>
	/// シーンを切り替えるクラス
	/// </summary>
	class PhaseSwitcher :public Singleton<PhaseSwitcher>, public SwitcherBase<Phase>
	{
	public:
		friend Singleton<PhaseSwitcher>;

		~PhaseSwitcher();

	private:
		PhaseSwitcher();

		/// <summary>
		/// 全てのシーンのインスタンスを生成する
		/// </summary>
		void CreateKindInstances()override;
	};
} // namespace summonersaster

#endif //!PHASE_SWITCHER_H
