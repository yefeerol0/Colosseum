#pragma once

struct DecisionParameters
{
	int SelfHealth;
	int PlayerHealth;
	int PersonalityBonus;
	bool isPlayerDodging;
};

class EnemyBehavior
{
public:
	
	float CalculateAgression(DecisionParameters& DecisionParameters);
	int DecideAction(DecisionParameters& DecisionParameters);
};