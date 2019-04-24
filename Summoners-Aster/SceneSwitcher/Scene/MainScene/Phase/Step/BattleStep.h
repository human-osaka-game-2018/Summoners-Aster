#ifndef BATTLE_STEP_H
#define BATTLE_STEP_H

#include "Step.h"
#include "SwitchEventMediatorBase.h"
#include "TaskScheduler.h"
#include "Turn.h"

namespace summonersaster
{
	/// <summary>
	/// 対戦を行うステップ
	/// </summary>
	class BattleStep :public Step
	{
	public:
		BattleStep();
		~BattleStep();

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
		BattleStep(BattleStep& battleStep) = delete;

		BattleStep& operator=(BattleStep& battleStep) = delete;

		Turn& m_rTurn = Turn::CreateAndGetRef();
	};
} // namespace summonersaster

#endif //!BATTLE_STEP_H
