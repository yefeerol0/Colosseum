#include "CombatActions.h"
#include "Gladiator.h"
#include "TextColors.h"
#include "GameTuning.h"
#include <algorithm>
using namespace Tuning;

void CombatActions::Attack(Gladiator& Target, Gladiator& Instigator)
{
	if (CheckDodge(Target))
	{
		return;
	}
	
	int Strength = Instigator.Stats.Strength;

	int DamageAmount = RandomGen.GenerateRandomInt((Strength / StrengthDivisor), Strength);

	auto [IsCritical, ExcessDamage] = CheckCrit(Instigator); 
	
	// If the CritChance exceeds the limit, the excess damage is added to the damage amount.
	// Therefore, to return two separate values and unpack them, I used std::pair + structured binding.

	if (IsCritical)
	{
		DamageAmount *= CritDamageMultiplier;
		DamageAmount += ExcessDamage;
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
	if (Instigator.HealsLeft <= 0)
	{
		GenerateCombatLog("Heal is used with no HealsLeft. Turn is skipped.");
		return; // This should never be called since CombatManager already checks it. 
				// But this is a safety measure in case of any unexpected AI behavior occurs.
	}

	int Recovery = Instigator.Stats.Recovery;

	int HealAmount = RandomGen.GenerateRandomInt((Recovery * RecoveryMultiplierMin), (Recovery * RecoveryMultiplierMax));

	int RestoredAmount = Instigator.RestoreHealth(HealAmount);

	GenerateCombatLog(Instigator.Name + " healed for " + GREEN + std::to_string(RestoredAmount) + " health points." + RESET);

	Instigator.HealsLeft--;
}

std::pair<bool, int> CombatActions::CheckCrit(Gladiator& Instigator)
{
	int Luck = Instigator.Stats.Luck;
	Instigator.CritChance = Luck * CritChancePerLuck;

	if (Instigator.IsCounterattacking)
	{
		Instigator.CritChance += CounterattackCritBonus;
		Instigator.IsCounterattacking = false;

		// The counterattack bonus only resets after attacking. Therefore, gladiators can save it for upcoming turns. 
		// Also, the counterattack bonus is saved if the enemy dodges the attack. 
		// The intention behind this was to avoid stalemate situations where gladiators keep dodging.
	}

	int ExcessCritDamage = 0;

	if (Instigator.CritChance > CritChanceLimit)
	{
		ExcessCritDamage = CalculateExcessCritDamage(Instigator.CritChance);
		Instigator.CritChance = CritChanceLimit;
	}

	int CritRoll = RandomGen.GenerateRandomInt(1, 100);

	if (CritRoll <= Instigator.CritChance)
	{
		GenerateCombatLog(Instigator.Name + " landed a" + ORANGE + " critical hit!" + RESET);
		return {true, ExcessCritDamage};
	}
	else
	{
		return {false, 0};
	}
}

int CombatActions::CalculateExcessCritDamage(int CritChance)
{
	int ExcessLuck = (CritChance - CritChanceLimit) / CritChancePerLuck;
	return ExcessLuck * CritDamagePerExcessLuck;
}

bool CombatActions::CheckDodge(Gladiator& Target)
{
	int Agility = Target.Stats.Agility;
	Target.DodgeChance = std::min(Agility * DodgeChancePerAgility, DodgeChanceLimit);

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
	ClearLogsToBeAdded();
	return LogPackage;
}

void CombatActions::ClearLogsToBeAdded()
{
	LogsToBeAdded.clear();
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
