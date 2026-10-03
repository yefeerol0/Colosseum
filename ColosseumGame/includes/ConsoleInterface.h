#pragma once
#include <string>

class ConsoleInterface
{
private:

	void ClearConsole();
	void PrintProgression(int StageNumber);
	void PrintGladiatorNames(std::string& PlayerName, std::string& EnemyName);
	void PrintHealthBars(int PlayerHealth, int EnemyHealth);

public:

	void DisplayCombatHUD(int StageNumber, int PlayerHealth, int EnemyHealth);

};