#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
#include <string>

struct UpgradeData;
class Gladiator;

class PlayerController
{
public:

	PlayerController();
	~PlayerController();

	Gladiator* PlayerGladiator;

	void PressAnyKey();
    std::string EnterName();

	// Combat

	ActionTypes DecideAction();

	// Upgrade System

	StatTypes SelectStat();
	void ApplyUpgrade(StatTypes Stat);
};