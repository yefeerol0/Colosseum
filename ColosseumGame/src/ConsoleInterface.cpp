#include "ConsoleInterface.h"
#include <iostream>
#include <iomanip>
using namespace std;

void ConsoleInterface::ClearConsole()
{
	cout << "\033[3J\033[2J\033[H";

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
                                                                              
	)ASCII" << "\n";
}

void ConsoleInterface::PrintProgression(int StageNumber)
{
    cout << "Stage: " << StageNumber << "/20 \n";
}

void ConsoleInterface::PrintGladiatorNames(const std::string& PlayerName, const std::string& EnemyName)
{
	cout << left << setw(20) << "PLAYER" << "ENEMY \n";
	cout << left << setw(20) << PlayerName << EnemyName << "\n";
}

void ConsoleInterface::PrintHealthBars(int PlayerHealth, int PlayerMaxHealth, int EnemyHealth, int EnemyMaxHealth)
{
	cout << left << setw(20) << ("HP: " + to_string(PlayerHealth) + "/" + to_string(PlayerMaxHealth))
		<< "HP: " << EnemyHealth << "/" << EnemyMaxHealth << "\n";

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
	cout << "Combat Log: \n";

	for (size_t i = CombatLogLines.size(); i < MaxLogLines; ++i)
	{
		cout << "\n";
	}

	for (const string& LogLine : CombatLogLines)
	{
		cout << LogLine + "\n";
	}
}

void ConsoleInterface::PrintActionOptions()
{
	cout << "Choose your next action: \n";
	cout << left << setw(12) << "{1} Attack" << setw(12) << "{2} Dodge" << setw(14) << "{3} Heal \n";
}

void ConsoleInterface::ClearCombatLog()
{
	CombatLogLines.clear();
}

void ConsoleInterface::DisplayCombatHUD(const ConsoleData& UIData)
{
	ClearConsole();

	cout << "=========================================== \n";
	PrintProgression(UIData.StageNumber);
	cout << "=========================================== \n";
	PrintGladiatorNames(UIData.PlayerName, UIData.EnemyName);
	PrintHealthBars(UIData.PlayerHealth, UIData.PlayerMaxHealth, 
					UIData.EnemyHealth, UIData.EnemyMaxHealth);
	cout << "=========================================== \n";
	PrintCombatLog();
	cout << "=========================================== \n";
	PrintActionOptions();	
}

void ConsoleInterface::DisplayStartMenu()
{
	ClearConsole();
	PrintTitle();

	cout << "Welcome to the Colosseum! \n";
	cout << "\x1b[5mPress any key to start!\x1b[0m \n"; // Another ANSI code for blinking text.

}

void ConsoleInterface::DisplayStoryScreen()
{
	ClearConsole();

	cout << R"(
	
	You were once a free man. But now, freedom is the only thing you seek.
	Since you are chained, you were preparing for the Grand Tournament.
	When it all comes down to who will die and who will survive,
	You are determined to reclaim your liberty and beat whoever comes your way.
		 
	Raise your sword, warrior. Your time has come!
	
	)" << "\n";

	cout << "\x1b[5mEnter your Gladiator's name: \x1b[0m";
}

void ConsoleInterface::DisplayUpgradeScreen(const UpgradeData& UIData)
{
	ClearConsole();

	cout << "Available Points: " + to_string(UIData.AvailablePoints) + "\n";
	cout << "Vitality: " + to_string(UIData.Vitality) + "\n";
	cout << "Strength: " + to_string(UIData.Strength) + "\n";
	cout << "Luck: " + to_string(UIData.Luck) + "\n";
	cout << "Agility: " + to_string(UIData.Agility) + "\n";
	cout << "Recovery: " + to_string(UIData.Recovery) + "\n";
}

void ConsoleInterface::DisplayGameOverMenu()
{
	ClearConsole();
	PrintTitle();

	cout << "You lost! \n";
	cout << "\x1b[5mPress any key to re-start!\x1b[0m \n";
}
