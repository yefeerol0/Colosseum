#include "GameManager.h"
#include "PlayerController.h"
#include "GladiatorDataLoader.h"
#include "ConsoleInterface.h"
#include "CombatManager.h"
#include <iostream>

using namespace std;

GameManager::GameManager()
{
	Controller = make_unique<PlayerController>();
	DataLoader = make_unique<GladiatorDataLoader>();
	UIManager = make_unique<ConsoleInterface>();
	CombatProcessor = make_unique<CombatManager>(*UIManager);
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
	int AvailablePoints = UpgradePoints;

	StatTypes SelectedStat = Controller->SelectStat();

	while (AvailablePoints > 0)
	{
		while (SelectedStat == StatTypes::Invalid)
		{
			SelectedStat = Controller->SelectStat();
		}

		AvailablePoints--;
	}

	ManageCombatLoop();

}

void GameManager::ManageCombatLoop()
{
	StageNumber++;
	SpawnEnemy();

	CombatResult Result = CombatProcessor->StartCombat(*Controller, *CurrentEnemy, StageNumber);

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
