#include "json.hpp"
#include "GladiatorDataLoader.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

std::vector<Gladiator> GladiatorDataLoader::LoadFromFile()
{
	std::ifstream file("Enemies.json");
	nlohmann::json data = nlohmann::json::parse(file);
	std::cout << data["Enemies"][0]["Name"] << "\n";
	return std::vector<Gladiator>();
}
