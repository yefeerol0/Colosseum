#include "CombatManager.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"

void CombatManager::StartCombat(Gladiator& Player, Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	PlayerGladiator = &Player;
	EnemyGladiator = &Enemy;

	PlayerGladiator->InitializeHealth();
	EnemyGladiator->InitializeHealth();

	SetUpInterface();
}

void CombatManager::EndCombat(Gladiator& Player, Gladiator& Enemy)
{
}

void CombatManager::SetUpInterface()
{
	UIManager.DisplayCombatHUD(LocalStageNumber, PlayerGladiator->HealthPoints, EnemyGladiator->HealthPoints);
}