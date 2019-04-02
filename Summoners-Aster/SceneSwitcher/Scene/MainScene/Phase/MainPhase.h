#ifndef MAIN_PHASE_H
#define MAIN_PHASE_H

#include "Phase.h"
#include "SwitchEventMediatorBase.h"
#include "Button.h"

namespace summonersaster
{
	/// <summary>
	/// 効果を発動したり攻撃したりするフェイズ
	/// </summary>
	class MainPhase :public Phase
	{
	public:
		MainPhase();
		~MainPhase();

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
		MainPhase(MainPhase& mainPhase) = delete;

		MainPhase& operator=(MainPhase& mainPhase) = delete;

		void UpdateButton();

		Button* m_pEndButton = nullptr;
	};
} // namespace summonersaster

#endif //!MAIN_PHASE_H
