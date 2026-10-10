#pragma once
#include "RandomGenerator.h"
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

	void GenerateCombatLog(const std::string& message);
	std::vector<std::string> LogsToBeAdded;
	std::vector<std::string> ForwardCombatLogs();

};

//===========================================
// 
// Another way of approach to accessing "RandomGenerator":
// 1. Accessing to RandomGenerator with a forward declaration and including it in the .cpp file.
// 2. Then turning its variable to a pointer and initializing it in the constructor of CombatActions.
// 3. Lastly, deleting it in the destructor of CombatActions to avoid memory leaks.
// However, since the class is very light, I directly included it.