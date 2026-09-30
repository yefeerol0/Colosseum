#include "GameManager.h"
#include "PlayerController.h"
#include "Gladiator.h"
#include <iostream>
using namespace std;

GameManager::GameManager()
{
	Controller = new PlayerController();
}

GameManager::~GameManager()
{
	delete Controller;
}

void GameManager::StartGame()
{
	DisplayWelcomeText();
	AskForPlayerName();
	string name = Controller->EnterName();
	cout << "Welcome, " << name << "!" << endl;

	// --- TEST ---

	cout << "\n" << endl;
	cout << "Your Gladiator's name is: " << Controller->PlayerGladiator->Name << endl;
	cout << "Your Gladiator's Vitality is: " << Controller->PlayerGladiator->Vitality << endl;
	cout << "Your Gladiator's Strength is: " << Controller->PlayerGladiator->Strength << endl;
	cout << "Your Gladiator's Luck is: " << Controller->PlayerGladiator->Luck << endl;
	
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

void GameManager::StartCombatLoop()
{
	StageNumber++;

}
