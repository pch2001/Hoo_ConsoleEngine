#pragma once

#include <Actor/Actor.h>

using namespace Wanted;

class Item : public Actor
{
	RTTI_DECLARATIONS(Item, Actor);

public :
	Item(const Vector2& position);
	~Item();

	virtual void OnOverlap(Actor* actor) override;


private :

};

