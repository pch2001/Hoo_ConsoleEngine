#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Navigation/Node.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class guidedMissile : public Actor
{
	RTTI_DECLARATIONS(guidedMissile, Actor)
public :
	guidedMissile(Vector2 position, Actor* targetActor);
	~guidedMissile();

	void Guide();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;


private :
	EngineTimer delay{ 0.02f };
	Actor* Enemyactor;

	Node* startNode = nullptr;
	Node* endNode = nullptr;

};

