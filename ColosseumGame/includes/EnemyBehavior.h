#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"

struct DecisionParameters
{
	// Passive Parameters (to be cached)

	int SelfMaxHealth = 0;
	int PlayerMaxHealth = 0;

	int StrengthStat = 0;
	int LuckStat = 0;
	int AgilityStat = 0;
	int RecoveryStat = 0;

	float Unpredictability = 0.0f;

	// Active Parameters

	int SelfHealth = 0;
	int PlayerHealth = 0;
	bool IsOutOfHeals = false;
	bool IsPlayerDodging = false;
	bool IsCounterattacking = false;
};

class EnemyBehavior
{
private:

	RandomGenerator RandomGen;

	float CalculateAttackScore(const DecisionParameters& Params);
	float CalculateDodgeScore(const DecisionParameters& Params);
	float CalculateHealScore(const DecisionParameters& Params);
	float AddRandomnessToScore(float Score, const DecisionParameters& Params);

public:

	ActionTypes DecideAction(const DecisionParameters& Params);
};