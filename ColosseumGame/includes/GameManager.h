#pragma once
#include "CombatResult.h"
#include <memory>

struct Gladiator;

class PlayerController;
class GladiatorDataLoader;
class ConsoleInterface;
class CombatManager;
class UpgradeSystem;

class GameManager
{

private:

	// Pointers

	std::unique_ptr<PlayerController> Controller;
	std::unique_ptr<GladiatorDataLoader> DataLoader;
	std::unique_ptr<ConsoleInterface> UIManager;
	std::unique_ptr<CombatManager> CombatProcessor;
	std::unique_ptr<Gladiator> CurrentEnemy;
	std::unique_ptr<UpgradeSystem> UpgradeManager;
	
	// UPGRADE SYSTEM

	void StartUpgradePhase(int UpgradePoints);

	// GAME LOOP

	void PlayRun();
	void SetupRun();
	void SpawnEnemy(int StageNumber);
	CombatResult StartFight(int StageNumber);
	void GameOver();
	void GameWon();

public:

	GameManager();
	~GameManager();

	void StartGame();

};