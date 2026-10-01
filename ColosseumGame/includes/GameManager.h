#pragma once
#include <memory>

class PlayerController;
class CombatManager;
class GladiatorDataLoader;
struct Gladiator;

class GameManager
{

private:

	int StageNumber = 0; // Which enemy the player is going to face, starting from 0, incremented at the start of each combat.

	// Pointers

	std::unique_ptr<PlayerController> Controller;
	std::unique_ptr<GladiatorDataLoader> DataLoader;
	std::unique_ptr<CombatManager> CombatProcessor;
	std::unique_ptr<Gladiator> CurrentEnemy;

	void DisplayWelcomeText();
	void AskForPlayerName();
	void ManageCombatLoop();
	void SpawnEnemy();

public:

	GameManager();
	~GameManager();

	void StartGame();

};