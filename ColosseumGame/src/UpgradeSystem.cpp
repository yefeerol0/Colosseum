#include "UpgradeSystem.h"
#include "StatTypes.h"
#include "PlayerController.h"
#include "ConsoleInterface.h"
#include "Gladiator.h"

void UpgradeSystem::UpgradeLoop(int UpgradePoints)
{
	int AvailablePoints = UpgradePoints;

	while (AvailablePoints > 0)
	{
		UpdateUpgradeInterface(AvailablePoints);

		StatTypes SelectedStat = Controller.SelectStat();

		while (SelectedStat == StatTypes::Invalid)
		{
			SelectedStat = Controller.SelectStat();
		}

		Controller.ApplyUpgrade(SelectedStat);
		AvailablePoints--;	
	}
}

void UpgradeSystem::UpdateUpgradeInterface(int AvailablePoints)
{
	UpgradeData UIData;

	UIData.AvailablePoints = AvailablePoints;
	UIData.Vitality = Controller.PlayerGladiator->Stats.Vitality;
	UIData.Strength = Controller.PlayerGladiator->Stats.Strength;
	UIData.Luck = Controller.PlayerGladiator->Stats.Luck;
	UIData.Agility = Controller.PlayerGladiator->Stats.Agility;
	UIData.Recovery = Controller.PlayerGladiator->Stats.Recovery;

	UIManager.DisplayUpgradeScreen(UIData);

	// Law of Demeter failure here, I will be fixing it later on. 
}
