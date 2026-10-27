#include "GameManager.h"
#include "PlayerController.h"
#include "GladiatorDataLoader.h"
#include "ConsoleInterface.h"
#include "CombatManager.h"
#include "UpgradeSystem.h"
#include <iostream>

using namespace std;

GameManager::GameManager()
{
	Controller = make_unique<PlayerController>();
	DataLoader = make_unique<GladiatorDataLoader>();
	UIManager = make_unique<ConsoleInterface>();
	CombatProcessor = make_unique<CombatManager>(*UIManager, *Controller);
	UpgradeManager = make_unique<UpgradeSystem>(*UIManager, *Controller);
}

GameManager::~GameManager() {}

void GameManager::StartGame()
{
	StageNumber = 0;

	UIManager->DisplayStartMenu();
	Controller->PressAnyKey();
	AskForPlayerName();
	StartUpgradePhase(StartPoints);
}

void GameManager::AskForPlayerName()
{
	cout << "Please enter your Gladiator's name: ";
	string name = Controller->EnterName();
	cout << name << ", Welcome to the Colosseum!" << endl;
}

void GameManager::StartUpgradePhase(int UpgradePoints)
{
	UpgradeManager->UpgradeLoop(UpgradePoints);

	ManageCombatLoop();
}

void GameManager::ManageCombatLoop()
{
	StageNumber++;
	SpawnEnemy();

	CombatResult Result = CombatProcessor->StartCombat(*CurrentEnemy, StageNumber);

	if (Result == CombatResult::PlayerLost)
	{
		GameOver();
		return;
	}
	else
	{
		StartUpgradePhase(RewardPoints);
	}
}

void GameManager::SpawnEnemy()
{
	CurrentEnemy = make_unique<Gladiator>(DataLoader->GetEnemy(StageNumber));
}

void GameManager::GameOver()
{
	UIManager->DisplayGameOverMenu();
	Controller->PressAnyKey();
	StartGame();
}
