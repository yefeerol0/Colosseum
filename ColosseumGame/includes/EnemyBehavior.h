#pragma once
#include "RandomGenerator.h"
#include "ActionTypes.h"

//enum class ActionTypes : int;
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

	float CalculateAttackScore(DecisionParameters& DecisionParameters);
	float CalculateDodgeScore(DecisionParameters& DecisionParameters);
	float CalculateHealScore(DecisionParameters& DecisionParameters);
	float AddRandomnessToScore(float Score, DecisionParameters& DecisionParameters);
	ActionTypes DecideAction(DecisionParameters& DecisionParameters);
};