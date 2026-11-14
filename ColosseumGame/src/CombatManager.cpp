#include "CombatManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include "ConsoleInterface.h"
#include "TextColors.h"

CombatResult CombatManager::StartCombat(Gladiator& Enemy, int InputStageNumber)
{
	LocalStageNumber = InputStageNumber;

	PlayerGladiator = &Controller.GetPlayerGladiator();
	EnemyGladiator = &Enemy;

	PlayerGladiator->InitializeValues();
	EnemyGladiator->InitializeValues();

	CacheDecisionParameters();

	UIManager.ClearCombatLog();
	Actions.ClearLogsToBeAdded();

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

void CombatManager::EndCombat(const Gladiator& Winner)
{
	ForwardAllPendingLogs();
	UIManager.AddMessageToCombatLog("-----");
	UIManager.AddMessageToCombatLog("The battle is over! " GREEN + Winner.Name + RESET + " has won!");
	UIManager.AddMessageToCombatLog(BLINK "Press any key to continue..." RESET);
	SetUpCombatInterface();         
	Controller.PressAnyKey();
}

bool CombatManager::StartPlayerTurn()
{
	ActionTypes SelectedAction = Controller.DecideAction();

	while (!CheckIsActionAllowed(SelectedAction))
	{
		UpdateCombatInterface();
		SelectedAction = Controller.DecideAction();
	}

	Actions.ExecuteAction(SelectedAction, *PlayerGladiator, *EnemyGladiator);

	if (EnemyGladiator->IsDead)
	{
		EndCombat(*PlayerGladiator);
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

	if (PlayerGladiator->IsDead)
	{
		EndCombat(*EnemyGladiator);
		return true;
	}

	UpdateCombatInterface();
	return false;
}

bool CombatManager::CheckIsActionAllowed(ActionTypes SelectedAction)
{
	if (SelectedAction == ActionTypes::Invalid)
	{
		UIManager.AddMessageToCombatLog("Invalid action selected. Press '1', '2', or '3' to choose an action.");
		return false;
	}
	else if (SelectedAction == ActionTypes::Heal && PlayerGladiator->HealsLeft <= 0)
	{
		UIManager.AddMessageToCombatLog("You have no heals left. Choose another action.");
		return false;
	}
	else
	{
		return true;
	}
}

void CombatManager::ForwardAllPendingLogs()
{
	for (const std::string& Log : Actions.ForwardCombatLogs())
	{
		UIManager.AddMessageToCombatLog(Log);
	}
}

void CombatManager::SetUpCombatInterface()
{
	ConsoleData UIData;

	UIData.StageNumber = LocalStageNumber;
	UIData.PlayerName = PlayerGladiator->Name;
	UIData.EnemyName = EnemyGladiator->Name;
	UIData.EnemyHealth = EnemyGladiator->HealthPoints;
	UIData.PlayerHealsLeft = PlayerGladiator->HealsLeft;
	UIData.PlayerHealth = PlayerGladiator->HealthPoints;
	UIData.PlayerMaxHealth = PlayerGladiator->MaxHealthPoints;
	UIData.EnemyMaxHealth = EnemyGladiator->MaxHealthPoints;

	UIManager.DisplayCombatHUD(UIData);
}

void CombatManager::UpdateCombatInterface()
{
	ForwardAllPendingLogs();
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
	EnemyDecisionParameters.IsPlayerDodging = PlayerGladiator->IsDodging;
	EnemyDecisionParameters.IsCounterattacking = EnemyGladiator->IsCounterattacking;
	EnemyDecisionParameters.IsOutOfHeals = (EnemyGladiator->HealsLeft <= 0);
}
