﻿#ifndef CONNECT_BUTTON_H
#define CONNECT_BUTTON_H

#include <GameFramework.h>

#include "Button.h"

namespace summonersaster
{
	class ConnectButton :public Button
	{
	public:
		ConnectButton(Color pressColor = 0xFF888888, bool isCircle = false,
			const TCHAR* pFontKey = nullptr, const RectSize& fontSize = RectSize(0.0f, 0.0f), const TCHAR* pFontName = nullptr);
		~ConnectButton();

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
		ConnectButton(ConnectButton& connectButton) = delete;

		ConnectButton& operator=(ConnectButton& connectButton) = delete;

	};
} // namespace summonersaster

#endif // !CONNECT_BUTTON_H


