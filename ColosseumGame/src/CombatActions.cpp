#include "CombatActions.h"
#include "Gladiator.h"
#include "TextColors.h"
#include <algorithm>

void CombatActions::Attack(Gladiator& Target, Gladiator& Instigator)
{
	if (CheckDodge(Target))
	{
		return;
	}
	
	int Strength = Instigator.Stats.Strength;

	int DamageAmount = RandomGen.GenerateRandomInt((Strength / 2), Strength);

	if (CheckCrit(Instigator))
	{
		DamageAmount *= 2;
	}

	Target.TakeDamage(DamageAmount);

	GenerateCombatLog(Instigator.Name + " attacked " + Target.Name + " for " + RED + std::to_string(DamageAmount) + " damage." + RESET);
}

void CombatActions::Dodge(Gladiator& Instigator)
{
	Instigator.IsDodging = true;

	GenerateCombatLog(Instigator.Name + " is preparing to" + BLUE + " dodge the next attack!" + RESET);
}

void CombatActions::Heal(Gladiator& Instigator)
{
	int Recovery = Instigator.Stats.Recovery;

	int HealAmount = RandomGen.GenerateRandomInt((Recovery / 2), Recovery);

	Instigator.RestoreHealth(HealAmount);

	GenerateCombatLog(Instigator.Name + " healed for " + GREEN + std::to_string(HealAmount) + " health points." + RESET);
}

// CritChance and DodgeChance are 4% per point of Luck and Agility.

bool CombatActions::CheckCrit(Gladiator& Instigator)
{
	int Luck = Instigator.Stats.Luck;
	Instigator.CritChance = std::min(Luck * 4, 72);

	if (Instigator.IsCounterattacking)
	{
		Instigator.CritChance += CounterattackCritBonus;
		Instigator.IsCounterattacking = false;

		// The counterattack bonus only resets after attacking. Therefore, gladiators can save it for upcoming turns. 
		// Also, the counterattack bonus is saved if the enemy dodges the attack. 
		// The intention behind this was to avoid stalemate situations where gladiators keep dodging.
	}

	int CritRoll = RandomGen.GenerateRandomInt(1, 100);

	if (CritRoll <= Instigator.CritChance)
	{
		GenerateCombatLog(Instigator.Name + " landed a" + ORANGE + " critical hit!" + RESET);
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
	Target.DodgeChance = std::min(Agility * 4, 72);

	if (Target.IsDodging)
	{
		Target.DodgeChance += DodgeActionBonus;
		Target.IsDodging = false;
	}

	int DodgeRoll = RandomGen.GenerateRandomInt(1, 100);

	if (DodgeRoll <= Target.DodgeChance)
	{
		GenerateCombatLog(Target.Name + BLUE + " dodged the attack!" + RESET);
		GenerateCombatLog(Target.Name + ORANGE + " can now counterattack!" + RESET);
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
