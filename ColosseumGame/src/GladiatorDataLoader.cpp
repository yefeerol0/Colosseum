#include "GladiatorDataLoader.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept> // json.hpp apparently already includes this, but I added it to prevent confusion.

using json = nlohmann::json;

GladiatorDataLoader::GladiatorDataLoader()
{
    LoadFromFile();
}

void GladiatorDataLoader::LoadFromFile()
{
    std::ifstream enemyFile("Enemies.json");

    json data = json::parse(enemyFile);
    
	if (data.at("Enemies").size() != GladiatorEnemies.size())
	{
		throw std::runtime_error("The number of enemies in the JSON file is: " + 
                                std::to_string(data.at("Enemies").size()) +
                                " while the expected number is: " +
                                std::to_string(GladiatorEnemies.size()));
	}

    int index = 0;

    for (const nlohmann::json& enemy : data["Enemies"])
    {
        Gladiator gladiator;

        gladiator.Name = enemy.at("Name").get<std::string>();
        gladiator.Stats.Vitality = enemy.at("Vitality").get<int>();
        gladiator.Stats.Strength = enemy.at("Strength").get<int>();
        gladiator.Stats.Luck = enemy.at("Luck").get<int>();
        gladiator.Stats.Agility = enemy.at("Agility").get<int>();
        gladiator.Stats.Recovery = enemy.at("Recovery").get<int>();
		gladiator.EnemyUnpredictability = enemy.at("EnemyUnpredictability").get<float>();

        GladiatorEnemies.at(index) = gladiator;
        index++;
    }

    // Apparently, the macro: "NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT" automatically does the part in the for loop.
	// However, I wrote the loop manually to learn how the conversion process works. 
}

const Gladiator& GladiatorDataLoader::GetEnemy(int StageNumber) const
{
    return GladiatorEnemies.at(StageNumber - 1);
}
