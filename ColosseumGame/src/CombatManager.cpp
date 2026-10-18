#include "CombatManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"

CombatResult CombatManager::StartCombat(PlayerController& InController, Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	Controller = &InController;

	PlayerGladiator = Controller->PlayerGladiator;
	EnemyGladiator = &Enemy;

	PlayerGladiator->InitializeHealth();
	EnemyGladiator->InitializeHealth();

	CacheDecisionParameters();
	SetUpInterface();
	StartPlayerTurn();

	while (true)
	{
		if (StartPlayerTurn())
		{
			return CombatResult::PlayerWon;
		}

		if (StartEnemyTurn())
		{
			return CombatResult::PlayerLost;
		}
	}
}

void CombatManager::EndCombat()
{
	UIManager.ClearCombatLog();
	Actions.LogsToBeAdded.clear();
	UIManager.AddMessageToCombatLog("The battle is over!");
	UpdateInterface();
}

bool CombatManager::StartPlayerTurn()
{

	PlayerActionOptions SelectedAction = Controller->DecideAction();

	switch (SelectedAction)
	{
	case PlayerActionOptions::Attack:
		Actions.Attack(*EnemyGladiator, *PlayerGladiator);
		break;
	case PlayerActionOptions::Dodge:
		Actions.Dodge(*PlayerGladiator);
		break;
	case PlayerActionOptions::Heal:
		Actions.Heal(*PlayerGladiator);
		break;
	case PlayerActionOptions::Invalid:
		UIManager.AddMessageToCombatLog("Invalid action selected. Press '1', '2', or '3' to choose an action.");
		break;
	}

	// Invalid action part is currently not working as intended since it skips the player turn.
	// It will be fixed later on.

	if (EnemyGladiator->isDead)
	{
		EndCombat();
		return true;
	}

	UpdateInterface();
	return false;
}

bool CombatManager::StartEnemyTurn()
{
	UpdateDecisionParameters();

	EnemyActionOptions SelectedAction = EnemyAI.DecideAction(EnemyDecisionParameters);

	switch (SelectedAction)
	{
	case EnemyActionOptions::Attack:
		Actions.Attack(*PlayerGladiator, *EnemyGladiator);
		break;
	case EnemyActionOptions::Dodge:
		Actions.Dodge(*EnemyGladiator);
		break;
	case EnemyActionOptions::Heal:
		Actions.Heal( *EnemyGladiator);
		break;
	default:
		UIManager.AddMessageToCombatLog("Invalid action selected.");
		break;
	}

	if (PlayerGladiator->isDead)
	{
		EndCombat();
		return true;
	}

	UpdateInterface();
	return false;
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

void CombatManager::CacheDecisionParameters()
{
	EnemyDecisionParameters.SelfMaxHealth = EnemyGladiator->MaxHealthPoints;
	EnemyDecisionParameters.PlayerMaxHealth = PlayerGladiator->MaxHealthPoints;
	EnemyDecisionParameters.StrengthStat = EnemyGladiator->Strength;
	EnemyDecisionParameters.LuckStat = EnemyGladiator->Luck;
	EnemyDecisionParameters.AgilityStat = EnemyGladiator->Agility;
	EnemyDecisionParameters.RecoveryStat = EnemyGladiator->Recovery;
	EnemyDecisionParameters.Unpredictability = EnemyGladiator->EnemyUnpredictability;
}

void CombatManager::UpdateDecisionParameters()
{
	EnemyDecisionParameters.SelfHealth = EnemyGladiator->HealthPoints;
	EnemyDecisionParameters.PlayerHealth = PlayerGladiator->HealthPoints;
	EnemyDecisionParameters.isPlayerDodging = PlayerGladiator->IsDodging;
	EnemyDecisionParameters.isCounterattacking = EnemyGladiator->IsCounterattacking;
}
