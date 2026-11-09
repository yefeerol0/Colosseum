#include "GameManager.h"
#include "Gladiator.h"
#include "PlayerController.h"
#include "GladiatorDataLoader.h"
#include "ConsoleInterface.h"
#include "CombatManager.h"
#include "UpgradeSystem.h"
#include "GameTuning.h"

using namespace std;

GameManager::GameManager()
{
	Controller = make_unique<PlayerController>();
	DataLoader = make_unique<GladiatorDataLoader>();
	UIManager = make_unique<ConsoleInterface>();
	CombatProcessor = make_unique<CombatManager>(*UIManager, *Controller);
	UpgradeManager = make_unique<UpgradeSystem>(*UIManager, *Controller);
}

GameManager::~GameManager() {}

void GameManager::StartGame()
{
	while (true)
	{
		PlayRun();
	}
}

void GameManager::PlayRun()
{
	SetupRun();
	StartUpgradePhase(Tuning::StartPoints); // Initial upgrade / character creation, in some way.

	for (int StageNumber = 1; StageNumber <= Tuning::TotalStageCount; ++StageNumber)
	{
		CombatResult Result = StartFight(StageNumber);

		if (Result == CombatResult::PlayerLost)
		{
			GameOver();
			return;
		}
		else if (StageNumber < Tuning::TotalStageCount) // else = CombatResult::PlayerWon
		{
			StartUpgradePhase(Tuning::RewardPoints);
		}
	}

	GameWon();
}

void GameManager::SetupRun()
{
	Controller->ResetStats();
	UIManager->DisplayStartMenu();
	Controller->PressAnyKey();
	UIManager->DisplayStoryScreen();
	Controller->EnterName();
}

CombatResult GameManager::StartFight(int StageNumber)
{
	SpawnEnemy(StageNumber);
	return CombatProcessor->StartCombat(*CurrentEnemy, StageNumber);
}

void GameManager::StartUpgradePhase(int UpgradePoints)
{
	UpgradeManager->UpgradeLoop(UpgradePoints); 
}

void GameManager::SpawnEnemy(int StageNumber)
{
	CurrentEnemy = make_unique<Gladiator>(DataLoader->GetEnemy(StageNumber));
}

void GameManager::GameOver()
{
	UIManager->DisplayGameOverMenu();
	Controller->PressAnyKey();
}

void GameManager::GameWon()
{
	UIManager->DisplayWinScreen();
	Controller->PressAnyKey();
}