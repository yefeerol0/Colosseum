#pragma once
#include <string>

class Gladiator;

enum class PlayerActionOptions
{
	Attack,
	Dodge,
	Heal,
	Invalid
};
class PlayerController
{
public:

	PlayerController();
	~PlayerController();

	Gladiator* PlayerGladiator;

    std::string EnterName();
	PlayerActionOptions DecideAction();
};