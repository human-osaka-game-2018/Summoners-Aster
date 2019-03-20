#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <vector>

#include "Object/Task.h"

namespace summonersaster
{
	/// <summary>
	/// Taskクラスを順番に処理するクラス
	/// </summary>
	class TaskScheduler
	{
	public:
		TaskScheduler();

		~TaskScheduler();

		/// <summary>
		/// タスクの登録を行う
		/// </summary>
		/// <param name="pTask">タスクのポインタ</param>
		/// <param name="frameTakesToStart">前のタスクが終了してから動かすのにかかるフレーム数</param>
		/// <param name="hasContinuedEvenIfFinished">タスクが終了した後も解放せずに動かすか</param>
		void Register(Task* pTask, int frameTakesToStart, bool hasContinuedEvenIfFinished = false);

		/// <summary>
		/// 処理すべきタスクの更新を行う
		/// </summary>
		/// <remarks>
		/// この関数で不必要なタスクを開放し、処理すべきタスクを調べ更新する
		/// </remarks>
		void Update();

		/// <summary>
		/// 処理すべきタスクの描画を行う
		/// </summary>
		void Render();

		/// <summary>
		/// 全てのタスクのリソースを再度読み込ませる
		/// </summary>
		void ReloadResources();

		/// <summary>
		/// 全てのタスクを開放する
		/// </summary>
		void ReleaseAll();

	private:
		/// <summary>
		/// タスクとタスクに必要な情報をまとめた構造体
		/// </summary>
		struct TaskData
		{
		public:
			/// <summary>
			/// タスクのポインタ
			/// </summary>
			Task* m_pTask = nullptr;

			/// <summary>
			/// 前のタスクが終了してから動かすまでのフレーム数
			/// </summary>
			int m_frameTakesToStart = 0;

			/// <summary>
			/// タスクが終了していても動かすか
			/// </summary>
			bool m_continuedEvenIfFinished = false;

			/// <summary>
			/// 前のタスクが終了してから経過しているフレーム数
			/// </summary>
			/// <remarks>
			/// 最大値はm_frameTakesToStartと同じ
			/// </remarks>
			int m_frameTakesToStartCount = 0;

			/// <summary>
			/// 動かせるかどうか
			/// </summary>
			/// <remarks>
			/// TaskSchedulerのUpdateで判別する
			/// </remarks>
			bool m_canRunning = false;
		};

		TaskScheduler(const TaskScheduler& taskScheduler) = delete;

		TaskScheduler& operator=(const TaskScheduler& taskScheduler) = delete;

		/// <summary>
		/// 全てのタスクの処理ができるかを更新する
		/// </summary>
		void UpdateCanRunning();

		/// <summary>
		/// 引数に渡したタスクが処理できるかを判別する
		/// </summary>
		/// <param name="task">処理できるかを判別したいタスク</param>
		/// <returns>できるのならtrue</returns>
		bool CanRunning(TaskData& task);

		/// <summary>
		/// 終了し動かす必要もないタスクを開放する
		/// </summary>
		void ReleaseNotUsingTasks();

		/// <summary>
		/// もう動かす必要のないタスクかどうかを判別する
		/// </summary>
		/// <param name="taskData">調べたいタスク</param>
		/// <returns>もう使わないのならture</returns>
		bool IsNotUsingTask(const TaskData& taskData);

		/// <summary>
		/// 引数のオブジェクトを比較してどちらが遠いか判断する
		/// </summary>
		/// <param name="compares">比較する方</param>
		/// <param name="compared">比較される方</param>
		/// <returns>遠ければtrue</returns>
		static bool IsFarther(const TaskData& compares, const TaskData& compared);

		std::vector<TaskData> m_tasks;
	};
}// namespace summonersaster

#endif // !TASK_SCHEDULER_H
