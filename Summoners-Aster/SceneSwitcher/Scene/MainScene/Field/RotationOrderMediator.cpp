#include "RotationOrderMediator.h"

using namespace gameframework;
using namespace gameframework::algorithm;

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

		LoadResource();
	}

	RotationOrderMediator::~RotationOrderMediator()
	{

	}

	void RotationOrderMediator::FinalizeInEndPhaseEnd()
	{
		m_rotated = false;
	}

	void RotationOrderMediator::LoadResource()
	{
		
	}

	void RotationOrderMediator::Register(PLAYER_KIND PlayerKind, RotationTickets* pRotationPoint)
	{
		m_pPlayerRotationPoints.emplace(std::piecewise_construct,
			std::forward_as_tuple(PlayerKind),
			std::forward_as_tuple(pRotationPoint));
	}

	void RotationOrderMediator::ProcessRotationOrders()
	{
		if (m_rotated) return;

		int rotationDirectionCount = 0;

		if (m_pRRotationButton->IsReleased())
		{
			++rotationDirectionCount;
		}

		if (m_pLRotationButton->IsReleased())
		{
			--rotationDirectionCount;
		}

		if (rotationDirectionCount == 0) return;

		PLAYER_KIND currentPlayer = BattleInformation::CurrentPlayer();

		//現在のプレイヤー
		if ((*m_pPlayerRotationPoints[currentPlayer]) <= 0) return;
		--(*m_pPlayerRotationPoints[currentPlayer]);

		m_rotated = true;

		m_rField.ActivateOstensiblyCirculation(Tertiary(rotationDirectionCount > 0, true, false));
	}

	void RotationOrderMediator::Render(bool isRunning)
	{
		LPTEXTURE pTexture = m_rGameFramework.GetTexture(_T("ROTATION_BUTTON"));

		Color color = 0xFFFFFFFF;

		if ((*m_pPlayerRotationPoints[BattleInformation::CurrentPlayer()]) <= 0 || m_rotated || !isRunning)
		{
			color = 0xFF888888;
		}

		m_pRRotationButton->GetFrame().GetColor() =
		m_pLRotationButton->GetFrame().GetColor() = color;

		m_pRRotationButton->Render(pTexture);
		m_pLRotationButton->Render(pTexture);
	}

	void RotationOrderMediator::LocaleButton()
	{
		float buttonPosY = m_windowCenter.y * 1.5f;
		m_pRRotationButton->GetFrame().GetCenter() = m_pLRotationButton->GetFrame().GetCenter() =
		{ m_windowCenter.x, buttonPosY, 0.87f };

		float distanceByCenter = m_windowSize.m_width * 0.18f;
		m_pRRotationButton->GetFrame().GetCenter().x -= distanceByCenter;
		m_pLRotationButton->GetFrame().GetCenter().x += distanceByCenter;

		RectSize buttonSize;
		buttonSize.m_width = buttonSize.m_height = m_windowSize.m_width * 0.03f;

		m_pRRotationButton->GetFrame().GetSize() = m_pLRotationButton->GetFrame().GetSize() = buttonSize;

		TextureUVs inverseTextures(D3DXVECTOR2(1.0f, 0.0f), RectSize(1.0f, 1.0f), RectSize(-1.0f, 1.0f), 1);
		m_pRRotationButton->GetFrame().GetTextureUVs() = inverseTextures;
	}
} // namespace summonersaster
