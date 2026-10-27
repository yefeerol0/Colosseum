#pragma once
#include "StatTypes.h"
#include <string>


struct UpgradeableStats
{
	// Stats

	int Vitality = 5; // Health points
	int Strength = 4; // Damage
	int Luck = 1; // Chance to crit
	int Agility = 1; // Chance to dodge
	int Recovery = 1; // Amount to heal
};

struct Gladiator
{
	// Core Values

	bool isDead = false;

	std::string Name = "Unknown";
	int MaxHealthPoints = 0;
	int HealthPoints = 0;

	float CritChance = 0;
	float DodgeChance = 0;

	bool IsDodging = false;
	bool IsCounterattacking = false;

	UpgradeableStats Stats;

	// AI Behavior

	float EnemyUnpredictability = 0.1f;

	// Functions

	void InitializeHealth();
	void TakeDamage(int DamageAmount);
	void RestoreHealth(int HealAmount);
	bool CheckIfDead();
	void UpgradeStat(StatTypes Stat);
};