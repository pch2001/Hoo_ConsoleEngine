#pragma once

#include "Actor/Actor.h"
#include "Actor/BPlayer.h"

using namespace Wanted;
class Mine : public Actor
{
	RTTI_DECLARATIONS(Mine, Actor)
public:
	Mine(const Vector2& position);
	~Mine();

	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;
	virtual void EndOverlap(Actor* actor) override;

	bool GetIsMineTime() const { return isMineTime; }
	void SetIsMineTime(bool statebool) 
	{ 
		isMineTime = statebool; 
		if (!statebool)
		{
			ChangeImage("X");
		}
		else
		{
			ChangeImage("M");
		}
	}

private :
	BPlayer* targetplayer;
	bool isMineTime = true;

};

