#include "PlayerController.h"
#include "Gladiator.h"
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
