#pragma once
#include <deque>
#include <string>

struct ConsoleData
{
	std::string PlayerName = "";
	std::string EnemyName = "";
	int StageNumber = 0;
	int PlayerHealth = 0;
	int PlayerMaxHealth = 0;
	int EnemyHealth = 0;
	int EnemyMaxHealth = 0;
};

class ConsoleInterface
{
private:

	std::deque<std::string> CombatLogLines;
	int MaxLogLines = 8;

	void ClearConsole();

	// Menu Functions

	void PrintTitle();

	// HUD Functions

	void PrintProgression(int StageNumber);
	void PrintGladiatorNames(const std::string& PlayerName, const std::string& EnemyName);
	void PrintHealthBars(int PlayerHealth, int PlayerMaxHealth, int EnemyHealth, int EnemyMaxHealth);

	// Combat Log Functions

	void PrintCombatLog();
	void PrintActionOptions();


public:

	void ClearCombatLog();
	void AddMessageToCombatLog(const std::string& LogMessage);
	void DisplayCombatHUD(const ConsoleData& UIData);

	// Other Screens

	void DisplayStartMenu();
	void DisplayStoryScreen(const std::string& PlayerName);
	void DisplayUpgradeScreen(int Points, ConsoleData& Stats);
	void DisplayGameOverMenu();

};