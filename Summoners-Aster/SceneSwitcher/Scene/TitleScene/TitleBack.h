﻿#ifndef TITLE_BACK_H
#define TITLE_BACK_H

#include <GameFramework.h>

#include "Task.h"

namespace summonersaster
{
	class TitleBack :public Task
	{
	public:
		TitleBack();
		~TitleBack();

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
		TitleBack(TitleBack& titleBack) = delete;

		TitleBack& operator=(TitleBack& titleBack) = delete;

		gameframework::Vertices* m_pRect = nullptr;
	};
} // namespace summonersaster

#endif // !TITLE_BACK_H
