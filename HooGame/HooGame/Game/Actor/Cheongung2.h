#pragma once

#include "Actor/Actor.h"
#include "Navigation/Node.h"
#include "Util/EngineTimer.h"
#include "Math/Color.h"
#include "Navigation/Astar.h"
#include <vector>
using namespace Wanted;
class guidedMissile;


class Cheongung2 : public Actor
{
	RTTI_DECLARATIONS(Cheongung2, Actor)

public :
	Cheongung2(const Vector2& position);
	~Cheongung2();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnOverlap(Actor* actor) override;

	void Shotdown();

	std::vector<guidedMissile*> enemymisilelists;


private :
	EngineTimer chagnedelay{ 0.1f };
	EngineTimer delay{ 0.05f };
	Astar astar;


	Node* startNode = nullptr;
	Node* endNode = nullptr;
	int colorcount = 0;
	Color colors[5] = { Color::Red, Color::Green, Color::Blue, Color::Brown, Color::White };

};

