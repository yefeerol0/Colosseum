#pragma once
#include "CombatActions.h" 
#include "EnemyBehavior.h"

class PlayerController;
class Gladiator;
class ConsoleInterface;

enum class CombatResult
{
	PlayerWon,
	PlayerLost
};

class CombatManager
{
private:

	Gladiator* PlayerGladiator = nullptr;
	Gladiator* EnemyGladiator = nullptr;

	PlayerController& Controller;
	ConsoleInterface& UIManager;

	CombatActions Actions;
	EnemyBehavior EnemyAI{};

	int LocalStageNumber = 0; // This variable copies the stage number from GameManager.

public:

	CombatManager(ConsoleInterface& InConsole, PlayerController& InController)
		: UIManager(InConsole), Controller(InController) {}

	// Combat Management
	
	CombatResult StartCombat(Gladiator& Enemy, int InputStageNumber);
	void EndCombat();

	bool StartPlayerTurn();
	bool StartEnemyTurn();

	// UI Functions

	void SetUpCombatInterface();
	void UpdateCombatInterface();

	// AI Behavior Parameters

	DecisionParameters EnemyDecisionParameters{};

	void CacheDecisionParameters();
	void UpdateDecisionParameters();

};