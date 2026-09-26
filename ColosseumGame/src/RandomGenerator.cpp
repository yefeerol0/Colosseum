#include "RandomGenerator.h"
#include <random>

int RandomGenerator::GenerateRandomInt(int min, int max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// RandomGenerator is a utility class that only contains GenerateRandomInt.
// My intention doing that was to isolate the random number generation for keeping the rest of the code more readable.