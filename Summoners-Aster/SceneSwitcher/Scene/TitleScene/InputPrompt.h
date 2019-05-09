#ifndef INPUT_PROMPT_H
#define INPUT_PROMPT_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class InputPrompt :public Task
	{
	public:
		InputPrompt();
		~InputPrompt();

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

		void Update();

	private:
		InputPrompt(InputPrompt& inputPrompt) = delete;

		InputPrompt& operator=(InputPrompt& inputPrompt) = delete;

		gameframework::Stream* m_pStream = nullptr;
	};
} // namespace summonersaster

#endif // !INPUT_PROMPT_H
