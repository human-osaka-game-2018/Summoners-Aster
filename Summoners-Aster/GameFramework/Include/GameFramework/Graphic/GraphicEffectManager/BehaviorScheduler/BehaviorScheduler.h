#ifndef BEHAVIOR_SCHEDULER_H
#define BEHAVIOR_SCHEDULER_H

#include "../../../Vertices.h"
#include "Behavior.h"
#include "../../../../NodeSystem.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// Behaviorを決められたに処理するクラス
	/// </summary>
	class BehaviorScheduler :public NodeSystem<Behavior>
	{
	public:
		BehaviorScheduler();

		~BehaviorScheduler();

		/// <summary>
		/// 引数の矩形に動作を適用させる
		/// </summary>
		/// <param name="pVertices">適用させる矩形のポインタ</param>
		void Update(Vertices* pVertices);

	private:
		BehaviorScheduler(const BehaviorScheduler& behaviorScheduler) = delete;

		BehaviorScheduler& operator=(const BehaviorScheduler& behaviorScheduler) = delete;

		bool IsParentNodeEnded(NodeData& nodeData)override;
	};
}

#endif //!BEHAVIOR_SCHEDULER_H
