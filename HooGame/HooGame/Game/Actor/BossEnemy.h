#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class BossEnemy : public Actor
{
	RTTI_DECLARATIONS(BossEnemy, Actor)

public :
	BossEnemy();
	~BossEnemy();

	void MisileAttack();

	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;

	void SetAttackCountUI(int boomcount);
	void StartAttack();
	
	void SetboomCount(int boomcount) { boomCount = boomcount; }
	int GetboomCount() const { return boomCount; }

private :
	EngineTimer attackTimer{ 0.3f };

	int boomCount = 0;

};

