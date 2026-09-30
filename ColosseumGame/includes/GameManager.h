#pragma once

class PlayerController;

class GameManager
{
public:

	int StageNumber = 0; // Which enemy the player is going to face, starting from 0.
	PlayerController* Controller;

	GameManager();
	~GameManager();

	void StartGame();
	void DisplayWelcomeText();
	void AskForPlayerName();
	void StartCombatLoop();
};