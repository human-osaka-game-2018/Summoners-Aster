#ifndef DRAW_PHASE_H
#define DRAW_PHASE_H

#include "Phase.h"
#include "SwitchEventMediatorBase.h"

namespace summonersaster
{
	/// <summary>
	/// ドローを行うフェイズ
	/// </summary>
	class DrawPhase :public Phase
	{
	public:
		DrawPhase();
		~DrawPhase();

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
		DrawPhase(DrawPhase& drawPhase) = delete;

		DrawPhase& operator=(DrawPhase& drawPhase) = delete;
	};
} // namespace summonersaster

#endif //!DRAW_PHASE_H
