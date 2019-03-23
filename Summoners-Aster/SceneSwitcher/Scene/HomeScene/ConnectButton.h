#ifndef CONNECT_BUTTON_H
#define CONNECT_BUTTON_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class ConnectButton :public Task
	{
	public:
		ConnectButton();
		~ConnectButton();

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
		ConnectButton(ConnectButton& connectButton) = delete;

		ConnectButton& operator=(ConnectButton& connectButton) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !CONNECT_BUTTON_H


