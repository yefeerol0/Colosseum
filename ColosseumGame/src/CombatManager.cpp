#include "CombatManager.h"
#include "Gladiator.h"

void CombatManager::StartCombat(Gladiator& Player, Gladiator& Enemy)
{
	Player.InitializeHealth();
	Enemy.InitializeHealth();
}

void CombatManager::EndCombat(Gladiator& Player, Gladiator& Enemy)
{
}
