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

bool CardAbilityMediator::Activator(ActivationEvent activationEvent,Card* card)
{
	if (nullptr == card) return false;
	bool isSuccess = false;

	//activationEventと同じEventがトリガーである効果が設定されているか確認する
	std::vector<Ability> abilities = card->Abilities();
	for (auto ability : abilities)
	{
		if (activationEvent == ability.activationEvent)
		{
			//設定されていたら、効果を呼ぶ
			AbilityExecutor::Execute(card, ability.execute);
			isSuccess = true;
		}
	}

	return isSuccess;
}

bool CardAbilityMediator::Activator(ActivationEvent activationEvent, FollowerData* pFollowerData)
{
	if (nullptr == pFollowerData->m_pFollower) return false;
	bool isSuccess = false;

	//activationEventと同じEventがトリガーである効果が設定されているか確認する
	std::vector<Ability> abilities = pFollowerData->m_pFollower->Abilities();
	for (auto ability: abilities)
	{
		if (activationEvent == ability.activationEvent)
		{
			//設定されていたら、効果を呼ぶ
			AbilityExecutor::Execute(pFollowerData, ability.execute);
			isSuccess = true;
		}
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
