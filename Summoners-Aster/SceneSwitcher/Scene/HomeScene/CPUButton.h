#ifndef CPU_BUTTON_H
#define CPU_BUTTON_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class CPUButton :public Task
	{
	public:
		CPUButton();
		~CPUButton();

		/// <summary>
		/// 初期化する
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// リソースの読み込み
		/// </summary>
		void LoadResource()override;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		void Release()override;

		/// <summary>
		/// 描画
		/// </summary>
		void Render()override;

	private:
		CPUButton(CPUButton& cpuButton) = delete;

		CPUButton& operator=(CPUButton& cpuButton) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !CPU_BUTTON_H

