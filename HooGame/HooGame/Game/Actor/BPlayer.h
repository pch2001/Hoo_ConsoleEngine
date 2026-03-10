#pragma once

#include "Actor/Actor.h"
#include <vector>
#include <string>
#include <iostream>
#include <Math/Vector2.h>
#include <Util/EngineTimer.h>


using namespace Wanted;
class BPlayer : public Actor
{
	RTTI_DECLARATIONS(BPlayer, Actor)
public :
	BPlayer();
	~BPlayer();

	virtual void Tick(float deltaTime) override;

	void Move(int x, int y);
	void Damaged(int x);

	void Die();

	void UIUpdate();

	void Attack(Vector2 dir);

	float GetMaxHp() { return MaxHP; }
	float GetHP() { return HP; }
	void SetHP(int hp) { HP += hp; }

	int GetPoint() { return (point); }
	void SetPoint(int pointchange) { point += pointchange; }

	void SetisMine() { isMine = true; }
	void SetisnotMine() { isMine = false; }

private :
	EngineTimer moveTimer{};
	Vector2 dir;
	float MaxHP = 5;
	float HP;

	bool isMine = false;

	int point = 100;

};

