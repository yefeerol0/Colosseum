#include "EnemyBehavior.h"

float EnemyBehavior::CalculateAttackScore(DecisionParameters& DecisionParameters)
{
	int PlayerHealthPercentage = (DecisionParameters.PlayerHealth * 100) / DecisionParameters.PlayerMaxHealth;	

	float AttackScore = ((float)DecisionParameters.StrengthStat * 0.025f) + ((float)DecisionParameters.LuckStat * 0.025f);

	if (PlayerHealthPercentage <= 20)
	{
		AttackScore += 0.5f; // Almost always attack if player health is below 20%.
	}

	if (DecisionParameters.isCounterattacking)
	{
		AttackScore += 0.4f; // Unless you are in critical condition, attack if it is a counterattack.
	}

	if (DecisionParameters.isPlayerDodging)
	{
		AttackScore -= 0.3f;
	}

	AttackScore = AddRandomnessToScore(AttackScore, DecisionParameters);

	return AttackScore;
}

float EnemyBehavior::CalculateDodgeScore(DecisionParameters& DecisionParameters)
{
	float DodgeScore = ((float)DecisionParameters.LuckStat * 0.025f) + ((float)DecisionParameters.AgilityStat * 0.025f);

	DodgeScore = AddRandomnessToScore(DodgeScore, DecisionParameters);

	return DodgeScore;
}

float EnemyBehavior::CalculateHealScore(DecisionParameters& DecisionParameters)
{
	int HealthPercentage = (DecisionParameters.SelfHealth * 100) / DecisionParameters.SelfMaxHealth;

	float HealScore = (0.5f - (float)HealthPercentage * 0.01f) + (float)DecisionParameters.RecoveryStat * 0.025f;

	if (HealthPercentage >= 75)
	{
		HealScore += -1.0f;
	}
	else if (HealthPercentage <= 20)
	{
		HealScore += 0.4f; // Almost always heal if health is below 20%.
	}

	HealScore = AddRandomnessToScore(HealScore, DecisionParameters);

	return HealScore;
}

float EnemyBehavior::AddRandomnessToScore(float Score, DecisionParameters& DecisionParameters)
{
	float RandomnessAmount = DecisionParameters.Unpredictability;

	Score += RandomGen.GenerateRandomFloat(-RandomnessAmount, RandomnessAmount);

	return Score;
}

EnemyActionOptions EnemyBehavior::DecideAction(DecisionParameters& DecisionParameters)
{
	float AttackScore = CalculateAttackScore(DecisionParameters);
	float DodgeScore = CalculateDodgeScore(DecisionParameters);
	float HealScore = CalculateHealScore(DecisionParameters);

	if (AttackScore >= DodgeScore && AttackScore >= HealScore)
	{
		return EnemyActionOptions::Attack;
	}
	else if (DodgeScore >= HealScore)
	{
		return EnemyActionOptions::Dodge;
	}
	else
	{
		return EnemyActionOptions::Heal;
	}
}
