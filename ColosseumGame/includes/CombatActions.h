#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"
#include <string>
#include <vector>

struct Gladiator;

class CombatActions
{
private:

	RandomGenerator RandomGen;

	void Attack(Gladiator& Target, Gladiator& Instigator);
	void Dodge(Gladiator& Instigator);
	void Heal(Gladiator& Instigator);

	bool CheckCrit(Gladiator& Instigator);
	bool CheckDodge(Gladiator& Instigator);

	void GenerateCombatLog(const std::string& message);

	std::vector<std::string> LogsToBeAdded;

public:

	std::vector<std::string> ForwardCombatLogs();
	void ClearLogsToBeAdded();
	void ExecuteAction(ActionTypes SelectedAction, Gladiator& Instigator, Gladiator& Target);
};

// ===========================================
// Another way of approach to accessing "RandomGenerator":
// 1. Accessing to RandomGenerator with a forward declaration and including it in the .cpp file.
// 2. Then turning its variable to a pointer using unique_ptr with <memory> library.
// However, since the class is very light, I directly included it.