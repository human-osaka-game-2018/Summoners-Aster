#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H
#include <GameFramework.h>

#include "Button.h"

namespace summonersaster
{

class MenuWindow
{
public:
	MenuWindow();
	~MenuWindow();
	void Initialize();
	void LoadResource();
	void Finalize();
	void Release();
	void Render();
	void Update();
	void LocaleButton();
	void ToggleActive()
	{
		isActive = !isActive;
	}
	bool GetActive()
	{
		return isActive;
	}
private:
	bool isActive = false;
	Stream* m_pStream = nullptr;
	Vertices* m_pVertices = nullptr;

	gameframework::RectSize m_windowSize;
	D3DXVECTOR2 m_windowCenter = { 0.0f,0.0f };

	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();

	Button* m_pExitButton;
	Button* m_pSettingButton;
	Button* m_pEndGameButton;

};
}
#endif
