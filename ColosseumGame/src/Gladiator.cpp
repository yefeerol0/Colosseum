#include "Gladiator.h"

void Gladiator::InitializeCoreValues()
{
	// Is called at "Combat Start"

	MaxHealthPoints = Vitality * 10;
	HealthPoints = MaxHealthPoints;

	CritChance = (Luck * 5) / 2;
	DodgeChance = (Agility * 5) / 2;

	// CritChance and DodgeChance are 2.5% per point of Luck and Agility.
}