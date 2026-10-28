#include "EnemyBehavior.h"

float EnemyBehavior::CalculateAttackScore(const DecisionParameters& Params)
{
	int PlayerHealthPercentage = (Params.PlayerHealth * 100) / Params.PlayerMaxHealth;

	float AttackScore = ((float)Params.StrengthStat * 0.025f) + ((float)Params.LuckStat * 0.025f);

	if (PlayerHealthPercentage <= 20)
	{
		AttackScore += 0.5f; // Almost always attack if player health is below 20%.
	}

	if (Params.isCounterattacking)
	{
		AttackScore += 0.4f; // Unless you are in critical condition, attack if it is a counterattack.
	}

	if (Params.isPlayerDodging)
	{
		AttackScore -= 0.3f;
	}

	AttackScore = AddRandomnessToScore(AttackScore, Params);

	return AttackScore;
}

float EnemyBehavior::CalculateDodgeScore(const DecisionParameters& Params)
{
	float DodgeScore = ((float)Params.LuckStat * 0.025f) + ((float)Params.AgilityStat * 0.025f);

	DodgeScore = AddRandomnessToScore(DodgeScore, Params);

	return DodgeScore;
}

float EnemyBehavior::CalculateHealScore(const DecisionParameters& Params)
{
	int HealthPercentage = (Params.SelfHealth * 100) / Params.SelfMaxHealth;

	float HealScore = (0.5f - (float)HealthPercentage * 0.01f) + (float)Params.RecoveryStat * 0.025f;

	if (HealthPercentage >= 75)
	{
		HealScore += -1.0f;
	}
	else if (HealthPercentage <= 20)
	{
		HealScore += 0.4f; // Almost always heal if health is below 20%.
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
