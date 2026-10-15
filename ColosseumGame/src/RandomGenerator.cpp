#include "RandomGenerator.h"

int RandomGenerator::GenerateRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(GetRng());
}

int RandomGenerator::GenerateRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(GetRng());
}

std::mt19937& RandomGenerator::GetRng()
{
    static std::mt19937 rng(std::random_device{}());
    return rng;
}

// RandomGenerator is a utility class that only contains GenerateRandomInt & GenerateRandomFloat.
// My intention doing that was to isolate the random number generation for keeping the rest of the code more readable.