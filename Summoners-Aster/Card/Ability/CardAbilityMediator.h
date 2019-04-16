#ifndef CARD_ABILITY_MEDIATOR_H
#define CARD_ABILITY_MEDIATOR_H

#include "Card.h"
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
	/// イベント名によって登録カード効果を発動する
	/// </summary>
	/// <param name="activationEvent">イベント名</param>
	/// <returns>実行の成否</returns>
	static bool Activator(Ability::ActivationEvent activationEvent);

	/// <summary>
	/// カードの登録
	/// </summary>
	/// <param name="pCard">登録するカードポインタ</param>
	/// <returns>実行の成否</returns>
	static bool Register(Card* pCard);

	/// <summary>
	/// カードの登録解除
	/// </summary>
	/// <param name="pCard">登録解除するカードポインタ</param>
	/// <returns>実行の成否</returns>
	static bool Unregister(Card* pCard);
	
private:
	static std::vector<Card*> m_pRegisteredCards;
};
}
#endif
