#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
#include <string>
#include <memory>

struct UpgradeData;
struct Gladiator;

class PlayerController
{

private:

	std::unique_ptr<Gladiator> PlayerGladiator;

	int GetKey();

public:

	PlayerController();
	~PlayerController();

	Gladiator& GetPlayerGladiator() const;

	// Input Events

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