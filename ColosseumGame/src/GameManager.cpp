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
	DisplayWelcomeText();
	AskForPlayerName();
	string name = Controller->EnterName();
	cout << "Welcome, " << name << "!" << endl;
	ManageCombatLoop();
}

void GameManager::DisplayWelcomeText()
{
	cout << "Welcome to the Colosseum!" << endl;
}

void GameManager::AskForPlayerName()
{
	cout << "Please enter your Gladiator's name: ";
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
		StartUpgradeSequence();
	}
}

void GameManager::StartUpgradeSequence()
{
	ManageCombatLoop();

	// This section is yet to be completed.
}

void GameManager::SpawnEnemy()
{
	CurrentEnemy = make_unique<Gladiator>(DataLoader->GetEnemy(StageNumber));
}

void GameManager::GameOver()
{
	cout << "Game Over!" << endl;
}
