#include <iostream>
#include "Engine/Engine.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"

using namespace Wanted;

int main()
{
	Game game;
	game.Run();


	/*Wanted::Engine engine;
	engine.SetNewLevel(new SokobanLevel());
	engine.Run();*/

	/*
	TestLevel* level = new TestLevel();
	//Actor* actor = new Actor();

	//TestActor* testActor = actor->As<TestActor>();
	Actor* actor = new TestActor();
	TestActor* testActor = new TestActor();

	TestActor* test2 = actor->As<TestActor>();
	if (test2) {
		std::cout << "actor is TestActor Type\n";
	}
	else {
		std::cout << "actor is not TestAtor Type\n";
	}

	if (testActor) {
		std::cout << "actor is TestActor type.\n";
	}
	else {
		std::cout << "actor is not TestActor type.\n";
	}*/ // RTTI
}
