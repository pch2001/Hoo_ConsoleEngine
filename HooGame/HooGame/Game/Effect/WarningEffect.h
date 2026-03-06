#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"

using namespace Wanted;


class WarningEffect : public Actor
{
	RTTI_DECLARATIONS(WarningEffect, Actor)

public :
	WarningEffect();
	~WarningEffect();

	virtual void Tick(float DeltaTime) override;
	virtual void Draw() override;

private :
	EngineTimer endTime;
	EngineTimer clickerTimer;

};

