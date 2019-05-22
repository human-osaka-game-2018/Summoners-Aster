#include "AbilityTextController.h"

namespace summonersaster
{
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

			m_pStagingCount->ShouldIncreased(gameframework::algorithm::Tertiary(m_selectedCardName == pNOT_FOUND, false, true));
		}

		m_pStagingCount->UpdateCount();
	}

	void AbilityTextController::Render()
	{
		RenderBack();

		if (m_pStagingCount->ProcessRatio() < 1.0f) return;

		RenderRemarks(m_selectedCardName);
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

	void AbilityTextController::RenderRemarks(const tstring& cardName)
	{
		RectSize cardSize;
		cardSize.m_height = 1.4f * (cardSize.m_width = 0.2f * m_windowBottomRight.x);
		
		D3DXVECTOR3 cardPos(0.5f * cardSize.m_width, m_windowBottomRight.y * 0.5f, 0.0f);

		m_rCardFolder.RenderCard(cardName, cardPos, cardSize);

		D3DXVECTOR2 abilityTextTopLeft(0.0f, cardPos.y + 0.5f * cardSize.m_height);

		RenderAbilityText(cardName, abilityTextTopLeft, m_rGameFramework.GetFont(_T("ABILITY_TEXT")));
	}

	void AbilityTextController::RenderAbilityText(const tstring& cardName, const D3DXVECTOR2& topLeft, const LPFONT& pFont)
	{
		m_pAbilityStream->SetTopLeft(topLeft);
		*m_pAbilityStream = GetActivationText(cardName);
		*m_pAbilityStream += gameframework::algorithm::Tertiary(*m_pAbilityStream == _T(""), _T(""), _T("\n"));
		*m_pAbilityStream += GetExecuteText(cardName);

		m_pAbilityStream->Render(pFont, DT_LEFT);
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

	AbilityTextController::AbilityTextController()
	{
		RectSize windowSize;
		gameframework::WindowParam::GetWindowSize(&windowSize);

		m_windowBottomRight = { windowSize.m_width, windowSize.m_height };

		GameFrameworkFactory::Create(&m_pAbilityStream);
		GameFrameworkFactory::Create(&m_pBack);;

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

	void AbilityTextController::SearchSelectedCardOnField()
	{
		Card* pSelectedCard = Field::GetRef().SelectedCard();

		if (pSelectedCard)
		{
			m_selectedCardName = pSelectedCard->Name();

			return;
		}

		m_selectedCardName = pNOT_FOUND;
	}

	void AbilityTextController::SearchCardRiddenCursorInHand()
	{
		Hand* pPlayerHand = (*Players::GetRef().HBattlePlayers())[PLAYER_KIND::PROPONENT]->HHand();

		for (auto& card : *pPlayerHand->GetCards())
		{
			Card* pCard = card->HCard();

			if (!m_rGameFramework.IsCursorOnRect(pCard->Rect())) continue;

			m_selectedCardName = pCard->Name();

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
				m_selectedCardName = pNOT_FOUND;

				return;
			}

			m_selectedCardName = pWeaponHolder->HWeapon()->Name();
		};

		for (auto& pPlayer : *Players::GetRef().HBattlePlayers())
		{
			SearchCard(pPlayer.second);
		}
	}

	const TCHAR* AbilityTextController::GetActivationText(const tstring& cardName)
	{
		switch (m_rCardFolder[cardName].GetActivationEvent())
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
			return _T("このカードが\n攻撃または移動を行った時");

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

	const TCHAR* AbilityTextController::GetExecuteText(const tstring& cardName)
	{
		switch (m_rCardFolder[cardName].GetExcute())
		{
		case Execute::DRAWCARD:
			return _T("カードを一枚ドローする。");

		case Execute::SPEED_ATTACK:
			return _T("このカードは召喚された\nターンでも攻撃または移動が\nできるようになる。");

		case Execute::DIRECT_ATTACK:
			return _T("このカードはどの位置からでも\n相手プレイヤーに\n攻撃できるようになる。");
		}

		return nullptr;
	}
}
