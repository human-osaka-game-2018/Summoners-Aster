#include "Player.h"

using namespace gameframework;

namespace summonersaster
{
	Player::Player() :Task(0.0f)
	{
		Initialize();
	}

	Player::~Player()
	{
		Finalize();
	}

	void Player::Initialize()
	{
		GameFrameworkFactory::Create(&m_pRect);

		LoadResource();
	}

	void Player::LoadResource()
	{
		m_rGameFramework.CreateTexture(_T("PLAYER"), _T("Textures/Player.png"));
	}

	void Player::Finalize()
	{
		Release();
	}

	void Player::Release()
	{
		delete m_pRect;
		m_rGameFramework.ReleaseTexture(_T("PLAYER"));
	}

	void Player::Render()
	{
		m_isFinished = true;

		m_pRect->GetCenter() = { m_windowCenter.x * 0.375f, m_windowCenter.y * 1.1667f, 0.0f };
		m_pRect->SetSize(RectSize(m_windowSize.m_width * 0.3125f, m_windowSize.m_height * 0.6667f));

		m_pRect->Render(m_rGameFramework.GetTexture(_T("PLAYER")));
	}
} // namespace summonersaster
