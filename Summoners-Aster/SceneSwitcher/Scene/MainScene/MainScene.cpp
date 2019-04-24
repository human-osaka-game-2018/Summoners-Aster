#include "MainScene.h"

namespace summonersaster
{
	MainScene::MainScene()
	{

	}

	MainScene::~MainScene()
	{
		m_rStepSwitcher.ReleaseInstance();
	}

	void MainScene::Initialize()
	{
		LoadResources();
	}

	void MainScene::Finalize()
	{
		GameFramework& rGameFramework = GameFramework::GetRef();

		//rGameFramework.ReleaseAllTexture();
		//rGameFramework.ReleaseAllFont();
	}

	void MainScene::LoadResources()
	{
		GameFramework& rGameFramework = GameFramework::GetRef();

		RectSize windowSize;
		gameframework::WindowParam::GetWindowSize(&windowSize);

		rGameFramework.CreateTexture(_T("BATTLE_BACK"), _T("Textures/Battle_background01.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[0], _T("Textures/Battle_rotationStar1.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[1], _T("Textures/Battle_rotationStar2.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[2], _T("Textures/Battle_rotationStar3.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[3], _T("Textures/Battle_rotationStar4.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[4], _T("Textures/Battle_rotationStar5.png"));
		rGameFramework.CreateTexture(Field::pTEXTURE_KEYS[5], _T("Textures/Battle_rotationStar6.png"));
		rGameFramework.CreateTexture(_T("DIGITAL_FILTER"), _T("Textures/Battle_digitalFilter.png"));
		
		rGameFramework.CreateTexture(_T("PLAYER_ICON"), _T("Textures/Player.png"));
		rGameFramework.CreateTexture(_T("FUJIZONO"), _T("Textures/fujizono.jpg"));
		rGameFramework.CreateTexture(_T("SHION"), _T("Textures/nigaoe.jpg"));
		rGameFramework.CreateTexture(_T("ROTATION_TICKET"), _T("Textures/Battle_rotationTicket.png"));
		rGameFramework.CreateTexture(_T("END_MAIN_BUTTON"), _T("Textures/Battle_endMainButton.png"));
		rGameFramework.CreateTexture(_T("ROTATION_BUTTON"), _T("Textures/Battle_rotationButtonR.png"));

		rGameFramework.CreateTexture(_T("CARD_BACK"), _T("Textures/Battle_cardBack.png"));

		rGameFramework.CreateTexture(_T("MP_FRAME"), _T("Textures/Battle_mPFrame.png"));
		rGameFramework.CreateTexture(_T("MP"), _T("Textures/Battle_mP.png"));

		rGameFramework.CreateTexture(_T("SELECTING_CARD_FRAME"), _T("Textures/Battle_selectingCardFrame.png"));

		rGameFramework.CreateTexture(_T("COST"), _T("Textures/Cost.png"));
		rGameFramework.CreateTexture(_T("ATTACK"), _T("Textures/Attack.png"));
		rGameFramework.CreateTexture(_T("HP"), _T("Textures/HP.png"));
		rGameFramework.CreateTexture(_T("CARD_FRAME"), _T("Textures/CardFrame.png"));

		RectSize turnFontSize;
		turnFontSize.m_width = windowSize.m_width * 0.035f;
		turnFontSize.m_height = 2.0f * turnFontSize.m_width;
		rGameFramework.CreateFont(_T("TURN_NUM"), turnFontSize, _T("IPAex明朝"));

		RectSize resultFontSize;
		resultFontSize.m_width = windowSize.m_width * 0.01f;
		resultFontSize.m_height = 2.0f * resultFontSize.m_width;
		rGameFramework.CreateFont(_T("RESULT"), resultFontSize, _T("IPAex明朝"));

		RectSize playerNameFontSize;
		playerNameFontSize.m_width = windowSize.m_width * 0.0156f;
		playerNameFontSize.m_height = 2.0f * playerNameFontSize.m_width;
		rGameFramework.CreateFont(_T("PLAYER_INFO"), playerNameFontSize, _T("IPAex明朝"));

		RectSize mPFontSize;
		mPFontSize.m_height = 2.0f * (mPFontSize.m_width = 18.0f);
		rGameFramework.CreateFont(_T("MP"), mPFontSize, _T("IPAex明朝"));

		RectSize cardInfoFontSize;
		cardInfoFontSize.m_width = windowSize.m_width * 0.008f;
		cardInfoFontSize.m_height = 2.0f * cardInfoFontSize.m_width;
		rGameFramework.CreateFont(_T("CARD"), cardInfoFontSize, _T("IPAex明朝"));
	}

	void MainScene::Update()
	{
		m_rStepSwitcher.Update();
		GameFramework& rGameFramework = GameFramework::GetRef();
		if (rGameFramework.KeyboardIsPressed(DIK_ESCAPE))
		{
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::TITLE);
		}

	}

	void MainScene::Render()
	{
		m_rStepSwitcher.Render();
	}

} // namespace summonersaster
