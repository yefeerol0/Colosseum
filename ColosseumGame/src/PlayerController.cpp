#include "PlayerController.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"
#include <string>
#include <conio.h> // For _getch() function
#include <cstdlib>
#include <iostream>

PlayerController::PlayerController()
{
	PlayerGladiator = std::make_unique<Gladiator>();
}

PlayerController::~PlayerController() = default;

int PlayerController::GetKey()
{
	int Key = _getch();

	if (Key == 27) // Escape Key
	{
		std::exit(0);
	}

	return Key;
}

Gladiator& PlayerController::GetPlayerGladiator()
{
	return *PlayerGladiator;
}

void PlayerController::PressAnyKey()
{
	(void)GetKey();

	// Press any key does not use the pressed key at any point in code.
	// However, compiler throws a warning since the returned value is not used.
	// Therefore, I added (void) to tell the compiler the result is not important.
}

void PlayerController::EnterName()
{
	const std::size_t MaxAllowedNameLength = 12;

	std::getline(std::cin, PlayerGladiator->Name);

	if (PlayerGladiator->Name.empty())
	{
		PlayerGladiator->Name = "Gladiator";
	}

	if (PlayerGladiator->Name.size() > MaxAllowedNameLength)
	{
		PlayerGladiator->Name.resize(MaxAllowedNameLength);
	}
}

ActionTypes PlayerController::DecideAction()
{
	int action = GetKey();

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
	int stat = GetKey();

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

UpgradeData PlayerController::GetUpgradeData(int AvailablePoints) const
{
	UpgradeData UIData;

	UIData.AvailablePoints = AvailablePoints;
	UIData.Vitality = PlayerGladiator->Stats.Vitality;
	UIData.Strength = PlayerGladiator->Stats.Strength;
	UIData.Luck = PlayerGladiator->Stats.Luck;
	UIData.Agility = PlayerGladiator->Stats.Agility;
	UIData.Recovery = PlayerGladiator->Stats.Recovery;

	return UIData;
}

void PlayerController::ResetStats()
{
	PlayerGladiator->Stats = {}; // Resets all stats.
}
