#include "CombatManager.h"
#include "Gladiator.h"

void CombatManager::StartCombat(Gladiator& Player, int EnemyIndex)
{
	Player.InitializeHealth();
	SpawnEnemy(EnemyIndex);
}

void CombatManager::EndCombat(Gladiator& Player, Gladiator& Enemy)
{
}

void CombatManager::SpawnEnemy(int EnemyIndex)
{
}
