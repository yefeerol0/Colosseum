#include "ConsoleInterface.h"
#include "TextColors.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ConsoleInterface::ClearConsole()
{
	cout << "\033[3J\033[2J\033[H";

	// An ANSI escape sequence. Previously, I was using system("cls"), but this works as well.
}

void ConsoleInterface::PrintSeparator()
{
	cout << GRAY << "=========================================== \n" << RESET;
}

void ConsoleInterface::PrintTitle()
{
	std::cout << RED << R"ASCII(

 ######   ######  ##        ######   ######   ######  ######## ##    ## ##     ##
##    ## ##    ## ##       ##    ## ##    ## ##    ## ##       ##    ## ###   ###
##       ##    ## ##       ##    ## ##       ##       ##       ##    ## #### ####
##       ##    ## ##       ##    ##  ######   ######  ######   ##    ## ## ### ##
##       ##    ## ##       ##    ##       ##       ## ##       ##    ## ##     ##
##    ## ##    ## ##       ##    ## ##    ## ##    ## ##       ##    ## ##     ##
 ######   ######  ########  ######   ######   ######  ########  ######  ##     ##
                                                                              
	)ASCII" << RESET << "\n";
}

void ConsoleInterface::PrintProgression(int StageNumber)
{
    cout << BOLD << YELLOW << "Stage: " << WHITE << StageNumber << "/20" << RESET << "\n";
}

void ConsoleInterface::PrintGladiatorNames(const std::string& PlayerName, const std::string& EnemyName)
{
	cout << GREEN << left << setw(20) << "PLAYER" << RED << "ENEMY" << RESET << "\n";
	cout << WHITE << left << setw(20) << PlayerName << EnemyName << RESET << "\n";
}

void ConsoleInterface::PrintHealthBars(int PlayerHealth, int PlayerMaxHealth, int EnemyHealth, int EnemyMaxHealth)
{
	cout << WHITE << left << setw(20) << ("HP: " + to_string(PlayerHealth) + "/" + to_string(PlayerMaxHealth))
		<< "HP: " << EnemyHealth << "/" << EnemyMaxHealth << RESET << "\n";

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
	cout << BOLD << YELLOW << "Combat Log:" << RESET << "\n";

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
	cout << YELLOW << BLINK << "Choose your next action:" << RESET  "\n";
	cout << RED << left << setw(12) << "{1} Attack" << BLUE << setw(12) << "{2} Dodge" << GREEN << setw(14) << "{3} Heal" << RESET  "\n";
}

void ConsoleInterface::ClearCombatLog()
{
	CombatLogLines.clear();
}

void ConsoleInterface::DisplayCombatHUD(const ConsoleData& UIData)
{
	ClearConsole();

	PrintSeparator(); //-----

	PrintProgression(UIData.StageNumber);

	PrintSeparator(); //-----

	PrintGladiatorNames(UIData.PlayerName, UIData.EnemyName);
	PrintHealthBars(UIData.PlayerHealth, UIData.PlayerMaxHealth, 
					UIData.EnemyHealth, UIData.EnemyMaxHealth);

	PrintSeparator(); //-----

	PrintCombatLog(); 

	PrintSeparator(); //-----

	PrintActionOptions();	
}

void ConsoleInterface::DisplayStartMenu()
{
	ClearConsole();
	PrintTitle();

	cout << BOLD << YELLOW << "Welcome to the Colosseum!" << RESET << "\n";
	cout << BLINK << BOLD << WHITE "Press any key to start!" << RESET << "\n";
}

void ConsoleInterface::DisplayStoryScreen()
{
	ClearConsole();

	cout << ITALIC << WHITE << R"(
 You were once a free man. But now, freedom is the only thing you seek.
 Since you are chained, you were preparing for the Grand Tournament.
 When it all comes down to who will die and who will survive,
 You are determined to reclaim your liberty and beat whoever comes your way.
		 
 Raise your sword, warrior. Your time has come!
	)" << RESET << "\n";

	cout << BLINK << BOLD << YELLOW << "Enter your Gladiator's name: " << RESET;
}

void ConsoleInterface::DisplayUpgradeScreen(const UpgradeData& UIData)
{
	ClearConsole();

	PrintSeparator(); //-----

	cout << ITALIC << YELLOW << "Gladiator,it is time to power up!" << RESET << "\n";
	cout << BOLD << YELLOW << "Available Points: " << WHITE << to_string(UIData.AvailablePoints) << RESET << "\n";

	PrintSeparator(); //-----

	cout << GREEN << "{1} Vitality: " << WHITE << to_string(UIData.Vitality) << RESET << "\n";
	cout << RED << "{2} Strength: " << WHITE << to_string(UIData.Strength) << RESET << "\n";
	cout << ORANGE << "{3} Luck: " << WHITE << to_string(UIData.Luck) << RESET << "\n";
	cout << BLUE << "{4} Agility: " << WHITE << to_string(UIData.Agility) << RESET << "\n";
	cout << LEAF << "{5} Recovery: " << WHITE << to_string(UIData.Recovery) << RESET << "\n";
}

void ConsoleInterface::DisplayGameOverMenu()
{
	ClearConsole();
	PrintTitle();

	cout << ITALIC << RED << R"(
 Everything goes black, as you fall to the ground. 
 The crowd cheers for your opponent, while you are dragged away.
 Was all the bloodshed worth it? You think to yourself.		 
 It is not important anymore, you have fallen...

	)" << RESET << "\n";

	cout << BLINK << "Press any key to restart!" << RESET << "\n";
}

void ConsoleInterface::DisplayWinScreen()
{
	ClearConsole();
	PrintTitle();

	cout << ITALIC << GREEN << R"(
 You drop your sword, as the crowd cheers for you.  You did it. You are victorious. 
 Was all the bloodshed worth it? You think to yourself.
 You played the game by its rules and you won. You walk free. 
 You have survived the Grand Tournament.
		 
 Congratulations gladiator, a new life awaits you...
	
	)" << RESET << "\n";

	cout << BLINK << "Press any key to restart!" << RESET << "\n";
}
