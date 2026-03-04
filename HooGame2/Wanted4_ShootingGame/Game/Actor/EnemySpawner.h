#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class EnemySpawner : public Actor
{
	RTTI_DECLARATIONS(EnemySpawner, Actor)

public:
	EnemySpawner();

private :

	virtual void Tick(float deltatime) override;

	void SpawnEnemy(float deltatime);

private:
	//생성 타이머
	Timer timer;

};

