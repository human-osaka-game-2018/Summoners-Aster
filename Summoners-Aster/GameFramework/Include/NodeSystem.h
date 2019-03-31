#ifndef NODE_SYSTEM_H
#define NODE_SYSTEM_H

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 処理を指定順に行う基底クラス
	/// </summary>
	template<class T>
	class NodeSystem
	{
	public:
		/// <summary>
		/// ノードに関係の情報をまとめた構造体
		/// </summary>
		struct NodeData
		{
		public:
			T* m_pT = nullptr;

			/// <summary>
			/// 親ノードなしエフェクト開始時に動かす
			/// </summary>
			static const int DEFAULT_START = -1;

			/// <summary>
			/// 親ノードとする動作クラスのインデックス
			/// </summary>
			int m_parentNodeIndex = DEFAULT_START;

			/// <summary>
			/// 親ノードが終了してから動作を適用するまでにかけるフレーム数
			/// </summary>
			int m_frameTakesToStart = 0;

			/// <summary>
			/// 動作させるフレーム数の制限なし
			/// </summary>
			static const int UNLIMITED = -1;

			/// <summary>
			/// 動作させることができるフレーム数
			/// </summary>
			int m_runableRemainingFrame = UNLIMITED;

			/// <summary>
			/// 動かせるかどうか
			/// </summary>
			/// <remarks>
			/// NodeSystemのUpdateで判別する
			/// </remarks>
			bool m_canRunning = false;
		};

		NodeSystem()
		{

		}

		virtual ~NodeSystem()
		{
			ReleaseAll();
		}

		/// <summary>
		/// 処理の登録
		/// </summary>
		/// <param name="pT">処理のポインタ</param>
		/// <param name="parentNodeIndex">親とする処理のインデックス番号</param>
		/// <param name="frameTakesToStart">親が終了してから処理の実行までにかかるフレーム数</param>
		/// <param name="runableRemainingFrame">動かせるフレーム数</param>
		virtual void Register(T* pT, int parentNodeIndex = NodeData::DEFAULT_START, int frameTakesToStart = 0, int runableRemainingFrame = NodeData::UNLIMITED)
		{
			NodeData nodeData;
			nodeData.m_pT = pT;
			nodeData.m_parentNodeIndex = parentNodeIndex;
			nodeData.m_frameTakesToStart = frameTakesToStart;
			nodeData.m_runableRemainingFrame = runableRemainingFrame;

			m_nodeDatas.push_back(nodeData);
		}

		/// <summary>
		/// 処理の全開放
		/// </summary>
		virtual void ReleaseAll()
		{
			for (auto& nodeData : m_nodeDatas)
			{
				delete nodeData.m_pT;
			}

			if (m_nodeDatas.size() == 0) return;

			m_nodeDatas.clear();
			m_nodeDatas.shrink_to_fit();
		}

		virtual bool IsEnd()
		{
			for (auto& nodeData : m_nodeDatas)
			{
				if (nodeData.m_runableRemainingFrame != 0) return false;
			}

			return true;
		}

	protected:
		NodeSystem(const NodeSystem& nodeSystem) = delete;

		NodeSystem& operator=(const NodeSystem& nodeSystem) = delete;

		/// <summary>
		/// 全ての処理が実行できるかを更新する
		/// </summary>
		virtual void UpdateCanRunning()
		{
			for (auto& nodeData : m_nodeDatas)
			{
				nodeData.m_canRunning = CanRunning(nodeData);
			}
		}

		virtual bool CanRunning(NodeData& nodeData)
		{
			//終わってなかったら動かせない
			if (!IsParentNodeEnded(nodeData)) return false;

			//開始までまだ時間がある場合は動かせない
			if (!IsStartDelayFrameEnded(nodeData)) return false;

			//動作時間がもうない場合は動かせない
			if (IsRunnableFrameEnded(nodeData)) return false;

			return true;
		}

		virtual bool IsParentNodeEnded(NodeData& nodeData)
		{
			//親ノードが終了しているかチェック
			int index = nodeData.m_parentNodeIndex;

			//親ノードがある
			if (index != NodeData::DEFAULT_START)
			{
				//親ノードが終了していない
				if (m_nodeDatas[index].m_runableRemainingFrame != 0) return false;
			}

			return true;
		}

		virtual bool IsStartDelayFrameEnded(NodeData& nodeData)
		{
			//フレームが残っていれば終わっていない
			if ((nodeData.m_frameTakesToStart--) > 0) return false;

			nodeData.m_frameTakesToStart = 0;

			return true;
		}

		virtual bool IsRunnableFrameEnded(NodeData& nodeData)
		{
			//動作時間が無限なら終わらない
			if (nodeData.m_runableRemainingFrame == NodeData::UNLIMITED) return false;

			//フレームが残っていたら終わっていない
			if ((nodeData.m_runableRemainingFrame--) > 0) return false;

			nodeData.m_runableRemainingFrame = 0;

			return true;
		}

		std::vector<NodeData> m_nodeDatas;
	};
}

#endif //!NODE_SYSTEM_H
