#include "Gladiator.h"

void Gladiator::InitializeHealth()
{
	isDead = false;
	MaxHealthPoints = Stats.Vitality * 10;
	HealthPoints = MaxHealthPoints;
}

void Gladiator::TakeDamage(int DamageAmount)
{
	HealthPoints -= DamageAmount;

	isDead = CheckIfDead();
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
		Stats = {}; // Resets all stats.
		return true;
	}
	else
	{
		return false;
	}
}

void Gladiator::UpgradeStat(StatTypes Stat)
{
	switch (Stat)
	{
	case StatTypes::Vitality: Stats.Vitality++; break;
	case StatTypes::Strength: Stats.Strength++; break;
	case StatTypes::Luck:     Stats.Luck++;     break;
	case StatTypes::Agility:  Stats.Agility++;  break;
	case StatTypes::Recovery: Stats.Recovery++; break;
	}
}