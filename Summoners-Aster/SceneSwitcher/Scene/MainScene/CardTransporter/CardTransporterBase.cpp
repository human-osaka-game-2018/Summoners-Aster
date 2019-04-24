#include "CardTransporterBase.h"

namespace summonersaster
{
	using namespace gameframework;

	CardTransporterBase::~CardTransporterBase()
	{

	}

	CardTransporterBase::CardTransporterBase()
	{

	}

	void CardTransporterBase::TransportCollidingCard(Vertices* pVertices, Card* pCard, Card** ppCardHolder)
	{
		if (IsCollided(pCard, pVertices))return;

		PayMPAndTransportCard(ppCardHolder, pCard);
	}

	bool CardTransporterBase::IsCollided(Card* pCard, Vertices* pVertices)const
	{
		if (collision::Collides(pCard->Rect(), *pVertices)) return true;

		return false;
	}

	bool CardTransporterBase::IsSameType(Card* pCard, const type_info& cardType)
	{
		bool isSame = false;

		switch (pCard->CARD_TYPE)
		{
		case Card::TYPE::FOLLOWER:
			isSame = algorithm::Tertiary(cardType == typeid(Follower), true, isSame);

			break;

		case Card::TYPE::SPELL:
			isSame = algorithm::Tertiary(cardType == typeid(Spell), true, isSame);

			break;

		case Card::TYPE::WEAPON:
			isSame = algorithm::Tertiary(cardType == typeid(Weapon), true, isSame);

			break;
		}

		isSame = algorithm::Tertiary(cardType == typeid(Card), true, isSame);

		return isSame;
	}
} // namespace summonersaster
