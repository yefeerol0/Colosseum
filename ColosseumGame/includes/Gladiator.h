#pragma once
#include <string>

struct Gladiator
{
	// Core Values

	std::string Name = "Unknown";
	int MaxHealthPoints = 0;
	int HealthPoints = 0;

	// Stats

	int Vitality = 0; // Health points
	int Strength = 0; // Damage
	int Luck = 0; // Chance to crit
	int Agility = 0; // Chance to dodge
	int Recovery = 0; // Amount to heal
};