#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class DeathLine : public Actor
{
	RTTI_DECLARATIONS(DeathLine, Actor);
public:
	DeathLine(const Vector2& position);
	~DeathLine();

private:

};

