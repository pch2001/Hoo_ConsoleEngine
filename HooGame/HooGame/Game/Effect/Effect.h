#pragma once
#include "Actor/Actor.h"
#include "Util/EngineTimer.h"
#include "Math/Vector2.h"

using namespace Wanted;

class Effect : public Actor
{
	RTTI_DECLARATIONS(Effect, Actor)

	Effect(Vector2 position,Actor* actor ,float effectTime);
	~Effect();

	virtual void Tick(float deltaTime) override;

private :
	EngineTimer effectTimer;
	float effectTime;

	Vector2 rootPosition;
	
	int width = 0;
	int heigth = 0;

	Actor* targetActor;

};

