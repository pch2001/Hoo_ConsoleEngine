#pragma once

#include "Actor/Actor.h"
#include "Player.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class PlayerAttack : public Actor
{
	RTTI_DECLARATIONS(PlayerAttack, Actor);
public :
	PlayerAttack(const Vector2& position, Player* player);
	~PlayerAttack();
	
	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;

	const char* frames[5] = { "/", "|", "-" ,"\\", "-"}; // 사용할 이미지 순서


private :
	bool rightAttack;

	float moveSpeed = 50.0f;
	float xPosition = 0.0f;

	EngineTimer timer{ 0.1f };
	
	int currentFrameIndex = 0;                  // 현재 몇 번째 이미지인지

};

