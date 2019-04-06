#ifndef PHASE_OPERATION_STAGE_H
#define PHASE_OPERATION_STAGE_H

#include "TurnStage.h"
#include "SwitchEventMediatorBase.h"
#include "PhaseSwitcher.h"

namespace summonersaster
{
	/// <summary>
	/// フェイズ操作
	/// </summary>
	class PhaseOperationStage :public TurnStage
	{
	public:
		PhaseOperationStage();
		~PhaseOperationStage();

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
		PhaseOperationStage(PhaseOperationStage& phaseOperationStage) = delete;

		PhaseOperationStage& operator=(PhaseOperationStage& phaseOperationStage) = delete;

		PhaseSwitcher& rPhaseSwitcher = PhaseSwitcher::CreateAndGetRef();

		SwitchEvent m_phaseSwitchEventPost;
	};
} // namespace summonersaster

#endif //!PHASE_OPERATION_STAGE_H
