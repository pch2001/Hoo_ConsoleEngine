#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet, Actor)
public :
	PlayerBullet(const Vector2& position);
	~PlayerBullet();

	//반복적인 호출이 필요 -> Tick 가져오기
	virtual void Tick(float deltaTime) override;

private:
	
	//이동속도 초당 몇칸 이동하는지를 나타냄
	float moveSpeed = 30.0f;

	// 위치 갱신을 할 때 소수점처리를 위한 변수.
	float yPosition = 0.0f;

};

