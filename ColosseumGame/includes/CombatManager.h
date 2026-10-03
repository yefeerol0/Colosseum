#pragma once

class Gladiator;
class ConsoleInterface;

class CombatManager
{
private:

	Gladiator* PlayerGladiator = nullptr;
	Gladiator* EnemyGladiator = nullptr;
	ConsoleInterface& UIManager;

	int LocalStageNumber = 0; // This variable copies the stage number from GameManager.

public:

	CombatManager(ConsoleInterface& InConsole) : UIManager(InConsole) {}

	// Combat Management
	
	void StartCombat(Gladiator& Player, Gladiator& Enemy, int InputStageNumber);
	void EndCombat(Gladiator& Player, Gladiator& Enemy);
	void SetUpInterface();
};