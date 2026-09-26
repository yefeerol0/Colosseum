#pragma once
#include <string>

struct Gladiator
{
	// Core Values

	std::string Name = "Unknown";
	int MaxHealthPoints = 0;
	int HealthPoints = 0;

	float CritChance = 0;
	float DodgeChance = 0;

	// Stats

	int Vitality = 5; // Health points
	int Strength = 1; // Damage
	int Luck = 1; // Chance to crit
	int Agility = 1; // Chance to dodge
	int Recovery = 1; // Amount to heal

	// Functions

	void InitializeCoreValues();
};