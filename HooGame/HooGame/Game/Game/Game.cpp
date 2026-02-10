#include "Game.h"
#include "Level/MainLevel.h"
#include "Level/GameLevel.h"
#include "Level/EndLevel.h"

#include <iostream>

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	levels.emplace_back(new MainLevel());
	levels.emplace_back(new GameLevel());
	levels.emplace_back(new EndLevel());

	state = State::GamePlay;

	mainLevel = levels[0];
}

Game::~Game()
{
	mainLevel = nullptr;
	for (Level*& level : levels)
	{
		delete level;
		level = nullptr;
	}
	levels.clear();
}

void Game::ToggleMenu()
{
	//system("cls");

	
	int stateIndex = (int)state;
	//int nextState = 1 - stateIndex;
	//state = (State)nextState;
	
	//state = State::Menu;

	if (stateIndex >= 2)
	{
		stateIndex = 1;
	}
	else
	{
		stateIndex = 1 - stateIndex;
	}

	state = static_cast<State>(stateIndex);
	mainLevel = levels[stateIndex];
}



void Game::EndGame()
{
	state = State::End;

	mainLevel = levels[2];
}

void Game::RestartGame()
{
	auto* physics = Wanted::Engine::Get().GetPhysics();
	if (physics)
	{
		physics->ClearActors();
	}
	delete levels[1];
	levels[1] = new GameLevel();
	
	state = State::GamePlay;
	mainLevel = levels[1];
}


Game& Game::Get()
{
	if (!instance)
	{
		__debugbreak();
	}

	return *instance;

}