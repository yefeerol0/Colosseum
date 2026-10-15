#pragma once
#include <random>

class RandomGenerator
{
public:

	int GenerateRandomInt(int min, int max);
	int GenerateRandomFloat(float min, float max);

private:

	static std::mt19937& GetRng();

};