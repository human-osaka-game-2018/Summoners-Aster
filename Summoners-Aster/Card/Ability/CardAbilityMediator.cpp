#include "CardAbilityMediator.h"
#include "AbilityExecutor.h"

namespace summonersaster
{
	using Execute = Ability::Execute;
	using ActivationEvent = Ability::ActivationEvent;
	std::vector<Card*> CardAbilityMediator::m_pRegisteredCards;

CardAbilityMediator::CardAbilityMediator()
{
}


CardAbilityMediator::~CardAbilityMediator()
{
}

bool CardAbilityMediator::Activator(ActivationEvent activationEvent)
{
	bool isSuccess = false;
	for (auto& card : m_pRegisteredCards)
	{
		if (activationEvent == card->GetActivationEvent()) 
		{
			AbilityExecutor::Execute(card);
			isSuccess = true;
		}
	}
	return isSuccess;
}

bool CardAbilityMediator::Register(Card* pCard)
{
	if (!pCard) return false;
	m_pRegisteredCards.emplace_back(pCard);
	return false;
}

bool CardAbilityMediator::Unregister(Card* pCard)
{
	if (!pCard) return false;
	Card* pRegistedCard;
	//登録解除するカードの検索
	for (auto& registedCard : m_pRegisteredCards)
	{
		if (pCard == registedCard)
		{
			pRegistedCard = registedCard;
		}
	}
	//登録しているカードと一致するカードを消去する
	m_pRegisteredCards.erase(remove(m_pRegisteredCards.begin(), m_pRegisteredCards.end(), pRegistedCard), m_pRegisteredCards.end());
	pRegistedCard = nullptr;
	return true;
}


}
