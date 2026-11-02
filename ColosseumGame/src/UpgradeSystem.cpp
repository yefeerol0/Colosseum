#include "UpgradeSystem.h"
#include "StatTypes.h"
#include "PlayerController.h"
#include "ConsoleInterface.h"

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
	UIManager.DisplayUpgradeScreen(Controller.GetUpgradeData(AvailablePoints));
}
