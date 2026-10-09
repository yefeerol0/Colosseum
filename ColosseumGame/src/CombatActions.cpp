#include "CombatActions.h"
#include "Gladiator.h"

void CombatActions::Attack(Gladiator& Target, Gladiator& Player)
{
	if (CheckDodge(Target))
	{
		return;
	}
	
	int Strength = Player.Strength;

	int DamageAmount = RandomGen.GenerateRandomInt(Strength, Strength + (Strength / 2));

	if (CheckCrit(Player))
	{
		DamageAmount *= 2;
	}

	Target.TakeDamage(DamageAmount);
}

void CombatActions::Dodge(Gladiator& Player)
{
	int Agility = Player.Agility;
}

void CombatActions::Heal(Gladiator& Player)
{
	int Recovery = Player.Recovery;

	int HealAmount = RandomGen.GenerateRandomInt(Recovery, Recovery + (Recovery / 2));

	Player.RestoreHealth(HealAmount);
}

// CritChance and DodgeChance are 2.5% per point of Luck and Agility.

bool CombatActions::CheckCrit(Gladiator& Player)
{
	int Luck = Player.Luck;
	Player.CritChance = (Luck * 5) / 2;

	int CritRoll = RandomGen.GenerateRandomInt(1, 100);

	if (CritRoll <= Player.CritChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CombatActions::CheckDodge(Gladiator& Target)
{
	int Agility = Target.Agility;
	Target.DodgeChance = (Agility * 5) / 2;

	int DodgeRoll = RandomGen.GenerateRandomInt(1, 100);

	if (DodgeRoll <= Target.DodgeChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}
