#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class ExplosionEffect : public Actor
{
	RTTI_DECLARATIONS(ExplosionEffect, Actor)

public:
	ExplosionEffect(const Vector2& position ,int power);
	~ExplosionEffect();

	void BoomEffect(int power);
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
private :
	int power;
	int currentpower =0;

	EngineTimer delaytimer{0.005f};
	EngineTimer dietimer{ 1 };
};

