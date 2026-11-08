#include "EnemyBehavior.h"
#include "GameTuning.h"
using namespace Tuning;

float EnemyBehavior::CalculateAttackScore(const DecisionParameters& Params)
{
	int PlayerHealthPercentage = (Params.PlayerHealth * 100) / Params.PlayerMaxHealth;

	float AttackScore = ((float)Params.StrengthStat * AS_StrengthRatio) + ((float)Params.LuckStat * AS_LuckRatio);

	if (PlayerHealthPercentage <= CriticalStatePercentage)
	{
		AttackScore += AS_CriticalStateBonus; // Almost always attack if player health is in critical state.
	}

	if (Params.IsCounterattacking)
	{
		AttackScore += AS_CounterattackBonus; // Unless you are in critical condition, attack if it is a counterattack.
	}

	if (Params.IsPlayerDodging)
	{
		AttackScore -= AS_DodgePenalty;
	}

	AttackScore = AddRandomnessToScore(AttackScore, Params);

	return AttackScore;
}

float EnemyBehavior::CalculateDodgeScore(const DecisionParameters& Params)
{
	float DodgeScore = ((float)Params.LuckStat * DS_LuckRatio) + ((float)Params.AgilityStat * DS_AgilityRatio);

	DodgeScore = AddRandomnessToScore(DodgeScore, Params);

	return DodgeScore;
}

float EnemyBehavior::CalculateHealScore(const DecisionParameters& Params)
{
	int HealthPercentage = (Params.SelfHealth * 100) / Params.SelfMaxHealth;

	float HealScore = (HS_ScoreBaseline - (float)HealthPercentage * HS_HealthPercentageRatio) + (float)Params.RecoveryStat * HS_RecoveryRatio;

	if (HealthPercentage >= SafeStatePercentage)
	{
		HealScore -= HS_SafeStatePenalty; // Almost never heal if health is in safe state.
	}
	else if (HealthPercentage <= CriticalStatePercentage)
	{
		HealScore += HS_CriticalStateBonus; // Almost always heal if health is in critical state.
	}

	HealScore = AddRandomnessToScore(HealScore, Params);

	return HealScore;
}

float EnemyBehavior::AddRandomnessToScore(float Score, const DecisionParameters& Params)
{
	float RandomnessAmount = Params.Unpredictability;

	Score += RandomGen.GenerateRandomFloat(-RandomnessAmount, RandomnessAmount);

	return Score;
}

ActionTypes EnemyBehavior::DecideAction(const DecisionParameters& Params)
{
	float AttackScore = CalculateAttackScore(Params);
	float DodgeScore = CalculateDodgeScore(Params);
	float HealScore = CalculateHealScore(Params);

	if (AttackScore >= DodgeScore && AttackScore >= HealScore)
	{
		return ActionTypes::Attack;
	}
	else if (DodgeScore >= HealScore)
	{
		return ActionTypes::Dodge;
	}
	else
	{
		return ActionTypes::Heal;
	}
}
