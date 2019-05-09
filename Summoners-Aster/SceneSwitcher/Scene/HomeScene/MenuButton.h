#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <GameFramework.h>

#include "Button.h"

namespace summonersaster
{
	class MenuButton :public Button
	{
	public:
		MenuButton();
		~MenuButton();

		/// <summary>
		/// 初期化する
		/// </summary>
		void Initialize();

		/// <summary>
		/// リソースの読み込み
		/// </summary>
		void LoadResource();

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		void Finalize();

		/// <summary>
		/// リソースなどの開放を行う
		/// </summary>
		void Release();

		void Render();


	private:
		/// <summary>
		/// 描画
		/// </summary>
		void RenderFrame();
		MenuButton(MenuButton& menuButton) = delete;

		MenuButton& operator=(MenuButton& menuButton) = delete;

	};
} // namespace summonersaster

#endif // !MENU_BUTTON_H
