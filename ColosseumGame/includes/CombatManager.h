#pragma once
#include "CombatActions.h" 
#include "EnemyBehavior.h"

class PlayerController;
class Gladiator;
class ConsoleInterface;
class EnemyBehavior;

class CombatManager
{
private:

	PlayerController* Controller = nullptr;
	Gladiator* PlayerGladiator = nullptr;
	Gladiator* EnemyGladiator = nullptr;
	CombatActions Actions;
	ConsoleInterface& UIManager;
	EnemyBehavior EnemyAI;

	int LocalStageNumber = 0; // This variable copies the stage number from GameManager.

public:

	CombatManager(ConsoleInterface& InConsole) : UIManager(InConsole) {}

	// Combat Management
	
	void StartCombat(PlayerController& InController, Gladiator& Enemy, int InputStageNumber);
	void EndCombat();
	void StartPlayerTurn();
	void StartEnemyTurn();

	// UI Functions

	void SetUpInterface();
	void UpdateInterface();

	// AI Behavior Parameters

	DecisionParameters EnemyDecisionParameters{};

	void CacheDecisionParameters();
	void UpdateDecisionParameters();

};