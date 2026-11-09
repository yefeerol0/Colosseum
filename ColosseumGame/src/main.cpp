#include "GameManager.h"
#include <exception>
#include <iostream>

int main()
{
	try
	{
		GameManager gameManager;
		gameManager.StartGame();
		return 0; // Never reached as the game loop checks conditions, but is kept for clarity.
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		std::cin.get(); // Wait for input before closing the console window immediately, so the error can be seen.
		return 1;
	}
}