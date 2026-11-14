#pragma once
#include "StatTypes.h"
#include <string>

struct UpgradeableStats
{
	// Stats

	int Vitality = 1; // Health points
	int Strength = 1; // Damage
	int Luck = 1; // Chance to crit
	int Agility = 1; // Chance to dodge
	int Recovery = 1; // Amount to heal
};

struct Gladiator
{
	// Core Values

	bool IsDead = false;

	std::string Name = "Unknown";
	int MaxHealthPoints = 0;
	int HealthPoints = 0;
	int HealsLeft = 0;

	int CritChance = 0;
	int DodgeChance = 0;

	// CritChance and DodgeChance are only used in their own calculate functions in CombatActions.cpp. 
	// Therefore, they could be local variables at there but I felt like they would be overlooked, so I wanted to store them here for clarity.

	bool IsDodging = false;
	bool IsCounterattacking = false;

	UpgradeableStats Stats;

	// AI Behavior

	float EnemyUnpredictability = 0.1f;

	// Functions

	void InitializeValues();
	void TakeDamage(int DamageAmount);
	int RestoreHealth(int HealAmount);
	bool CheckIfDead();
	void UpgradeStat(StatTypes Stat);
};