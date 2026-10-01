#include "GladiatorDataLoader.h"
#include "Gladiator.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

GladiatorDataLoader::GladiatorDataLoader()
{
    LoadFromFile();
}

void GladiatorDataLoader::LoadFromFile()
{
    std::ifstream enemyFile("Enemies.json");

    json data = json::parse(enemyFile);
    
    int index = 0;

    for (const nlohmann::json& enemy : data["Enemies"])
    {
        Gladiator gladiator;

        gladiator.Name = enemy.at("Name").get<std::string>();
        gladiator.Vitality = enemy.at("Vitality").get<int>();
        gladiator.Strength = enemy.at("Strength").get<int>();
        gladiator.Luck = enemy.at("Luck").get<int>();
        gladiator.Agility = enemy.at("Agility").get<int>();
        gladiator.Recovery = enemy.at("Recovery").get<int>();

        GladiatorEnemies[index] = gladiator;
        index++;
    }

    // Apparently, the macro: "NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT" automatically does the part in the for loop.
	// However, I wrote the loop manually to learn how the conversion process works. 
}

const Gladiator& GladiatorDataLoader::GetEnemy(int stageNumber)
{
    return GladiatorEnemies[stageNumber - 1];
}
