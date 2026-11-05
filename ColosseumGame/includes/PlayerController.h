#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
#include <string>
#include <memory>

struct UpgradeData;
struct Gladiator;

class PlayerController
{

public:

	PlayerController();
	~PlayerController();

	std::unique_ptr<Gladiator> PlayerGladiator;

	int GetKey();

	void PressAnyKey();
    std::string EnterName();

	// Combat

	ActionTypes DecideAction();

	// Upgrade System

	StatTypes SelectStat();
	void ApplyUpgrade(StatTypes Stat);
	UpgradeData GetUpgradeData(int AvailablePoints) const;
	void ResetStats();
};