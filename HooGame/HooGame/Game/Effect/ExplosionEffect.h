#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"
#include "Math/Color.h" 

using namespace Wanted;


class ExplosionEffect : public Actor
{
	RTTI_DECLARATIONS(ExplosionEffect, Actor)

public:
	ExplosionEffect(const Vector2& position ,int power, Color color);
	~ExplosionEffect();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnOverlap(Actor* actor) override;
	
	int SetChangeColortoBackGroundColor(Color color);
	void CheckIsVailed (Vector2 checkPosition);




private :
	Color EffectColor;
	bool firstattack = false;

	int power;
	int currentpower =0;

	EngineTimer delaytimer{0.005f};
	EngineTimer dietimer{ 1 };
};

