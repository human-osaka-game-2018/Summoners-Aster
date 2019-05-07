#ifndef ABILITY_EXECUTOR_H
#define ABILITY_EXECUTOR_H
#include "Ability/Ability.h"
#include "Card.h"
#include "Field.h"

namespace summonersaster
{
/// <summary>
/// 効果を実行する
/// </summary>
class AbilityExecutor
{
public:
	AbilityExecutor();
	~AbilityExecutor();

	/// <summary>
	/// 効果実行
	/// </summary>
	/// <param name="card">効果を実行するカード</param>
	static void Execute(Card* card);
	/// <summary>
	/// 効果実行
	/// </summary>
	/// <param name="followerData">効果を実行するフォロワーデータ</param>
	static void Execute(FollowerData* followerData);
};
}
#endif
