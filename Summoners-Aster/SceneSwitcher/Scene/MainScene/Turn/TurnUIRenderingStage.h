#ifndef TURN_UI_RENDERING_STAGE_H
#define TURN_UI_RENDERING_STAGE_H

#include "TurnStage.h"
#include "SwitchEventMediatorBase.h"
#include "BattleInformation.h"

namespace summonersaster
{
	using gameframework::GameFramework;
	using gameframework::RectSize;
	using gameframework::Stream;

	/// <summary>
	/// 効果を発動したり攻撃したりするフェイズ
	/// </summary>
	class TurnUIRenderingStage :public TurnStage
	{
	public:
		TurnUIRenderingStage();
		~TurnUIRenderingStage();

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
		TurnUIRenderingStage(TurnUIRenderingStage& turnUIRenderingStage) = delete;

		TurnUIRenderingStage& operator=(TurnUIRenderingStage& turnUIRenderingStage) = delete;

		void CreateTurnStream();

		RectSize m_windowSize;

		Stream* m_pStream = nullptr;

		GameFramework& m_rGameFramework = GameFramework::GetRef();
	};
} // namespace summonersaster

#endif //!TURN_UI_RENDERING_STAGE_H
