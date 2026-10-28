#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"

class CombatActions;

struct DecisionParameters
{
	// Passive Parameters (to be cached)

	int SelfMaxHealth;
	int PlayerMaxHealth;

	int StrengthStat;
	int LuckStat;
	int AgilityStat;
	int RecoveryStat;

	int Unpredictability;

	// Active Parameters

	int SelfHealth;
	int PlayerHealth;
	bool isPlayerDodging;
	bool isCounterattacking;
};

class EnemyBehavior
{
public:
	
	RandomGenerator RandomGen;

	float CalculateAttackScore(const DecisionParameters& Params);
	float CalculateDodgeScore(const DecisionParameters& Params);
	float CalculateHealScore(const DecisionParameters& Params);
	float AddRandomnessToScore(float Score, const DecisionParameters& Params);
	ActionTypes DecideAction(const DecisionParameters& Params);
};