#include "AbilityExecutor.h"
#include <windows.h>
#include "BattlePlayer/Players.h"

namespace summonersaster
{


AbilityExecutor::AbilityExecutor()
{
}


AbilityExecutor::~AbilityExecutor()
{
}

void AbilityExecutor::Execute(Card* card, Ability::Execute executeName)
{
	switch (executeName)
	{
	case Ability::Execute::DRAWCARD:
		Players::GetPlayer(card->Owner())->DrawCard();
		OutputDebugString(L"カードをドローします\n");
		break;
	case Ability::Execute::DIRECT_ATTACK:
	{
		PLAYER_KIND kind = (card->Owner() == PLAYER_KIND::OPPONENT) ? PLAYER_KIND::PROPONENT : PLAYER_KIND::OPPONENT;
		GameFramework& rGameFramework = GameFramework::CreateAndGetRef();
		rGameFramework.OneShotSimultaneous(L"ATTACK");
		rGameFramework.OneShotStart(L"DAMAGE");
		Players::GetPlayer(kind)->Damaged(dynamic_cast<Follower*>(card)->Attack());
		OutputDebugString(L"相手プレイヤーに直接攻撃します\n");
		break; 
	}
	default:
		OutputDebugString(L"発動できませんでした\n");
	}
}

void AbilityExecutor::Execute(FollowerData* followerData, Ability::Execute executeName)
{
	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();
	rGameFramework.OneShotSimultaneous(L"ABILITY");
	rGameFramework.RegisterGraphicEffect(
		new MovingEffect(followerData->m_pVertices->GetCenter(),
			followerData->m_pVertices->GetCenter(),
			20));

	switch (executeName)
	{
	case Ability::Execute::DRAWCARD:
		Players::GetPlayer(followerData->m_pFollower->Owner())->DrawCard();
		OutputDebugString(L"カードをドローします\n");
		break;
	case Ability::Execute::SPEED_ATTACK:
		followerData->m_isSummoned = false;
		OutputDebugString(L"召喚酔いを無くします\n");
		break;
	case Ability::Execute::DIRECT_ATTACK:
		// 自陣にいる場合に発動できる
	{
		if ((followerData->m_isOpponentZone && followerData->m_pFollower->Owner() != PLAYER_KIND::OPPONENT) ||
			(!followerData->m_isOpponentZone && followerData->m_pFollower->Owner() == PLAYER_KIND::OPPONENT)) break;

		PLAYER_KIND targetKind = (followerData->m_pFollower->Owner() == PLAYER_KIND::OPPONENT) ? PLAYER_KIND::PROPONENT : PLAYER_KIND::OPPONENT;
		rGameFramework.OneShotSimultaneous(L"ATTACK");
		rGameFramework.OneShotStart(L"DAMAGE");
		Players::GetPlayer(targetKind)->Damaged(followerData->m_pFollower->Attack());
		OutputDebugString(L"相手プレイヤーに直接攻撃します\n");
		break;
	}
	case Ability::Execute::RAISE_FRIEND_ATTACK:
	{
		Field& rField = Field::GetRef();
		FollowerData* pFollowerZone;
		rField.GetFollowerZone(&pFollowerZone);
		auto targetFollowers = followerData->m_pFollower->GetTargegtFollowers();

		targetFollowers->clear();
		targetFollowers->shrink_to_fit();

		for (int fzi = 0; fzi < rField.FIELD_FOLLOWERS_NUM; ++fzi)
		{
			//フィールドにフォロワーが存在してなければContinue
			if (pFollowerZone[fzi].m_pFollower == nullptr) continue;
			//味方のフォロワー出なければContinue
			if (pFollowerZone[fzi].m_pFollower->Owner() != followerData->m_pFollower->Owner()) continue;
			//味方のフォロワーの攻撃力をあげていく
			int attackTmp = pFollowerZone[fzi].m_pFollower->Attack() + 2;
			pFollowerZone[fzi].m_pFollower->Attack(attackTmp);
			//攻撃力を上げたフォロワーをtargetFollowersに保存しておく、死ぬときに攻撃力を戻すのに使う
			targetFollowers->push_back(pFollowerZone[fzi].m_pFollower);
		}
		OutputDebugString(L"味方の攻撃力を上昇させます\n");
		break;
	}
	case Ability::Execute::RESTORE_FRIEND_ATTACK:
	{
		Field& rField = Field::GetRef();
		FollowerData* pFollowerZone;
		rField.GetFollowerZone(&pFollowerZone);

		auto targetFollowers = followerData->m_pFollower->GetTargegtFollowers();
		for (int fzi = 0; fzi < rField.FIELD_FOLLOWERS_NUM; ++fzi)
		{
			for (auto targetFollower : *targetFollowers)
			{
				//フィールドにフォロワーが存在してなければContinue
				if (pFollowerZone[fzi].m_pFollower == nullptr) continue;
				//攻撃力を戻す対象のフォロワーでなければContinue
				if (pFollowerZone[fzi].m_pFollower != targetFollower) continue;

				//攻撃力を戻す
				targetFollower->RestoreAttack();
			}
		}
		OutputDebugString(L"上昇していた攻撃力を元に戻します\n");
		break;
	}
	default:
		OutputDebugString(L"発動できませんでした\n");
	}
}

}
