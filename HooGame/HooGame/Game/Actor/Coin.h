#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"
using namespace Wanted;

class Coin : public Actor
{
	RTTI_DECLARATIONS(Coin, Actor)
public :
	Coin(const Vector2& position);
	~Coin();
	

	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;

	const char* frames[4] = { "(", "|", ")", "|"}; 

	EngineTimer timer{ 0.2f };

private :
	int  currentFrameIndex = 0;
};

