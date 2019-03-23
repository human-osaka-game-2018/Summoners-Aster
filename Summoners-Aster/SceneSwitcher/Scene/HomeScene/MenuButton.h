#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class MenuButton :public Task
	{
	public:
		MenuButton();
		~MenuButton();

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
		MenuButton(MenuButton& menuButton) = delete;

		MenuButton& operator=(MenuButton& menuButton) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !MENU_BUTTON_H
