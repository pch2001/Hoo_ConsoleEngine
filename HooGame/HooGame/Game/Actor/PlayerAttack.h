#pragma once

#include "Actor/Actor.h"
#include "Player.h"
#include "Util/EngineTimer.h"
#include "BPlayer.h"

using namespace Wanted;

class PlayerAttack : public Actor
{
	RTTI_DECLARATIONS(PlayerAttack, Actor);
public :
	PlayerAttack(const Vector2& position, Player* player);
	PlayerAttack(Vector2 dir, BPlayer* player);
	~PlayerAttack();
	
	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;

	const char* frames[5] = { "/", "|", "-" ,"\\", "-"}; // 사용할 이미지 순서


private :

	Vector2 direction;

	bool rightAttack;

	float moveSpeed = 50.0f;
	int xPosition = 0.0f;
	int yPosition = 0.0f;

	EngineTimer timer{ 0.05f };

	EngineTimer arriveTimer{ 2.0f };
	
	int currentFrameIndex = 0;                  // 현재 몇 번째 이미지인지

};

