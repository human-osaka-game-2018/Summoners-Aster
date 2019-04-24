#ifndef TURN_H
#define TURN_H

#include <unordered_map>

#include <GameFramework.h>

#include "TurnStage.h"
#include "SwitcherBase.h"
#include "TurnUIRenderingStage.h"
#include "PhaseOperationStage.h"
#include "BattleInformation.h"

namespace summonersaster
{
	using gameframework::Singleton;

	/// <summary>
	/// ターンクラス
	/// </summary>
	class Turn :public Singleton<Turn>, public SwitcherBase<TurnStage>
	{
	public:
		friend Singleton<Turn>;

		~Turn();

		/// <summary>
		/// 現在の段階の更新処理を行う
		/// </summary>
		/// <remarks>
		/// 段階を切り替える関数を呼ぶ
		/// </remarks>
		void Update()override;

	private:
		Turn();

		/// <summary>
		/// 全てのシーンのインスタンスを生成する
		/// </summary>
		void CreateKindInstances()override;

		void IncrementTurn();

		int m_turnNum = 1;
	};
} // namespace summonersaster

#endif //!TURN_H
