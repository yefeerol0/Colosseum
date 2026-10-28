#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"
#include <string>
#include <vector>

class Gladiator;

class CombatActions
{

public:

	RandomGenerator RandomGen;

	void Attack(Gladiator& Target, Gladiator& Player);
	void Dodge(Gladiator& Player);
	void Heal(Gladiator& Player);

	bool CheckCrit(Gladiator& Player);
	bool CheckDodge(Gladiator& Target);

	const int CounterattackCritBonus = 20;
	const int DodgeActionBonus = 20;

	void GenerateCombatLog(const std::string& message);
	std::vector<std::string> LogsToBeAdded;
	std::vector<std::string> ForwardCombatLogs();

	void ExecuteAction(ActionTypes SelectedAction, Gladiator& Instigator, Gladiator& Target);
};

// ===========================================
// Another way of approach to accessing "RandomGenerator":
// 1. Accessing to RandomGenerator with a forward declaration and including it in the .cpp file.
// 2. Then turning its variable to a pointer using unique_ptr with <memory> library.
// However, since the class is very light, I directly included it.