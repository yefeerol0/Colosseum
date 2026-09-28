#include "GameManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include <iostream>
using namespace std;

GameManager::GameManager()
{
	playerController = new PlayerController();
}

GameManager::~GameManager()
{
	delete playerController;
}

void GameManager::StartGame()
{
	DisplayWelcomeText();
	AskForPlayerName();
	string name = playerController->EnterName();
	cout << "Welcome, " << name << "!" << endl;

	// --- TEST ---

	cout << "\n" << endl;
	cout << "Your Gladiator's name is: " << playerController->PlayerGladiator->Name << endl;
	cout << "Your Gladiator's Vitality is: " << playerController->PlayerGladiator->Vitality << endl;
	cout << "Your Gladiator's Strength is: " << playerController->PlayerGladiator->Strength << endl;
	cout << "Your Gladiator's Luck is: " << playerController->PlayerGladiator->Luck << endl;
	
	// --- TEST END ---
}

void GameManager::DisplayWelcomeText()
{
	cout << "Welcome to the Colosseum!" << endl;
}

void GameManager::AskForPlayerName()
{
	cout << "Please enter your Gladiator's name: ";
}

void GameManager::StartCombat()
{
}
