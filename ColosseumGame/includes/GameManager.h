#pragma once

class PlayerController;

class GameManager
{
public:

	int EnemyCount = 0;
	PlayerController* playerController;

	GameManager();
	~GameManager();

	void StartGame();

	void DisplayWelcomeText();
	void AskForPlayerName();
	void StartCombat();
};