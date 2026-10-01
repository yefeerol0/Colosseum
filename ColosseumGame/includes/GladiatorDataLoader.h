#pragma once
#include "Gladiator.h"
#include <array>

class GladiatorDataLoader
{

private:

    std::array<Gladiator, 20> GladiatorEnemies;

    // Using type 'vector' instead of 'array' is another sensible approach. (std::vector<Gladiator> GladiatorEnemies;)
	// However, I used 'array' because the number of enemies will be fixed for this project to maintain scope.

public:

    GladiatorDataLoader();
    void LoadFromFile();
    const Gladiator& GetEnemy(int stageNumber);

};