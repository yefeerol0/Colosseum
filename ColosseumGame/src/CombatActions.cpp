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

	GenerateCombatLog(Player.Name + " attacked " + Target.Name + " for " + std::to_string(DamageAmount) + " damage.");
}

void CombatActions::Dodge(Gladiator& Player)
{
	int Agility = Player.Agility;

	Player.IsDodging = true;

	GenerateCombatLog(Player.Name + " is preparing to dodge the next attack!");
}

void CombatActions::Heal(Gladiator& Player)
{
	int Recovery = Player.Recovery;

	int HealAmount = RandomGen.GenerateRandomInt(Recovery, Recovery + (Recovery / 2));

	Player.RestoreHealth(HealAmount);

	GenerateCombatLog(Player.Name + " healed for " + std::to_string(HealAmount) + " health points.");
}

// CritChance and DodgeChance are 2.5% per point of Luck and Agility.

bool CombatActions::CheckCrit(Gladiator& Player)
{
	int Luck = Player.Luck;
	Player.CritChance = (Luck * 5) / 2;

	if (Player.IsCounterattacking)
	{
		Player.CritChance += 20;
	}

	int CritRoll = RandomGen.GenerateRandomInt(1, 100);

	if (CritRoll <= Player.CritChance)
	{
		GenerateCombatLog(Player.Name + " landed a critical hit!");
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

	if (Target.IsDodging)
	{
		Target.DodgeChance += 20;
	}

	int DodgeRoll = RandomGen.GenerateRandomInt(1, 100);

	if (DodgeRoll <= Target.DodgeChance)
	{
		GenerateCombatLog(Target.Name + " dodged the attack!");
		GenerateCombatLog(Target.Name + " can now counterattack!");
		Target.IsCounterattacking = true;
		return true;
	}
	else
	{
		return false;
	}
}

void CombatActions::GenerateCombatLog(const std::string& message)
{
	LogsToBeAdded.push_back(message);
}

std::vector<std::string> CombatActions::ForwardCombatLogs()
{
	std::vector<std::string> LogPackage = LogsToBeAdded;
	LogsToBeAdded.clear();
	return LogPackage;
}
