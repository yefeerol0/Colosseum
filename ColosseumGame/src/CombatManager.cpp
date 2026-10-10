#include "CombatManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"


void CombatManager::StartCombat(PlayerController& InController, Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	Controller = &InController;

	PlayerGladiator = Controller->PlayerGladiator;
	EnemyGladiator = &Enemy;

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
		Actions.Attack(*EnemyGladiator, *PlayerGladiator);
		break;
	case '2':
		Actions.Dodge(*PlayerGladiator);
		break;
	case '3':
		Actions.Heal(*PlayerGladiator);
		break;
	default:
		UIManager.AddMessageToCombatLog("Invalid action selected. Press '1', '2', or '3' to choose an action.");
		break;
	}

	// Invalid action part is currently not working as intended since it skips the player turn.
	// It will be fixed later on.

	UpdateInterface();
	StartEnemyTurn();
}

void CombatManager::StartEnemyTurn()
{
	StartPlayerTurn();
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

void CombatManager::UpdateInterface()
{
	for (const std::string& Log : Actions.ForwardCombatLogs())
	{
		UIManager.AddMessageToCombatLog(Log);
	}

	SetUpInterface();
}
