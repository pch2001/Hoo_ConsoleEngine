#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class Player : public Actor
{
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
