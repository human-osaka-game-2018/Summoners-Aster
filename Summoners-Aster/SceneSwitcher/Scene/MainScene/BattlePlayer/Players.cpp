#include "Players.h"

namespace summonersaster
{
	using namespace gameframework;

	std::unordered_map<PLAYER_KIND, BattlePlayer*> Players::m_pBattlePlayers;

	Players::Players()
	{
		Initialize();
	}

	Players::~Players()
	{
		Finalize();
	}

	void Players::Initialize()
	{
		m_pBattlePlayers[PLAYER_KIND::OPPONENT] = new OpponentPlayer(_T("FUJIZONO"));
		m_pBattlePlayers[PLAYER_KIND::OPPONENT]->Initialize();

		m_pBattlePlayers[PLAYER_KIND::PROPONENT] = new BattlePlayer(_T("SHION"));
		m_pBattlePlayers[PLAYER_KIND::PROPONENT]->Initialize();
	}

	void Players::Finalize()
	{
		for (auto& pBattlePlayer : m_pBattlePlayers)
		{
			delete pBattlePlayer.second;
		}

		m_pBattlePlayers.clear();
	}

	bool Players::Update(const tstring& phaseName)
	{
		for (auto& player : m_pBattlePlayers)
		{
			if (player.second->HHP()->GetRemain() > 0
				|| BattleInformation::IsWaitingAction()) continue;

			PLAYER_KIND winner = algorithm::Tertiary(
				player.first == PLAYER_KIND::OPPONENT, 
				PLAYER_KIND::PROPONENT, PLAYER_KIND::OPPONENT);

			BattleInformation::Winner(winner);

			return true;
		}

		DestroyDeadFollower();

		if (phaseName == STEP_KIND::BATTLE_PREPARING)
		{
			for (auto& player : m_pBattlePlayers)
			{
				player.second->Update(phaseName);
			}

			return true;
		}

		for (auto& player : m_pBattlePlayers)
		{
			player.second->HHand()->Update();
		}

		return m_pBattlePlayers[BattleInformation::CurrentPlayer()]->Update(phaseName);
	}

	void Players::Render()
	{
		for (auto& player : m_pBattlePlayers)
		{
			player.second->Render();
		}

		return;
	}

	void Players::InitializeInMainPhaseStart()
	{
		m_pBattlePlayers[BattleInformation::CurrentPlayer()]->InitializeInMainPhaseStart();
	}

	void Players::DestroyDeadFollower()
	{
		if (BattleInformation::IsWaitingAction()) return;

		std::vector<Card*>* pCemetary;

		pCemetary = Field::GetRef().HCemeteryTmp();

		for (auto& pCard : *pCemetary)
		{
			for (auto& player : m_pBattlePlayers)
			{
				player.second->SendCardToCemetery(pCard);
			}
		}

		pCemetary->clear();
	}
}
