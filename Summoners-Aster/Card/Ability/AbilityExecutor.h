#ifndef ABILITY_EXECUTOR_H
#define ABILITY_EXECUTOR_H
#include "Ability/Ability.h"
#include "Card.h"

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
	/// <param name="execute">実行効果種別</param>
	static void Execute(Card* card);
};
}
#endif
