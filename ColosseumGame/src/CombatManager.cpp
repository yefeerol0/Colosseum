#include "CombatManager.h"
#include "Gladiator.h"

void CombatManager::StartCombat(Gladiator& Player, Gladiator& Enemy)
{
	Player.InitializeCoreValues();
	Enemy.InitializeCoreValues();
}

void CombatManager::EndCombat(Gladiator& Player, Gladiator& Enemy)
{
}
