#include "PlayerController.h"
#include "Gladiator.h"
#include "conio.h" // For _getch() function
#include <iostream>


PlayerController::PlayerController()
{
	PlayerGladiator = std::make_unique<Gladiator>();
}

void PlayerController::PressAnyKey()
{
	(void)_getch();

	// Press any key does not use the pressed key at any point in code.
	// However, compiler throws a warning since the returned value is not used.
	// Therefore, I added (void) to tell the compiler the result is not important.
}

std::string PlayerController::EnterName()
{
	std::string name;
	std::cin >> name;
	PlayerGladiator->Name = name;
	return name;
}

ActionTypes PlayerController::DecideAction()
{
	char action = _getch();

	switch (action)
	{
	case '1':
		return ActionTypes::Attack;
	case '2':
		return ActionTypes::Dodge;
	case '3':
		return ActionTypes::Heal;
	default:
		return ActionTypes::Invalid;
	}
}

StatTypes PlayerController::SelectStat()
{
	char stat = _getch();

	switch(stat)
	{
	case '1':
		return StatTypes::Vitality;
	case '2':
		return StatTypes::Strength;
	case '3':
		return StatTypes::Luck;
	case '4':
		return StatTypes::Agility;
	case '5':
		return StatTypes::Recovery;
	default:
		return StatTypes::Invalid;
	}
}

void PlayerController::ApplyUpgrade(StatTypes Stat) 
{
	PlayerGladiator->UpgradeStat(Stat);

	// This function is a wrapper to remove the need of UpgradeSystem.cpp knowing about Gladiator.h.
}
