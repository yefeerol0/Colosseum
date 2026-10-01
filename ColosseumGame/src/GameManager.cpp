#include "GameManager.h"
#include "PlayerController.h"
#include "GladiatorDataLoader.h"
#include "CombatManager.h"
#include <iostream>
using namespace std;

GameManager::GameManager()
{
	Controller = make_unique<PlayerController>();
	DataLoader = make_unique<GladiatorDataLoader>();
	CombatProcessor = make_unique<CombatManager>();
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

	// TEST

	cout << CurrentEnemy->Name << " has appeared!" << endl;
	cout << CurrentEnemy->Agility << endl;
	cout << CurrentEnemy->Strength << endl;
	cout << CurrentEnemy->Vitality << endl;

	// TEST ENDS
}

void GameManager::SpawnEnemy()
{
	CurrentEnemy = make_unique<Gladiator>(DataLoader->GetEnemy(StageNumber));
}
