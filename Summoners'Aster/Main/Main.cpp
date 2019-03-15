#include <Windows.h>
#include <tchar.h>

#include <Window/WindowParam.h>
#include <Window/Window.h>

using WindowParam = gameframework::WindowParam;
using Window = gameframework::Window;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	WindowParam::SetInstanceHandle(hInst);

	Window* pWindow = new Window(_T("Summoners'Aster"));

	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;

	}

	delete pWindow;

	return 0;
}
