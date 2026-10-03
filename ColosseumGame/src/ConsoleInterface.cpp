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
    cout << "Stage: " << StageNumber << endl;
}

void ConsoleInterface::PrintGladiatorNames(std::string& PlayerName, std::string& EnemyName)
{
    cout << left << setw(15) << "Player: " << PlayerName << endl;
    cout << left << setw(15) << "Enemy: " << EnemyName << endl;
}

void ConsoleInterface::PrintHealthBars(int PlayerHealth, int EnemyHealth)
{
    cout << left << setw(15) << "Player Health: " << PlayerHealth << endl;
	cout << "===============================" << endl;
    cout << left << setw(15) << "Enemy Health: " << EnemyHealth << endl;
}

void ConsoleInterface::DisplayCombatHUD(int StageNumber, int PlayerHealth, int EnemyHealth)
{
	ClearConsole();
	cout << "===============================" << endl;
	PrintProgression(StageNumber);
	cout << "===============================" << endl;
	PrintHealthBars(PlayerHealth, EnemyHealth);
	cout << "===============================" << endl;
}
