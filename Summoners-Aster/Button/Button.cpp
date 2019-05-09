#include "Button.h"

namespace summonersaster
{
	using namespace gameframework;

	Button::Button(Color pressColor, bool isCircle, const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pFontName)
		: m_pressColor(pressColor), m_isCircle(isCircle), pFONT_KEY(pFontKey), FONT_SIZE(fontSize), pFONT_NAME(pFontName)
	{
		Initialize();
	}

	Button::~Button()
	{
		Finalize();
	}

	void Button::Initialize()
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);
		m_windowCenter = { m_windowSize.m_width * 0.5f, m_windowSize.m_height * 0.5f };

		gameframework::GameFrameworkFactory::Create(&m_pStream);
		gameframework::GameFrameworkFactory::Create(&m_pVertices);

		LoadResource();
	}

	void Button::LoadResource()
	{
		if (!pFONT_KEY) return;

		m_rGameFramework.CreateFont(pFONT_KEY, FONT_SIZE, pFONT_NAME);
	}

	void Button::Finalize()
	{
		Release();
	}

	void Button::Release()
	{
		delete m_pStream;
		delete m_pVertices;
		m_rGameFramework.ReleaseFont(pFONT_KEY);
	}

	bool Button::IsUnderCursor()
	{
		if (m_isCircle)
		{
			if (!m_rGameFramework.IsCursorOnCircle(*m_pVertices)) return false;

			return true;
		}

		if (!m_rGameFramework.IsCursorOnRect(*m_pVertices)) return false;

		return true;
	}

	bool Button::IsClicked()
	{
		if (!m_rGameFramework.MouseIsPressed(gameframework::DirectX8Mouse::DIM_LEFT)) return false;

		if (IsUnderCursor()) return true;

		return false;
	}

	bool Button::IsHeld()
	{
		if (!m_rGameFramework.MouseIsHeld(gameframework::DirectX8Mouse::DIM_LEFT)) return false;

		if (IsUnderCursor()) return true;

		return false;
	}

	bool Button::IsReleased()
	{
		if (!m_rGameFramework.MouseIsReleased(gameframework::DirectX8Mouse::DIM_LEFT)) return false;

		if (IsUnderCursor()) return true;

		return false;
	}

	void Button::Render(const gameframework::LPTEXTURE pTexture)
	{
		RenderFrame(pTexture);
		RenderStream();
	}

	void Button::RenderFrame(const gameframework::LPTEXTURE pTexture)
	{
		bool isHeld = false;
		Color defaultColorBuff;

		if (IsHeld())
		{
			isHeld = true;
			defaultColorBuff = m_pVertices->GetColor();
			m_pVertices->GetColor() = m_pressColor;
		}

		m_pVertices->Render(pTexture);

		if (isHeld)
		{
			m_pVertices->GetColor() = defaultColorBuff;
		}
	}

	void Button::RenderStream()
	{
		if (!pFONT_KEY) return;

		D3DXVECTOR3& rCenter = m_pVertices->GetCenter();
		D3DXVECTOR2 topLeft = { rCenter.x, rCenter.y-GetFontSize().m_height*0.5f };
		m_pStream->SetTopLeft(topLeft);

		m_pStream->Render(m_rGameFramework.GetFont(pFONT_KEY), DT_CENTER);
	}
} // namespace summonersaster
