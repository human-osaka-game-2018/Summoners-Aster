#include "Object.h"

#ifndef TASK_H
#define TASK_H

namespace summonersaster
{
	/// <summary>
	/// 動作の完了の概念があるObjectを継承したクラス
	/// </summary>
	class Task :public Object
	{
	public:
		virtual ~Task();

		/// <summary>
		/// タスクを初期化する
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// リソースの読み込み
		/// </summary>
		virtual void LoadResource() = 0;

		/// <summary>
		/// タスクの終了処理を行う
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		virtual void Release() = 0;

		/// <summary>
		/// タスクの更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// タスクの描画
		/// </summary>
		virtual void Render() = 0;

		/// <summary>
		/// タスクが終了しているか
		/// </summary>
		/// <returns>終了していたらtrue</returns>
		inline bool IsFinished()const
		{
			return m_isFinished;
		}

	protected:
		Task(float z);

		Task(const Task& task) = delete;

		Task& operator=(Task& task) = delete;

		/// <summary>
		/// 終了しているか
		/// </summary>
		bool m_isFinished = false;
	};
} // namespace summonersaster

#endif // !TASK_H
