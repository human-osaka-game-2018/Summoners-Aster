#ifndef ABILITY_EXECUTOR_H
#define ABILITY_EXECUTOR_H
#include "Ability/Ability.h"
#include "Card.h"
#include "Weapon/Weapon.h"
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
	/// <param name="card">効果を発動したカード</param>
	/// <param name="executeName">発動効果の名前</param>
	static void Execute(Card* card, Ability::Execute executeName);

	/// <summary>
	/// 効果実行
	/// </summary>
	/// <param name="followerData">効果を発動したFollowerカード</param>
	/// <param name="executeName">発動効果の名前</param>
	static void Execute(FollowerData* followerData, Ability::Execute executeName);

	/// <summary>
	/// 効果実行
	/// </summary>
	/// <param name="weaponCard">効果を発動したカード</param>
	/// <param name="executeName">発動効果の名前</param>
	static void Execute(Weapon* weaponCard, Ability::Execute executeName);

};
}
#endif
