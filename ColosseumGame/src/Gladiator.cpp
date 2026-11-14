#include "Gladiator.h"
#include "GameTuning.h"

void Gladiator::InitializeValues()
{
	IsDead = false;
	MaxHealthPoints = Stats.Vitality * Tuning::HealthPerVitality;
	HealthPoints = MaxHealthPoints;

	HealsLeft = Tuning::MaxHealsPerFight;

	IsCounterattacking = false;
	IsDodging = false;
}

void Gladiator::TakeDamage(int DamageAmount)
{
	HealthPoints -= DamageAmount;

	if (HealthPoints < 0)
	{
		HealthPoints = 0;
	}

	IsDead = CheckIfDead();
}


int Gladiator::RestoreHealth(int HealAmount)
{
	int InitialHealth = HealthPoints;

	HealthPoints += HealAmount;

	if (HealthPoints > MaxHealthPoints)
	{
		HealthPoints = MaxHealthPoints;
	}

	return HealthPoints - InitialHealth;
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
