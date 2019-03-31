#ifndef PART_SCHEDULER_H
#define PART_SCHEDULER_H

#include "../../../Vertices.h"
#include "Part.h"
#include "../../../../NodeSystem.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// エフェクトパーツを決められた順に処理する
	/// </summary>
	class PartScheduler :public NodeSystem<Part>
	{
	public:
		PartScheduler();

		~PartScheduler();

		/// <summary>
		/// エフェクトパーツの更新
		/// </summary>
		void Update();

		/// <summary>
		/// エフェクトパーツの描画
		/// </summary>
		/// <param name="isAdditionBlendMode">加算で描画するか</param>
		void Render(bool isAdditionBlendMode);

		bool IsEnd()override;

	private:
		PartScheduler(const PartScheduler& partScheduler) = delete;

		PartScheduler& operator=(const PartScheduler& partScheduler) = delete;

		/// <remarks>
		/// エフェクトパーツはそれ自体の処理が完了したかを考える必要がある
		/// </remarks>
		bool IsParentNodeEnded(NodeData& nodeData)override;

		bool IsPartEnd(const NodeData& nodeData);
	};
}

#endif //!PART_SCHEDULER_H
