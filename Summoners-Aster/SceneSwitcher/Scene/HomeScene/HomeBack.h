#ifndef HOME_BACK_H
#define HOME_BACK_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class HomeBack :public Task
	{
	public:
		HomeBack();
		~HomeBack();

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
		HomeBack(HomeBack& homeBack) = delete;

		HomeBack& operator=(HomeBack& homeBack) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !HOME_BACK_H
