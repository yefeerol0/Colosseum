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

char PlayerController::DecideAction()
{
	char action = _getch();

	if (action == '1' || action == '2' || action == '3')
	{
		return action;
	}
	else
	{
		return 0;
	}
}
