#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
#include <string>

class Gladiator;

class PlayerController
{
public:

	PlayerController();
	~PlayerController();

	Gladiator* PlayerGladiator;

	void PressAnyKey();
    std::string EnterName();
	ActionTypes DecideAction();
	StatTypes SelectStat();
};