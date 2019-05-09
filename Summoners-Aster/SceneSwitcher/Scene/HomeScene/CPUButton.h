#ifndef CPU_BUTTON_H
#define CPU_BUTTON_H

#include <GameFramework.h>

#include "Button.h"

namespace summonersaster
{
	class CPUButton :public Button
	{
	public:
		CPUButton(Color pressColor = 0xFF888888, bool isCircle = false,
			const TCHAR* pFontKey = nullptr, const RectSize& fontSize = RectSize(0.0f, 0.0f), const TCHAR* pFontName = nullptr);
		~CPUButton();

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
		CPUButton(CPUButton& cpuButton) = delete;

		CPUButton& operator=(CPUButton& cpuButton) = delete;

	};
} // namespace summonersaster

#endif // !CPU_BUTTON_H

