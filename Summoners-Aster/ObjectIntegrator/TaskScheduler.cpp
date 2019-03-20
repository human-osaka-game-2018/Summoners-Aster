#include "TaskScheduler.h"

namespace summonersaster
{
	TaskScheduler::TaskScheduler() 
	{
	
	}

	TaskScheduler::~TaskScheduler()
	{
		ReleaseAll();
	}

	void TaskScheduler::Register(Task* pTask, int frameTakesToStart, bool hasContinuedEvenIfFinished)
	{
		TaskData taskData;
		taskData.m_pTask				   = pTask;
		taskData.m_frameTakesToStart	   = frameTakesToStart;
		taskData.m_continuedEvenIfFinished = hasContinuedEvenIfFinished;

		m_tasks.push_back(taskData);
	}

	void TaskScheduler::Update()
	{
		ReleaseNotUsingTasks();
		UpdateCanRunning();

		for (auto& task : m_tasks)
		{
			if (!task.m_canRunning) continue;

			(task.m_pTask)->Update();
		}
	}

	void TaskScheduler::Render()
	{
		std::vector<TaskData> tasksForZSort;
		tasksForZSort = m_tasks;
		std::sort(tasksForZSort.begin(), tasksForZSort.end(), IsFarther);

		for (auto& task : tasksForZSort)
		{
			if (!task.m_canRunning) continue;

			(task.m_pTask)->Render();
		}
	}

	void TaskScheduler::ReloadResources()
	{
		for (auto& task : m_tasks)
		{
			(task.m_pTask)->LoadResource();
		}
	}

	void TaskScheduler::ReleaseAll()
	{
		for (auto& task : m_tasks)
		{
			delete task.m_pTask;
		}

		m_tasks.clear();
		m_tasks.shrink_to_fit();
	}

	void TaskScheduler::UpdateCanRunning()
	{
		for (auto& task : m_tasks)
		{
			task.m_canRunning = CanRunning(task);
		}
	}

	bool TaskScheduler::CanRunning(TaskData& task)
	{
		int index = static_cast<int>(&task - &m_tasks[0]);

		/// <summary>
		/// 前のタスクからの経過時間のみで動かすことができるかを判別する
		/// </summary>
		/// <returns>処理することができるならtrue</returns>
		auto CanRunningInTermsOfFrameCount = [&]() -> bool
		{
			if ((task.m_frameTakesToStartCount++) < task.m_frameTakesToStart) return false;

			task.m_frameTakesToStartCount = task.m_frameTakesToStart;

			return true;
		};

		// 一番初めのタスクの場合は前のタスクがない
		if (index == 0)
		{
			return CanRunningInTermsOfFrameCount();
		}

		if ((m_tasks[index - 1].m_pTask)->IsFinished())
		{
			return CanRunningInTermsOfFrameCount();
		}

		return false;
	}

	void TaskScheduler::ReleaseNotUsingTasks()
	{
		for (int i = static_cast<int>(m_tasks.size() - 1); i >= 0; --i)
		{
			if (!IsNotUsingTask(m_tasks[i])) continue;

			delete m_tasks[i].m_pTask;

			// 現在のiが指し示している場所の削除
			m_tasks.erase(m_tasks.begin() + i);
		}

		m_tasks.shrink_to_fit();
	}

	bool TaskScheduler::IsNotUsingTask(const TaskData& taskData)
	{
		// タスクが完了していないか
		if (!(taskData.m_pTask->IsFinished())) return false;

		// 終了していても続けるか
		if (taskData.m_continuedEvenIfFinished) return false;

		return true;
	}

	bool TaskScheduler::IsFarther(const TaskData& compares, const TaskData& compared)
	{
		return (compares.m_pTask->GetZ() > compared.m_pTask->GetZ());
	}

} // namespace summonersaster
