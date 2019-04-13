#include "RotationOrderMediator.h"

using namespace gameframework;

namespace summonersaster
{
	RotationOrderMediator::RotationOrderMediator()
	{
		gameframework::WindowParam::GetWindowSize(&m_windowSize);

		m_windowCenter.x = m_windowSize.m_width  * 0.5f;
		m_windowCenter.y = m_windowSize.m_height * 0.5f;

		m_pRRotationButton = new Button(0xFF888888, false);
		m_pLRotationButton = new Button(0xFF888888, false);

		LocaleButton();
	}

	RotationOrderMediator::~RotationOrderMediator()
	{
		m_rGameFramework.ReleaseTexture(_T("ROTATION_BUTTON"));
	}

	void RotationOrderMediator::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("ROTATION_BUTTON"), _T("Textures/Battle_rotationButtonR.png"));
	}

	void RotationOrderMediator::Register(PLAYER_KIND PlayerKind, RotationPoint* pRotationPoint)
	{
		m_pPlayerRotationPoints.emplace(PlayerKind, pRotationPoint);
	}

	void RotationOrderMediator::ProcessRotationOrders()
	{
		int rotationDirectionCount = 0;

		if (m_pRRotationButton->IsReleased())
		{
			--rotationDirectionCount;
		}

		if (m_pLRotationButton->IsReleased())
		{
			++rotationDirectionCount;
		}

		if (rotationDirectionCount == 0) return;

		//if (!((*m_pPlayerRotationPoints[現在のプレイヤー]) -= 1)) return;

		m_rField.Rotate((rotationDirectionCount > 0) ? true : false);
	}

	void RotationOrderMediator::Render()
	{
		LPTEXTURE pTexture = m_rGameFramework.GetTexture(_T("ROTATION_BUTTON"));

		m_pRRotationButton->Render(pTexture);
		m_pLRotationButton->Render(pTexture);
	}

	void RotationOrderMediator::LocaleButton()
	{
		float distanceByCenter = m_windowSize.m_width * 0.03f;
		float buttonPosY = m_windowCenter.y * 1.75f;

		m_pRRotationButton->GetFrame().GetCenter() = m_pLRotationButton->GetFrame().GetCenter() =
		{ m_windowCenter.x, buttonPosY, 0.0f };

		m_pRRotationButton->GetFrame().GetCenter().x -= distanceByCenter;
		m_pLRotationButton->GetFrame().GetCenter().x += distanceByCenter;

		RectSize buttonSize;
		buttonSize.m_width = buttonSize.m_height = m_windowSize.m_width * 0.02f;

		m_pRRotationButton->GetFrame().GetSize() = m_pRRotationButton->GetFrame().GetSize() = buttonSize;

		TextureUVs inverseTextures(D3DXVECTOR2(1.0f, 0.0f), RectSize(1.0f, 1.0f), RectSize(-1.0f, 1.0f), 1);
		m_pLRotationButton->GetFrame().GetTextureUVs() = inverseTextures;
	}
} // namespace summonersaster
