#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"

using namespace Wanted;

class WhiteEffect : public Actor
{
	RTTI_DECLARATIONS(WhiteEffect, Actor);

public :

	WhiteEffect(Vector2 position, Actor* actor);
	~WhiteEffect();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	bool IsActuallyAttacking() const {return elapsedTime >= warningDuration;}
private :

	Actor* actor;

	Vector2 rootPosition;
	float elapsedTime = 0.0f;
	float warningDuration = 1.0f; // 빨간색 유지 시간
	float attackDuration = 0.5f;  // 흰색 유지 시간
	int targetWidth;
	int targetHeight;

	bool isWarning = false; // 플레이어에게 피격하는 조건
	const char* icon;
};

