#include "PlayerController.h"
#include "Gladiator.h"
#include "conio.h" // For _getch() function
#include <iostream>


PlayerController::PlayerController()
{
	PlayerGladiator = new Gladiator();
}

PlayerController::~PlayerController()
{
	delete PlayerGladiator;
}

std::string PlayerController::EnterName()
{
	std::string name;
	std::cin >> name;
	PlayerGladiator->Name = name;
	return name;
}

PlayerActionOptions PlayerController::DecideAction()
{
	char action = _getch();

	switch (action)
	{
	case '1':
		return PlayerActionOptions::Attack;
	case '2':
		return PlayerActionOptions::Dodge;
	case '3':
		return PlayerActionOptions::Heal;
	default:
		return PlayerActionOptions::Invalid;
	}
}
