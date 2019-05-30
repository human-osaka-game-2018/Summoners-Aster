#include "AbilityTextController.h"

namespace summonersaster
{
	using namespace gameframework;

	AbilityTextController::~AbilityTextController()
	{
		delete m_pAbilityStream;
		delete m_pBack;
		delete m_pStagingCount;
		m_rGameFramework.ReleaseFont(_T("ABILITY_TEXT"));
	}

	void AbilityTextController::Update()
	{
		if (GameFramework::GetRef().MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			SearchSelectedCard();

			m_pStagingCount->ShouldIncreased(gameframework::algorithm::Tertiary(!m_renderingCardInformation.m_pCard, false, true));
		}

		SearchAndUpgateSummonedCardState();

		m_pStagingCount->UpdateCount();
	}

	void AbilityTextController::Render()
	{
		RenderBack();

		if (m_pStagingCount->ProcessRatio() < 1.0f) return;

		RenderRemarks();
	}

	void AbilityTextController::RenderBack()
	{
		D3DXVECTOR3 pos(
			m_windowBottomRight.x * 0.1f,
			m_windowBottomRight.y * 0.75f * (2.0f - m_pStagingCount->ProcessRatio()), 0.0f);
		RectSize size(2.0f * pos.x, m_windowBottomRight.y);

		Color color(0x00000000);
		color[Color::COMPONENT::ALPHA] = static_cast<BYTE>(0xBB * m_pStagingCount->ProcessRatio());

		m_pBack->SetCenterAndSizeAndColor(pos, size, color);

		m_pBack->Render(nullptr);
	}

	void AbilityTextController::RenderRemarks()
	{
		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = 0.2f * m_windowBottomRight.x);
		
		D3DXVECTOR3 cardPos(0.5f * cardSize.m_width, m_windowBottomRight.y * 0.5f, 0.0f);

		D3DXVECTOR3 cardPosTmp = m_renderingCardInformation.m_pCard->Rect().GetCenter();
		RectSize cardSizeTmp = m_renderingCardInformation.m_pCard->Rect().GetSize();

		m_renderingCardInformation.m_pCard->Rect().GetColor()[Color::COMPONENT::ALPHA] = 0xFF;
		m_renderingCardInformation.m_pCard->Render(cardPos, cardSize, Card::RENDERING_TYPE::LARGE);

		m_renderingCardInformation.m_pCard->Rect().SetCenterAndSize(cardPosTmp, cardSizeTmp);

		D3DXVECTOR2 abilityTextTopLeft(0.0f, cardPos.y + 0.5f * cardSize.m_height);

