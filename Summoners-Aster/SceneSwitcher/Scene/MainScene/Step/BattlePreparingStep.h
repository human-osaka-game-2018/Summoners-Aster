#ifndef BATTLE_PREPARING_H
#define BATTLE_PREPARING_H

#include "Step.h"
#include "SwitchEventMediatorBase.h"
#include "TaskScheduler.h"

namespace summonersaster
{
	/// <summary>
	/// ドローと手札入れ替えをするステップ
	/// </summary>
	class BattlePreparingStep :public Step
	{
	public:
		BattlePreparingStep();
		~BattlePreparingStep();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// 更新を行う
		/// </summary>
		void Update()override;

		/// <summary>
		/// 描画を行う
		/// </summary>
		void Render()override;

	private:
		BattlePreparingStep(BattlePreparingStep& battlePreparingStep) = delete;

		BattlePreparingStep& operator=(BattlePreparingStep& battlePreparingStep) = delete;
	};
} // namespace summonersaster

#endif //!BATTLE_PREPARING_H
