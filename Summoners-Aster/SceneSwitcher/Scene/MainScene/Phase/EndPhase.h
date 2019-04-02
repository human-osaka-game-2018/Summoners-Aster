#ifndef END_PHASE_H
#define END_PHASE_H

#include "Phase.h"
#include "SwitchEventMediatorBase.h"

namespace summonersaster
{
	/// <summary>
	/// エンドフェイズ
	/// </summary>
	class EndPhase :public Phase
	{
	public:
		EndPhase();
		~EndPhase();

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
		EndPhase(EndPhase& endPhase) = delete;

		EndPhase& operator=(EndPhase& endPhase) = delete;
	};
} // namespace summonersaster

#endif //!END_PHASE_H
