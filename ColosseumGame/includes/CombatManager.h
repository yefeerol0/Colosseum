#pragma once
#include "CombatActions.h" 
#include "EnemyBehavior.h"

struct Gladiator;

class PlayerController;
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

	ConsoleInterface& UIManager;
	PlayerController& Controller;

	CombatActions Actions;
	EnemyBehavior EnemyAI{};

	int LocalStageNumber = 0; // This variable copies the stage number from GameManager.

	bool StartPlayerTurn();
	bool StartEnemyTurn();

	// UI Functions

	void SetUpCombatInterface();
	void UpdateCombatInterface();

	// AI Behavior Parameters

	DecisionParameters EnemyDecisionParameters{};

	void CacheDecisionParameters();
	void UpdateDecisionParameters();

	// Combat Management

	void EndCombat();

public:

	CombatManager(ConsoleInterface& InConsole, PlayerController& InController)
		: UIManager(InConsole), Controller(InController) {}

	// Combat Management

	CombatResult StartCombat(Gladiator& Enemy, int InputStageNumber);
};