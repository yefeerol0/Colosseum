#pragma once

// This header exists to store all the game tuning parameters in one place for quick access.

namespace Tuning
{
	// Gladiator

	constexpr int HealthPerVitality = 10;

	// GameManager

	constexpr int TotalStageCount = 20;

	constexpr int StartPoints = 15; // Upgrade points given at the start of game.
	constexpr int RewardPoints = 3; // Upgrade points given after each combat won.

	// CombatActions

	constexpr int StrengthDivisor = 2;
	constexpr int RecoveryDivisor = 2;

	constexpr int CounterattackCritBonus = 20;
	constexpr int DodgeActionBonus = 20;

	constexpr int CritChanceLimit = 72;
	constexpr int DodgeChanceLimit = 72;

	constexpr int CritDamageMultiplier = 2;

	constexpr int CritChancePerLuck = 4;
	constexpr int DodgeChancePerAgility = 4;

	// EnemyBehavior

	// AS = "Attack Score", DS = "Dodge Score", HS = "Heal Score"

	constexpr int CriticalStatePercentage = 20; // The health percentage that is considered 'critical'.
	constexpr int SafeStatePercentage = 75; // The health percentage that is considered 'safe'. 

	constexpr float AS_StrengthRatio = 0.025f;
	constexpr float AS_LuckRatio = 0.025f;
	constexpr float AS_CriticalStateBonus = 0.5f;
	constexpr float AS_CounterattackBonus = 0.4f;
	constexpr float AS_DodgePenalty = 0.3f;

	constexpr float DS_LuckRatio = 0.025f;
	constexpr float DS_AgilityRatio = 0.025f;

	constexpr float HS_ScoreBaseline = 0.5f;
	constexpr float HS_HealthPercentageRatio = 0.01f;
	constexpr float HS_RecoveryRatio = 0.025f;
	constexpr float HS_SafeStatePenalty = 1.0f;
	constexpr float HS_CriticalStateBonus = 0.4f;
}