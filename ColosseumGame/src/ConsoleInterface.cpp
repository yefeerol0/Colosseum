#include "ConsoleInterface.h"
#include <iostream>
#include <iomanip>
using namespace std;

void ConsoleInterface::ClearConsole()
{
    cout << "\033[2J\033[1;1H"; 

	// An ANSI escape sequence. Previously, I was using system("cls") which was only for Windows, but this works on other systems as well.
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

void ConsoleInterface::DisplayCombatHUD(const ConsoleData& UIData)
{
	// ------TEST----------------

	AddMessageToCombatLog("You have entered the Colosseum!");
	AddMessageToCombatLog("Your opponent is " + UIData.EnemyName + ".");
	AddMessageToCombatLog("Prepare for battle!");
	AddMessageToCombatLog("You have chosen to attack!");
	AddMessageToCombatLog("You have chosen to dodge!");
	AddMessageToCombatLog("You have chosen to heal!");
	AddMessageToCombatLog("You have taken damage!");
	AddMessageToCombatLog("You have healed yourself!");
	AddMessageToCombatLog("You have defeated your opponent!");
	AddMessageToCombatLog("You have been defeated!");
	AddMessageToCombatLog("You have advanced to the next stage!");
	AddMessageToCombatLog("You have been knocked down!");

	// ------TEST END----------------


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
