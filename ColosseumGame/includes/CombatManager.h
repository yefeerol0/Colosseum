#pragma once

class Gladiator;

class CombatManager
{
public:

	// Combat Management
	
	void StartCombat(Gladiator& Player, Gladiator& Enemy);
	void EndCombat(Gladiator& Player, Gladiator& Enemy);

};