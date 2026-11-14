#pragma once
#include "ActionTypes.h"
#include "StatTypes.h"
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

	Gladiator& GetPlayerGladiator();

	// Input Events

	void PressAnyKey();
	void EnterName();

	// Combat

	ActionTypes DecideAction();

	// Upgrade System

	StatTypes SelectStat();
	void ApplyUpgrade(StatTypes Stat);
	UpgradeData GetUpgradeData(int AvailablePoints) const;
	void ResetStats();
};