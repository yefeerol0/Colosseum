#pragma once

class Gladiator;

class CombatManager
{
public:

	void Attack(Gladiator& Enemy, int Damage);
	void Dodge(Gladiator& Player, Gladiator& Enemy);
	void Heal(Gladiator& Player, int Amount);

};