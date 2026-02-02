#pragma once

#include "Actor/Actor.h"
//#include "Math/Vector2.h"

using namespace Wanted;

class Player : public Wanted::Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public :

		Player(const Vector2& position);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
