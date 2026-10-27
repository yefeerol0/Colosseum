#pragma once
#include <memory>

class PlayerController;
class GladiatorDataLoader;
class ConsoleInterface;
class CombatManager;
class UpgradeSystem;

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
	std::unique_ptr<UpgradeSystem> UpgradeManager;

	// GAME START

	void WaitForStartInput();
	void AskForPlayerName();
	
	// UPGRADE SYSTEM

	void StartUpgradePhase(int UpgradePoints);

	int StartPoints = 15; // Upgrade points given at the start of game.
	int RewardPoints = 3; // Upgrade points given after each combat won.


	// GAME LOOP

	void ManageCombatLoop();
	void SpawnEnemy();
	void GameOver();

public:

	GameManager();
	~GameManager();

	void StartGame();

};