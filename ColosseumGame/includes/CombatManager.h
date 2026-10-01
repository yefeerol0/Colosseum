#pragma once

class Gladiator;

class CombatManager
{
public:

	// Combat Management
	
	void StartCombat(Gladiator& Player, int EnemyIndex);
	void EndCombat(Gladiator& Player, Gladiator& Enemy);
};