#include "CombatManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include "CombatActions.h"
#include "ConsoleInterface.h"

void CombatManager::StartCombat(PlayerController& InController, Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	Controller = &InController;

	PlayerGladiator = Controller->PlayerGladiator;
	EnemyGladiator = &Enemy;

	CombatActions Actions;

	PlayerGladiator->InitializeHealth();
	EnemyGladiator->InitializeHealth();

	SetUpInterface();
	StartPlayerTurn();
}

void CombatManager::EndCombat()
{
}

void CombatManager::StartPlayerTurn()
{

	char SelectedAction = Controller->DecideAction();

	switch (SelectedAction)
	{
	case '1':
		Actions->Attack(*EnemyGladiator, *PlayerGladiator);
		break;
	case '2':
		Actions->Dodge(*PlayerGladiator);
		break;
	case '3':
		Actions->Heal(*PlayerGladiator);
		break;
	}
}

void CombatManager::StartEnemyTurn()
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