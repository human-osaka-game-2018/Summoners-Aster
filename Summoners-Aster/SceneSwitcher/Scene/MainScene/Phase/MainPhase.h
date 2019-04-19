#ifndef MAIN_PHASE_H
#define MAIN_PHASE_H

#include "Phase.h"
#include "SwitchEventMediatorBase.h"
#include "Button.h"
#include "RotationOrderMediator.h"

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

		void LocaleButton();

		Button* m_pEndButton = nullptr;

		RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f, 0.0f };

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif //!MAIN_PHASE_H
