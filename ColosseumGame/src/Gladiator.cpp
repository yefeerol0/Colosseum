#include "Gladiator.h"

void Gladiator::InitializeHealth()
{
	// Is called at "Combat Start"

	MaxHealthPoints = Vitality * 10;
	HealthPoints = MaxHealthPoints;

}

void Gladiator::TakeDamage(int DamageAmount)
{
	HealthPoints -= DamageAmount;

	CheckIfDead();
}

void Gladiator::RestoreHealth(int HealAmount)
{
	HealthPoints += HealAmount;

	if (HealthPoints > MaxHealthPoints)
	{
		HealthPoints = MaxHealthPoints;
	}
}

bool Gladiator::CheckIfDead()
{
	if (HealthPoints <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}