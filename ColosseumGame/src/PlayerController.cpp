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
