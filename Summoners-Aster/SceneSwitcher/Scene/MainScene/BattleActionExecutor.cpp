#include "BattleActionExecutor.h"

namespace summonersaster
{
	void BattleActionExecutor::Update()
	{
		BattleInformation::ActionInformation currentAction = BattleInformation::QueFront();

		switch (currentAction.m_actionKind)
		{
		case ACTION_KIND::SUMMONING:
			Summon();

			break;

		case ACTION_KIND::WEAPON_DESTROYING:
			DstroyWeapon();

			break;

		case ACTION_KIND::ARMING:
			Arm();

			break;

		case ACTION_KIND::ROTATION:
			Rotate();

			break;

		case ACTION_KIND::ATTACK:
			Attack();

			break;

		case ACTION_KIND::MOVING:
			Move();

			break;

		default:
			break;
		}
	}
} // namespace summonersaster
