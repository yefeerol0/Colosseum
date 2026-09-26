#include "CombatActions.h"

void CombatActions::Attack(Gladiator& Target, int Strength)
{
	int DamageAmount = RandomGen.GenerateRandomInt(Strength, Strength + (Strength / 2));
}

void CombatActions::Heal(Gladiator& Player, int Recovery)
{
	int HealAmount = RandomGen.GenerateRandomInt(Recovery, Recovery + (Recovery / 2));
}

bool CombatActions::CheckCrit(Gladiator& Player, float CritChance)
{
	return false;
}

bool CombatActions::CheckDodge(Gladiator& Player, float DodgeChance)
{
	return false;
}
