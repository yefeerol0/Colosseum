#include "CombatManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"

CombatResult CombatManager::StartCombat(Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	PlayerGladiator = Controller.PlayerGladiator.get();
	EnemyGladiator = &Enemy;

	PlayerGladiator->InitializeHealth();
	EnemyGladiator->InitializeHealth();

	CacheDecisionParameters();
	UpdateCombatInterface();

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
	UpdateCombatInterface();
}

bool CombatManager::StartPlayerTurn()
{
	ActionTypes SelectedAction = Controller.DecideAction();

	while (SelectedAction == ActionTypes::Invalid)
	{
		UIManager.AddMessageToCombatLog("Invalid action selected. Press '1', '2', or '3' to choose an action.");
		UpdateCombatInterface();
		SelectedAction = Controller.DecideAction();
	}

	Actions.ExecuteAction(SelectedAction, *PlayerGladiator, *EnemyGladiator);

	if (EnemyGladiator->isDead)
	{
		EndCombat();
		return true;
	}

	UpdateCombatInterface();
	return false;
}

bool CombatManager::StartEnemyTurn()
{
	UpdateDecisionParameters();

	ActionTypes SelectedAction = EnemyAI.DecideAction(EnemyDecisionParameters);

	Actions.ExecuteAction(SelectedAction, *EnemyGladiator, *PlayerGladiator);

	if (PlayerGladiator->isDead)
	{
		EndCombat();
		return true;
	}

	UpdateCombatInterface();
	return false;
}

void CombatManager::SetUpCombatInterface()
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

void CombatManager::UpdateCombatInterface()
{
	for (const std::string& Log : Actions.ForwardCombatLogs())
	{
		UIManager.AddMessageToCombatLog(Log);
	}

	SetUpCombatInterface();
}

void CombatManager::CacheDecisionParameters()
{
	EnemyDecisionParameters.SelfMaxHealth = EnemyGladiator->MaxHealthPoints;
	EnemyDecisionParameters.PlayerMaxHealth = PlayerGladiator->MaxHealthPoints;
	EnemyDecisionParameters.StrengthStat = EnemyGladiator->Stats.Strength;
	EnemyDecisionParameters.LuckStat = EnemyGladiator->Stats.Luck;
	EnemyDecisionParameters.AgilityStat = EnemyGladiator->Stats.Agility;
	EnemyDecisionParameters.RecoveryStat = EnemyGladiator->Stats.Recovery;
	EnemyDecisionParameters.Unpredictability = EnemyGladiator->EnemyUnpredictability;
}

void CombatManager::UpdateDecisionParameters()
{
	EnemyDecisionParameters.SelfHealth = EnemyGladiator->HealthPoints;
	EnemyDecisionParameters.PlayerHealth = PlayerGladiator->HealthPoints;
	EnemyDecisionParameters.isPlayerDodging = PlayerGladiator->IsDodging;
	EnemyDecisionParameters.isCounterattacking = EnemyGladiator->IsCounterattacking;
}
