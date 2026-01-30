#pragma once
#include "Actor/Actor.h"


class Box : public  Wanted::Actor
{
	// RTTI µî·Ï
	RTTI_DECLARATIONS(Box, Actor)
public :
	Box(const Wanted::Vector2& newPosition);
};

