#pragma once
#include "RandomGenerator.h"

// Another way of approach to accessing "RandomGenerator":
// 1. Accessing to RandomGenerator with a forward declaration and including it in the .cpp file.
// 2. Then turning its variable to a pointer and initializing it in the constructor of CombatActions.
// 3. Lastly, deleting it in the destructor of CombatActions to avoid memory leaks.
// However, since the class is very light, I directly included it.

class Gladiator;

class CombatActions
{

public:

	RandomGenerator RandomGen;

	void Attack(Gladiator& Target, int Strength);
	void Heal(Gladiator& Player, int Recovery);

	bool CheckCrit(Gladiator& Player, float CritChance);
	bool CheckDodge(Gladiator& Player, float DodgeChance);

};