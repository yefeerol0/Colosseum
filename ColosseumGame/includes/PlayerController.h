#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
#include <string>
#include <memory>

struct UpgradeData;
class Gladiator;

class PlayerController
{
public:

	PlayerController();

	std::unique_ptr<Gladiator> PlayerGladiator;

	void PressAnyKey();
    std::string EnterName();

	// Combat

	ActionTypes DecideAction();

	// Upgrade System

	StatTypes SelectStat();
	void ApplyUpgrade(StatTypes Stat);
};