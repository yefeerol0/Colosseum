#include "ConsoleInterface.h"
#include <iostream>
#include <iomanip>
using namespace std;

void ConsoleInterface::ClearConsole()
{
	cout << "\033[3J\033[2J\033[H" << flush;

	// An ANSI escape sequence. Previously, I was using system("cls") which was only for Windows, but this works on other systems as well.
}

void ConsoleInterface::PrintTitle()
{
	std::cout << R"ASCII(

 ######   ######  ##        ######   ######   ######  ######## ##    ## ##     ##
##    ## ##    ## ##       ##    ## ##    ## ##    ## ##       ##    ## ###   ###
##       ##    ## ##       ##    ## ##       ##       ##       ##    ## #### ####
##       ##    ## ##       ##    ##  ######   ######  ######   ##    ## ## ### ##
##       ##    ## ##       ##    ##       ##       ## ##       ##    ## ##     ##
##    ## ##    ## ##       ##    ## ##    ## ##    ## ##       ##    ## ##     ##
 ######   ######  ########  ######   ######   ######  ########  ######  ##     ##
                                                                              
	)ASCII" << std::endl;
}

void ConsoleInterface::PrintProgression(int StageNumber)
{
    cout << "Stage: " << StageNumber << "/20" << endl;
}

void ConsoleInterface::PrintGladiatorNames(const std::string& PlayerName, const std::string& EnemyName)
{
	cout << left << setw(20) << "PLAYER" << "ENEMY" << endl;
	cout << left << setw(20) << PlayerName << EnemyName << endl;
}

void ConsoleInterface::PrintHealthBars(int PlayerHealth, int PlayerMaxHealth, int EnemyHealth, int EnemyMaxHealth)
{
	cout << left << setw(20) << ("HP: " + to_string(PlayerHealth) + "/" + to_string(PlayerMaxHealth)) 
	<< "HP: " << EnemyHealth << "/" << EnemyMaxHealth << endl;

	// "setw()" adds weight to the left side of the string. Same result would be possible without using any to_strings and 
	// placing setw() between "/" and "PlayerMaxHealth", but it would be less readable and more complicated to understand.
	// This approach makes the whole Player part a singular unit, so setw() can separate the Enemy part from it at once.
}

void ConsoleInterface::AddMessageToCombatLog(const std::string& LogMessage)
{
	CombatLogLines.push_back(LogMessage);

	if (CombatLogLines.size() > MaxLogLines)
	{
		CombatLogLines.pop_front();
	}
}

void ConsoleInterface::PrintCombatLog()
{
	cout << "Combat Log: " << endl;

	for (int i = CombatLogLines.size(); i < MaxLogLines; ++i)
	{
		cout << endl;
	}

	for (const string& LogLine : CombatLogLines)
	{
		cout << LogLine << endl;
	}
}

void ConsoleInterface::PrintActionOptions()
{
	cout << "Choose your next action:" << endl;
	cout << left << setw(12) << "{1} Attack" << setw(12) << "{2} Dodge" << setw(14) << "{3} Heal" << endl;
}

void ConsoleInterface::ClearCombatLog()
{
	CombatLogLines.clear();
}

void ConsoleInterface::DisplayCombatHUD(const ConsoleData& UIData)
{
	ClearConsole();
	cout << "===========================================" << endl;
	PrintProgression(UIData.StageNumber);
	cout << "===========================================" << endl;
	PrintGladiatorNames(UIData.PlayerName, UIData.EnemyName);
	PrintHealthBars(UIData.PlayerHealth, UIData.PlayerMaxHealth, 
					UIData.EnemyHealth, UIData.EnemyMaxHealth);
	cout << "===========================================" << endl;
	PrintCombatLog();
	cout << "===========================================" << endl;
	PrintActionOptions();	
}

void ConsoleInterface::DisplayStartMenu()
{
	ClearConsole();
	PrintTitle();

	cout << "Welcome to the Colosseum!" << endl;
	cout << "\x1b[5mPress any key to start!\x1b[0m\n" << endl; // Another ANSI code for blinking text.

}

void ConsoleInterface::DisplayStoryScreen(const std::string& PlayerName)
{

}

void ConsoleInterface::DisplayUpgradeScreen(UpgradeData& UIData)
{
	ClearConsole();

	cout << "Available Points: " + to_string(UIData.AvailablePoints) + "\n" << endl;
	cout << "Vitality: " + to_string(UIData.Vitality) << endl;
	cout << "Strength: " + to_string(UIData.Strength) << endl;
	cout << "Luck: " + to_string(UIData.Luck) << endl;
	cout << "Agility: " + to_string(UIData.Agility) << endl;
	cout << "Recovery: " + to_string(UIData.Recovery) << endl;
}

void ConsoleInterface::DisplayGameOverMenu()
{
	ClearConsole();
	PrintTitle();

	cout << "You lost!" << endl;
	cout << "\x1b[5mPress any key to re-start!\x1b[0m\n" << endl;
}
