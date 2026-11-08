#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"

struct DecisionParameters
{
	// Passive Parameters (to be cached)

	int SelfMaxHealth;
	int PlayerMaxHealth;

	int StrengthStat;
	int LuckStat;
	int AgilityStat;
	int RecoveryStat;

	float Unpredictability;

	// Active Parameters

	int SelfHealth;
	int PlayerHealth;
	bool IsPlayerDodging;
	bool IsCounterattacking;
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