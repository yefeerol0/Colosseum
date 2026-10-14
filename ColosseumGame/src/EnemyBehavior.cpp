#include "EnemyBehavior.h"

float EnemyBehavior::CalculateAgression(DecisionParameters& DecisionParameters)
{
	return 0.0f;
}

int EnemyBehavior::DecideAction(DecisionParameters& DecisionParameters)
{
	float AgressionLevel = CalculateAgression(DecisionParameters);

	if (AgressionLevel < 33.0f)
	{
		return 0; // Defensive action
	}
	else if (AgressionLevel < 67.0f)
	{
		return 1; // Balanced action
	}
	else
	{
		return 2; // Aggressive action
	}
}
