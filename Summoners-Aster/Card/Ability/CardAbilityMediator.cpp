#include "CardAbilityMediator.h"
#include "AbilityExecutor.h"

namespace summonersaster
{
	using Execute = Ability::Execute;
	using ActivationEvent = Ability::ActivationEvent;
	std::vector<FollowerData*> CardAbilityMediator::m_pRegisteredCards;

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
		if (activationEvent == card->m_pFollower->GetActivationEvent()) 
		{
			AbilityExecutor::Execute(card);
			isSuccess = true;
		}
	}
	return isSuccess;
}

bool CardAbilityMediator::Activator(ActivationEvent activationEvent,Card* card)
{
	if (nullptr == card) return false;
	bool isSuccess = false;
	if (activationEvent == card->GetActivationEvent())
	{
		AbilityExecutor::Execute(card);
		isSuccess = true;
	}
	return isSuccess;
}

bool CardAbilityMediator::Activator(ActivationEvent activationEvent, FollowerData* pFollowerData)
{
	if (nullptr == pFollowerData->m_pFollower) return false;
	bool isSuccess = false;
	if (activationEvent == pFollowerData->m_pFollower->GetActivationEvent())
	{
		AbilityExecutor::Execute(pFollowerData);
		isSuccess = true;
	}
	return isSuccess;
}

bool CardAbilityMediator::Register(FollowerData* pFollowerData)
{
	if (!pFollowerData->m_pFollower) return false;
	m_pRegisteredCards.emplace_back(pFollowerData);
	return false;
}

bool CardAbilityMediator::Unregister(FollowerData* pFollowerData)
{
	if (!pFollowerData->m_pFollower) return false;
	FollowerData* pRegistedCard = nullptr;
	//登録解除するカードの検索
	for (auto& registedCard : m_pRegisteredCards)
	{
		if (pFollowerData == registedCard)
		{
			pRegistedCard = registedCard;
			break;
		}
	}
	if (!pRegistedCard) return false;
	//登録しているカードと一致するカードを消去する
	m_pRegisteredCards.erase(remove(m_pRegisteredCards.begin(), m_pRegisteredCards.end(), pRegistedCard), m_pRegisteredCards.end());
	pRegistedCard = nullptr;
	return true;
}


}
