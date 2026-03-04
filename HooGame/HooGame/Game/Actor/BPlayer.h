#pragma once

#include "Actor/Actor.h"


using namespace Wanted;
class BPlayer : public Actor
{
	RTTI_DECLARATIONS(BPlayer, Actor)
public :
	BPlayer();
	~BPlayer();

	virtual void Tick(float deltaTime) override;

	void Move(int x, int y);
private :

};

