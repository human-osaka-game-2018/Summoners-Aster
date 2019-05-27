#include "MainScene.h"

namespace summonersaster
{
	MainScene::MainScene()
	{

	}

	MainScene::~MainScene()
	{

	}

	void MainScene::Initialize()
	{
		Load();
	}

	void MainScene::Finalize()
	{
		GameFramework& rGameFramework = GameFramework::GetRef();
		StepSwitcher::GetRef().ReleaseInstance();
		Players::GetRef().ReleaseInstance();
		Field::GetRef().ReleaseInstance();
		FollowerOrderMediator::GetRef().ReleaseInstance();
		RotationOrderMediator::GetRef().ReleaseInstance();

		AbilityTextController::GetRef().ReleaseInstance();

		m_rGameFramework.Stop(L"BATTLE");
		ReleaseResources();
	}

	void MainScene::LoadResources()
	{
		StepSwitcher::CreateAndGetRef();
		Players::CreateAndGetRef();
		Field::CreateAndGetRef();
		AbilityTextController::CreateAndGetRef();
		BattleInformation::Initialize();

		GameFramework& rGameFramework = GameFramework::GetRef();

		RectSize windowSize;
		gameframework::WindowParam::GetWindowSize(&windowSize);

		CreateTexture(_T("BATTLE_BACK"), _T("Textures/Battle_background01.png"));

		CreateTexture(Field::pTEXTURE_KEYS[0], _T("Textures/Battle_rotationStar1.png"));
		CreateTexture(Field::pTEXTURE_KEYS[1], _T("Textures/Battle_rotationStar2.png"));
		CreateTexture(Field::pTEXTURE_KEYS[2], _T("Textures/Battle_rotationStar3.png"));
		CreateTexture(_T("DIGITAL_FILTER"), _T("Textures/Battle_digitalFilter.png"));
		
		CreateTexture(_T("PLAYER_ICON"), _T("Textures/Player.png"));
		CreateTexture(_T("FUJIZONO"), _T("Textures/fujizono.jpg"));
		CreateTexture(_T("SHION"), _T("Textures/nigaoe.jpg"));
		CreateTexture(_T("PLAYER_BACK"), _T("Textures/Battle_playerBack.png"));
		CreateTexture(_T("PLAYER_FRAME"), _T("Textures/Battle_playerFrame.png"));
		CreateTexture(_T("ROTATION_TICKET_FRAME"), _T("Textures/Battle_rotationTicketFrame.png"));
		CreateTexture(_T("ROTATION_TICKET1"), _T("Textures/Battle_rotationTicket_01.png"));
		CreateTexture(_T("ROTATION_TICKET2"), _T("Textures/Battle_rotationTicket_02.png"));
		CreateTexture(_T("ROTATION_TICKET3"), _T("Textures/Battle_rotationTicket_03.png"));
		CreateTexture(_T("END_MAIN_BUTTON"), _T("Textures/Battle_endMainButton.png"));
		CreateTexture(_T("ROTATION_BUTTON"), _T("Textures/Battle_rotationButtonR.png"));
		CreateTexture(_T("RESULT_BACK"), _T("Textures/ResultBack.png"));

		CreateTexture(_T("TURN_CIRCULE"), _T("Textures/TurnCircule.png"));

		CreateTexture(_T("CARD_BACK"), _T("Textures/Battle_cardBack.png"));

		CreateTexture(_T("MP_FRAME"), _T("Textures/Battle_mPFrame.png"));
		CreateTexture(_T("MP"), _T("Textures/Battle_mP.png"));

		CreateTexture(_T("SELECTING_CARD_FRAME"), _T("Textures/Battle_selectingCardFrame.png"));

		CreateTexture(_T("COST"), _T("Textures/Cost.png"));
		CreateTexture(_T("ATTACK"), _T("Textures/Attack.png"));
		CreateTexture(_T("HP"), _T("Textures/HP.png"));
		CreateTexture(_T("CARD_FRAME"), _T("Textures/CardFrame.png"));

		CreateTexture(_T("ATTACKED"), _T("Textures/Attacked.jpg"));
		CreateTexture(_T("MOVED"), _T("Textures/Moved.jpg"));
		CreateTexture(_T("SUMMONED"), _T("Textures/Summoned.jpg"));

		RectSize turnFontSize;
		turnFontSize.m_width = windowSize.m_width * 0.035f;
		turnFontSize.m_height = 2.0f * turnFontSize.m_width;
		CreateFont(_T("TURN_NUM"), turnFontSize, _T("IPAex明朝"));

		RectSize resultFontSize;
		resultFontSize.m_width = windowSize.m_width * 0.01f;
		resultFontSize.m_height = 2.0f * resultFontSize.m_width;
		CreateFont(_T("RESULT"), resultFontSize, _T("IPAex明朝"));

		RectSize playerNameFontSize;
		playerNameFontSize.m_width = windowSize.m_width * 0.0156f;
		playerNameFontSize.m_height = 2.0f * playerNameFontSize.m_width;
		CreateFont(_T("PLAYER_INFO"), playerNameFontSize, _T("IPAex明朝"));

		RectSize mPFontSize;
		mPFontSize.m_height = 2.0f * (mPFontSize.m_width = 18.0f);
		CreateFont(_T("MP"), mPFontSize, _T("IPAex明朝"));

		RectSize cardInfoFontSSize;
		cardInfoFontSSize.m_width = windowSize.m_width * 0.006f;
		cardInfoFontSSize.m_height = 2.0f * cardInfoFontSSize.m_width;
		CreateFont(_T("CARD_S"), cardInfoFontSSize, _T("IPAex明朝"));

		RectSize cardInfoFontMSize;
		cardInfoFontMSize.m_width = windowSize.m_width * 0.008f;
		cardInfoFontMSize.m_height = 2.0f * cardInfoFontMSize.m_width;
		CreateFont(_T("CARD_M"), cardInfoFontMSize, _T("IPAex明朝"));

		RectSize cardInfoFontLSize;
		cardInfoFontLSize.m_width = windowSize.m_width * 0.0165f;
		cardInfoFontLSize.m_height = 2.0f * cardInfoFontLSize.m_width;
		CreateFont(_T("CARD_L"), cardInfoFontLSize, _T("IPAex明朝"));
		
		const float HEGHT_MULTIPLY = 4.0f;

		RectSize cardInfoNameFontSSize;
		cardInfoNameFontSSize.m_width = windowSize.m_width * 0.002f;
		cardInfoNameFontSSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontSSize.m_width;
		CreateFont(_T("NAME_S"), cardInfoNameFontSSize, _T("IPAex明朝"));

		RectSize cardInfoNameFontMSize;
		cardInfoNameFontMSize.m_width = windowSize.m_width * 0.0027f;
		cardInfoNameFontMSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontMSize.m_width;
		CreateFont(_T("NAME_M"), cardInfoNameFontMSize, _T("IPAex明朝"));

		RectSize cardInfoNameFontLSize;
		cardInfoNameFontLSize.m_width = windowSize.m_width * 0.006f;
		cardInfoNameFontLSize.m_height = HEGHT_MULTIPLY * cardInfoNameFontLSize.m_width;
		CreateFont(_T("NAME_L"), cardInfoNameFontLSize, _T("IPAex明朝"));
		
		isLoadEnd = true;
	}

	void MainScene::Update()
	{
		StepSwitcher::GetRef().Update();

		GameFramework& rGameFramework = GameFramework::GetRef();

		if (rGameFramework.KeyboardIsPressed(DIK_ESCAPE))
		{
			SwitchEventMediatorBase<Scene>::GetRef().SendSwitchEvent(SCENE_KIND::TITLE);
		}
	}

	void MainScene::Render()
	{
		StepSwitcher::GetRef().Render();
	}

} // namespace summonersaster
