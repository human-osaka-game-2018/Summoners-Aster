#ifndef CARD_ABILITY_MEDIATOR_H
#define CARD_ABILITY_MEDIATOR_H

#include "Card.h"
#include "Field.h"

namespace summonersaster
{
/// <summary>
/// 効果実行の仲介
/// </summary>
class CardAbilityMediator
{
public:
	CardAbilityMediator();
	~CardAbilityMediator();
	
	/// <summary>
	/// イベント名によって指定のカード効果を発動する
	/// </summary>
	/// <param name="activationEvent">イベント名</param>
	/// <param name="card">効果を発動させるカード</param>
	/// <returns>実行の成否</returns>
	static bool Activator(Ability::ActivationEvent activationEvent, Card* card);

	/// <summary>
	/// イベント名によって指定のカード効果を発動する
	/// </summary>
	/// <param name="activationEvent">イベント名</param>
	/// <param name="pFollowerData">効果を発動させるフォロワーデータ</param>
	/// <returns></returns>
	static bool Activator(Ability::ActivationEvent activationEvent, FollowerData* pFollowerData);

	/// <summary>
	/// カードの登録
	/// </summary>
	/// <param name="pFollowerData">登録するカードポインタ</param>
	/// <returns>実行の成否</returns>
	static bool Register(FollowerData* pFollowerData);

	/// <summary>
	/// カードの登録解除
	/// </summary>
	/// <param name="pFollowerData">登録解除するカードポインタ</param>
	/// <returns>実行の成否</returns>
	static bool Unregister(FollowerData* pFollowerData);
	
private:
	static std::vector<FollowerData*> m_pRegisteredCards;
};
}
#endif
