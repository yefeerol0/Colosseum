#include "Gladiator.h"
#include "GameTuning.h"

void Gladiator::InitializeValues()
{
	IsDead = false;
	MaxHealthPoints = Stats.Vitality * Tuning::HealthPerVitality;
	HealthPoints = MaxHealthPoints;

	IsCounterattacking = false;
	IsDodging = false;
}

void Gladiator::TakeDamage(int DamageAmount)
{
	HealthPoints -= DamageAmount;

	IsDead = CheckIfDead();
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