		RenderAbilityText(m_renderingCardInformation.m_pCard->Name(), abilityTextTopLeft, m_rGameFramework.GetFont(_T("ABILITY_TEXT")));
	}

	void AbilityTextController::RenderAbilityText(const tstring& cardName, const D3DXVECTOR2& topLeft, const LPFONT& pFont)
	{
		m_pAbilityStream->SetTopLeft(topLeft);

		*m_pAbilityStream = _T("");

		std::vector<Ability> abilities = m_rCardFolder[cardName].Abilities();
		//カード効果全てを文字列に詰める
		for (auto ability : abilities)
		{
			*m_pAbilityStream += GetActivationText(ability.activationEvent, cardName);
			*m_pAbilityStream += gameframework::algorithm::Tertiary(*m_pAbilityStream == _T(""), _T(""), _T("\n"));
			*m_pAbilityStream += GetExecuteText(ability.execute, cardName);
			*m_pAbilityStream += gameframework::algorithm::Tertiary(*m_pAbilityStream == _T(""), _T(""), _T("\n\n"));
		}

		m_pAbilityStream->Render(pFont, DT_LEFT);
		RenderCardStateText();
	}

	AbilityTextController::Count::Count(int countMax) :COUNT_MAX(countMax)
	{

	}

	float AbilityTextController::Count::ProcessRatio()
	{
		return static_cast<float>(m_count) / static_cast<float>(COUNT_MAX);
	}

	void AbilityTextController::Count::UpdateCount()
	{
		if (m_shoudIncreased)
		{
			IncrementCount();

			return;
		}

		DecrementCount();
	}

	bool AbilityTextController::Count::ShouldIncreased()
	{
		return m_shoudIncreased;
	}

	void AbilityTextController::Count::ShouldIncreased(bool shouldIncreased)
	{
		m_shoudIncreased = shouldIncreased;
	}

	void AbilityTextController::Count::IncrementCount()
	{
		if (m_count >= COUNT_MAX) return;

		++m_count;
	}

	void AbilityTextController::Count::DecrementCount()
	{
		if (m_count <= 0) return;

		--m_count;
	}

	AbilityTextController::RenderingCardInformation::RenderingCardInformation()
	{
		GameFrameworkFactory::Create(&m_pSummonedStream);
		GameFrameworkFactory::Create(&m_pSummonedIcon);
		GameFrameworkFactory::Create(&m_pAttackedStream);
		GameFrameworkFactory::Create(&m_pAttackedIcon);
		GameFrameworkFactory::Create(&m_pMovedStream);
		GameFrameworkFactory::Create(&m_pMovedIcon);

		*m_pSummonedStream = _T("召喚酔い\n");
		*m_pAttackedStream = _T("攻撃酔い\n");
		*m_pMovedStream = _T("移動酔い\n");
	}

	AbilityTextController::RenderingCardInformation::~RenderingCardInformation()
	{
		delete m_pSummonedStream;
		delete m_pSummonedIcon;
		delete m_pAttackedStream;
		delete m_pAttackedIcon;
		delete m_pMovedStream;
		delete m_pMovedIcon;
	}

	AbilityTextController::AbilityTextController()
	{
		RectSize windowSize;
		gameframework::WindowParam::GetWindowSize(&windowSize);

		m_windowBottomRight = { windowSize.m_width, windowSize.m_height };

		GameFrameworkFactory::Create(&m_pAbilityStream);
		GameFrameworkFactory::Create(&m_pBack);

		m_pStagingCount = new Count(15);

		RectSize fontSize;
		fontSize.m_width = windowSize.m_width * 0.005f;
		fontSize.m_height = 2.0f * fontSize.m_width;
		m_rGameFramework.CreateFont(_T("ABILITY_TEXT"), fontSize, _T("IPAex明朝"));
	}

	void AbilityTextController::SearchSelectedCard()
	{
		SearchSelectedCardOnField();

		SearchCardRiddenCursorInHand();

		SearchCardRiddenCursorInWeaponHolder();
	}

	void AbilityTextController::SearchAndUpgateSummonedCardState()
	{
		FollowerData* pFieldCardDatas = nullptr;
		Field::GetRef().GetFollowerZone(&pFieldCardDatas);

		for (int i = 0; i < Field::FIELD_FOLLOWERS_NUM; ++i)
		{
			if (!pFieldCardDatas[i].m_pFollower) continue;

			if (pFieldCardDatas[i].m_pFollower != m_renderingCardInformation.m_pCard) continue;

			SubstituteFollowerData(pFieldCardDatas[i]);

			return;
		}
	}

	void AbilityTextController::SearchSelectedCardOnField()
	{
		FollowerData* pSelectedCard = Field::GetRef().SelectedCard();

		if (pSelectedCard)
		{
			SubstituteFollowerData(*pSelectedCard);

			m_rGameFramework.OneShotSimultaneous(L"SELECTCARD");


			return;
		}

		m_renderingCardInformation.Zero();
	}

	void AbilityTextController::SearchCardRiddenCursorInHand()
	{
		Hand* pPlayerHand = (*Players::GetRef().HBattlePlayers())[PLAYER_KIND::PROPONENT]->HHand();

		for (auto& card : *pPlayerHand->GetCards())
		{
			Card* pCard = card->HCard();

			if (!m_rGameFramework.IsCursorOnRect(pCard->Rect())) continue;

			m_renderingCardInformation.m_pCard = pCard;

			m_rGameFramework.OneShotSimultaneous(L"SELECTCARD");

			return;
		}
	}

	void AbilityTextController::SearchCardRiddenCursorInWeaponHolder()
	{
		auto SearchCard = [&](BattlePlayer* pPlayer)
		{
			WeaponHolder* pWeaponHolder = pPlayer->HWeaponHolder();

			if (!m_rGameFramework.IsCursorOnRect(*pWeaponHolder->HCollisionRect())) return;

			if (pWeaponHolder->HWeapon() == nullptr)
			{
				m_renderingCardInformation.Zero();

				return;
			}

			m_rGameFramework.OneShotSimultaneous(L"SELECTCARD");

			m_renderingCardInformation.m_pCard = pWeaponHolder->HWeapon();
		};

		for (auto& pPlayer : *Players::GetRef().HBattlePlayers())
		{
			SearchCard(pPlayer.second);
		}
	}

	void AbilityTextController::SubstituteFollowerData(const FollowerData& followerData)
	{
		m_renderingCardInformation.m_pCard = followerData.m_pFollower;

		m_renderingCardInformation.m_isAttacked = followerData.m_isAttacked;
		m_renderingCardInformation.m_isSummoned = followerData.m_isSummoned;
		m_renderingCardInformation.m_isMoved = followerData.m_isMoved;
	}

	const TCHAR* AbilityTextController::GetActivationText(ActivationEvent eventName, const tstring& cardName)
	{
		switch (eventName)
		{
		case ActivationEvent::NONE:
			return _T("");

		case ActivationEvent::ROTATE:
			return _T("このカードが回転時");

		case ActivationEvent::SUMMON:
			return _T("フィールド上にカードが\n召喚された時");

		case ActivationEvent::SUMMONED:
			return _T("このカードが召喚された時");

		case ActivationEvent::KILLED:
			return _T("このカードが破壊された時");

		case ActivationEvent::ODRERED:
			return _T("１ターンに１度発動できる");

		case ActivationEvent::MOVED:
			return _T("このカードが移動を行った時");

		case ActivationEvent::FOLLOWER_MOVED:
			return _T("フィールド上のカードが\n移動を行った時");

		case ActivationEvent::RIVAL_FOLLOWER_MOVED:
			return _T("フィールド上の相手のカードが\n移動を行った時");

		case ActivationEvent::ALLY_FOLLOWER_MOVED:
			return _T("フィールド上の自身のカードが\n移動を行った時");

		case ActivationEvent::ATTACK:
			return _T("このカードが攻撃を行った時");

		case ActivationEvent::ATTACK_RIVAL_PLAYER:
			return _T("このカードがプレイヤーに\n攻撃を行った時");

		case ActivationEvent::ATTACK_RIVAL_FOLLOWER:
			return _T("このカードが相手のカードに攻撃を行った時");

		case ActivationEvent::RIVAL_ATTACKED:
			return _T("フィールド上の相手のカードが\n攻撃を行った時");

		case ActivationEvent::ATTACKED:
			return _T("このカードに相手のカードが\n攻撃を行った時");

		case ActivationEvent::ATTACKED_ALLY_FOLLOWER:
			return _T("フィールド上の自身のカードが\n攻撃された時");

		case ActivationEvent::ATTACKED_OWNER_PLAYER:
			return _T("フィールド上の相手のカードが\nプレイヤーに攻撃を行った時");

		case ActivationEvent::KILL_RIVAL_FOLLOWER:
			return _T("このカードが相手のカードを\n攻撃し破壊した時");
		}

		return nullptr;
	}

	const TCHAR* AbilityTextController::GetExecuteText(Execute executeName, const tstring& cardName)
	{
		switch (executeName)
		{
		case Execute::DRAWCARD:
			return _T("カードを一枚ドローする。");

		case Execute::SPEED_ATTACK:
			return _T("このカードは召喚された\nターンでも攻撃または移動が\nできるようになる。");

		case Execute::DIRECT_ATTACK:
			return _T("このカードはどの位置からでも\n相手プレイヤーに\n攻撃する。");

		case Execute::RAISE_FRIEND_ATTACK:
			return _T("このカード以外の味方フォロワーの\n攻撃力を+２する。");

		case Execute::RESTORE_FRIEND_ATTACK:
			return _T("このカードの効果で攻撃力が上昇した\n全てのフォロワーの攻撃力を\nもとに戻す。");
		}

		return nullptr;
	}

	void AbilityTextController::PushBackRenderingState(std::vector<std::tuple<Vertices*, const TCHAR*, Stream*>>* pFollowerState)
	{
		if (m_renderingCardInformation.m_isSummoned)
		{
			pFollowerState->emplace_back(m_renderingCardInformation.m_pSummonedIcon,
				_T("SUMMONED"), m_renderingCardInformation.m_pSummonedStream);
		}

		if (m_renderingCardInformation.m_isAttacked)
		{
			pFollowerState->emplace_back(m_renderingCardInformation.m_pAttackedIcon,
				_T("ATTACKED"), m_renderingCardInformation.m_pAttackedStream);
		}

		if (m_renderingCardInformation.m_isMoved)
		{
			pFollowerState->emplace_back(m_renderingCardInformation.m_pMovedIcon,
				_T("MOVED"), m_renderingCardInformation.m_pMovedStream);
		}
	}

	void AbilityTextController::RenderCardStateText()
	{
		//全てのアイコンサイズは同じ
		RectSize iconSize;
		iconSize.m_width = iconSize.m_height = m_windowBottomRight.x * 0.03f;
		m_renderingCardInformation.m_pSummonedIcon->GetSize() =
		m_renderingCardInformation.m_pAttackedIcon->GetSize() =
		m_renderingCardInformation.m_pMovedIcon->GetSize() = iconSize;

		//表示すべきアイコンだけをベクターへ詰める
		std::vector<std::tuple<Vertices*, const TCHAR* ,Stream*>> followerStates;
		PushBackRenderingState(&followerStates);

		RectSize fontHalfSize;
		m_rGameFramework.GetFontSize(_T("ABILITY_TEXT"), &fontHalfSize);
		fontHalfSize = fontHalfSize * 0.5f;

		for (auto& followerState : followerStates)
		{
			int index = static_cast<int>(&followerState - &followerStates[0]);

			D3DXVECTOR3 iconTopLeft(0.0f, m_windowBottomRight.y * 0.9f, 0.0f);
			iconTopLeft.y += iconSize.m_height * index;

			Vertices* pIcon = std::get<0>(followerState);
			pIcon->SetPosByTopLeft(iconTopLeft, iconSize);
			pIcon->Render(m_rGameFramework.GetTexture(std::get<1>(followerState)));

			Stream* pStateStream = std::get<2>(followerState);

			pStateStream->SetTopLeft(D3DXVECTOR2(iconSize.m_width, pIcon->GetCenter().y - fontHalfSize.m_height));
			pStateStream->Render(m_rGameFramework.GetFont(_T("ABILITY_TEXT")), DT_LEFT);
		}
	}
}
