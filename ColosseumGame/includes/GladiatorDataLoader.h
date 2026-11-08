#pragma once
#include "Gladiator.h"
#include "GameTuning.h"
#include <array>

class GladiatorDataLoader
{

private:

    std::array<Gladiator, Tuning::TotalStageCount> GladiatorEnemies;

    // Using type 'vector' instead of 'array' is another sensible approach. (std::vector<Gladiator> GladiatorEnemies;)
	// However, I used 'array' because the number of enemies will be fixed during runtime in this project to maintain scope.

    void LoadFromFile();

public:

    GladiatorDataLoader();

    const Gladiator& GetEnemy(int StageNumber) const;

};