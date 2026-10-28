#include "CombatActions.h"
#include "Gladiator.h"

void CombatActions::Attack(Gladiator& Target, Gladiator& Player)
{
	if (CheckDodge(Target))
	{
		return;
	}
	
	int Strength = Player.Stats.Strength;

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
	Player.IsDodging = true;

	GenerateCombatLog(Player.Name + " is preparing to dodge the next attack!");
}

void CombatActions::Heal(Gladiator& Player)
{
	int Recovery = Player.Stats.Recovery;

	int HealAmount = RandomGen.GenerateRandomInt(Recovery, Recovery + (Recovery / 2));

	Player.RestoreHealth(HealAmount);

	GenerateCombatLog(Player.Name + " healed for " + std::to_string(HealAmount) + " health points.");
}

// CritChance and DodgeChance are 2.5% per point of Luck and Agility.

bool CombatActions::CheckCrit(Gladiator& Player)
{
	int Luck = Player.Stats.Luck;
	Player.CritChance = (Luck * 5) / 2;

	if (Player.IsCounterattacking)
	{
		Player.CritChance += CounterattackCritBonus;
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
	int Agility = Target.Stats.Agility;
	Target.DodgeChance = (Agility * 5) / 2;

	if (Target.IsDodging)
	{
		Target.DodgeChance += DodgeActionBonus;
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

void CombatActions::ExecuteAction(ActionTypes SelectedAction, Gladiator& Instigator, Gladiator& Target)
{
	switch (SelectedAction)
	{

	case ActionTypes::Attack:

		Attack(Target, Instigator);
		break;

	case ActionTypes::Dodge:

		Dodge(Instigator);
		break;

	case ActionTypes::Heal:

		Heal(Instigator);
		break;

	}
}
