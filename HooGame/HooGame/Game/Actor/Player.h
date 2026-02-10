#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"
#include "Physics/Physics.h"

#include <string>
#include <vector>
using namespace Wanted;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:



	Player();
	~Player();

	bool IsRightDirection() const { return rightDirection; }

private:
	virtual void Tick(float deltaTime) override;

	virtual void OnOverlap(Actor* actor) override; 


	// 오른쪽으로 이동하는 함수.
	void MoveRight();
	
	// 왼쪽으로 이동하는 함수.
	void MoveLeft();

	// 점프하는 함수
	void Jump(float deltaTime);

	// 공격하는 함수
	void Attack();

public :

	void Upgrade();

	void Downgrade();


private:

	std::vector<std::string> images = { "P", "PP", "PPP", "PPPP", "PPPPP"};

	int currentLevel = 0;

	bool rightDirection = true;

	// 타이머 변수.
	//EngineTimer engine;
	//Wanted::EngineTimer timer;
	int jumpStepsRemaining = 0;

	EngineTimer timer{0.1f};

	//땅 높이
	int groundY = 0;

	//무적 무적인지 체크;
	bool invincibleBool = false;

	EngineTimer invincibleTimer;//무적 타이머
	EngineTimer blinkTimer;	//색상 바꾸는 타이머

};
