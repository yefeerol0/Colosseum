#pragma once
#include <string>

class Gladiator;

class PlayerController
{
public:

	PlayerController();
	~PlayerController();

	Gladiator* PlayerGladiator;

    std::string EnterName();
};