#include "CombatManager.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"
#include <iostream>

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
	ConsoleData UIData;

	UIData.StageNumber = LocalStageNumber;
	UIData.PlayerName = PlayerGladiator->Name;
	UIData.EnemyName = EnemyGladiator->Name;
	UIData.EnemyHealth = EnemyGladiator->HealthPoints;
	UIData.PlayerHealth = PlayerGladiator->HealthPoints;
	UIData.PlayerMaxHealth = PlayerGladiator->MaxHealthPoints;
	UIData.EnemyMaxHealth = EnemyGladiator->MaxHealthPoints;

	UIManager.DisplayCombatHUD(UIData);
}