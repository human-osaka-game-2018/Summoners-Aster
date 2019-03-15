#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

#include "../RectSize.h"
#include "WindowParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// ウィンドウ作成時に必要な情報をまとめたstaticクラス
	/// </summary>
	class Window
	{
	public:
		Window(const TCHAR* pAppName, const WNDPROC pWndProc = nullptr)
		{
			Create(pAppName, pWndProc);
		}

		~Window() {};

		/// <summary>
		/// Winメッセージが何か送られているか
		/// </summary>
		/// <returns>送られていたらtrue</returns>
		inline bool ReceivedWinMessage()
		{
			if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);

				return true;
			}

			return false;
		}

		/// <summary>
		/// ウィンドウを終了するメッセージが送られているか
		/// </summary>
		/// <returns>送られていたらtrue</returns>
		inline bool ReceivedQuitMessage() const
		{
			if (m_msg.message == WM_QUIT) return true;

			return false;
		}

	private:
		Window(const Window& rhs) = delete;

		Window& operator=(const Window& rhs) = delete;

		/// <summary>
		/// ウィンドウの生成を行う
		/// </summary>
		/// <param name="pAppName">ウィンドウの名前</param>
		/// <param name="pWndProc">ウィンドウプロシージャのポインタ</param>
		void Create(const TCHAR* pAppName, const WNDPROC pWndProc = nullptr);

		/// <summary>
		/// ウィンドウクラスを登録する
		/// </summary>
		/// <param name="pAppName">ウィンドウの名前</param>
		/// <param name="pWndProc">ウィンドウプロシージャのポインタ</param>
		/// <remarks>
		/// ウィンドウプロシージャが渡されていない場合このクラスのものが呼ばれる
		/// </remarks>
		void RegisterWindowClass(const TCHAR* pAppName, const WNDPROC pWndProc = nullptr);

		/// <summary>
		/// ウィンドウのクライアントサイズをウィンドウサイズにする
		/// </summary>
		void ResizeWindow() const;

		/// <summary>
		/// デフォルトのウィンドウプロシージャ
		/// </summary>
		/// <remarks>
		/// このクラスの引数にウィンドウプロシージャが渡されていない場合このプロシージャが扱われる
		/// </remarks>
		static LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

		MSG m_msg;
	};
}

#endif //!WINDOW_H
