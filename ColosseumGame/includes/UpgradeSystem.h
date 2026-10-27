#pragma once

class PlayerController;
class ConsoleInterface;

class UpgradeSystem
{

private:

	ConsoleInterface& UIManager;
	PlayerController& Controller;

	void UpdateUpgradeInterface(int AvailablePoints);

public:

	UpgradeSystem(ConsoleInterface& InConsole, PlayerController& InController)
	: UIManager(InConsole), Controller(InController) {}

	void UpgradeLoop(int UpgradePoints);

};