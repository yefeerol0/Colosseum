#pragma once
#include <memory>

class PlayerController;
class GladiatorDataLoader;
class ConsoleInterface;
class CombatManager;

struct Gladiator;

class GameManager
{

private:

	int StageNumber = 0; // Which enemy the player is going to face, starting from 0, incremented at the start of each combat.

	// Pointers

	std::unique_ptr<PlayerController> Controller;
	std::unique_ptr<GladiatorDataLoader> DataLoader;
	std::unique_ptr<ConsoleInterface> UIManager;
	std::unique_ptr<CombatManager> CombatProcessor;
	std::unique_ptr<Gladiator> CurrentEnemy;

	// GAME START

	void DisplayWelcomeText();
	void WaitForStartInput();
	void AskForPlayerName();

	// GAME LOOP

	void ManageCombatLoop();
	void SpawnEnemy();
	void StartUpgradeSequence();
	void GameOver();

public:

	GameManager();
	~GameManager();

	void StartGame();

};