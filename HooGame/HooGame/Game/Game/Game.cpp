#include "Game.h"
#include "Level/MainLevel.h"
#include "Level/GameLevel.h"
#include "Level/EndLevel.h"
#include "Level/SelectedLevel.h"
#include "Level/BossLevel.h"
#include "Level/Store.h"
#include "Render/Renderer.h"

#include <iostream>

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	levels.emplace_back(new MainLevel());
	levels.emplace_back(new SelectedLevel());
	levels.emplace_back(new GameLevel());
	levels.emplace_back(new BossLevel());
	levels.emplace_back(new EndLevel());
	levels.emplace_back(new Store());

	state = State::Menu;

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
	state = State::Select;

	mainLevel = levels[static_cast<int>(State::Select)];
}



void Game::EndGame()
{
	state = State::End;

	mainLevel = levels[static_cast<int>(State::End)];
}

void Game::RestartGame(int level)
{
	auto* physics = Wanted::Engine::Get().GetPhysics();
	if (physics)
	{
		physics->ClearActors();
	}
	delete levels[static_cast<int>(State::GamePlay)];
	levels[static_cast<int>(State::GamePlay)] = new GameLevel(level);
	
	state = State::GamePlay;
	mainLevel = levels[static_cast<int>(State::GamePlay)];
}

void Game::BossGame()
{
	delete levels[static_cast<int>(State::Boss)];
	levels[static_cast<int>(State::Boss)] = new BossLevel();
	
	
	Renderer::Get().SetCameraPosition(Vector2(0,0));

	state = State::Boss;
	mainLevel = levels[static_cast<int>(State::Boss)];
}


Game& Game::Get()
{
	if (!instance)
	{
		__debugbreak();
	}

	return *instance;

}

void Game::StoreEntry()
{
	state = State::Store;
	Renderer::Get().SetCameraPosition(Vector2(0, 0));

	mainLevel = levels[static_cast<int>(State::Store)];
}

void Game::BuyMaxHP()
{

	if (Money >= MaxHP * 2 && MaxSpeedLevel < 5)
	{
		Money -= (MaxHP * 2);
		MaxHP++;
		MaxHPLevel++;
	}

}

void Game::BuyMaxSpeed()
{
	if (Money >= SpeedPrice * 2 && MaxSpeedLevel < 5)
	{
		Money -= (MaxSpeed * 20);
		MaxSpeed += 0.01;
		SpeedPrice++;
		MaxSpeedLevel++;
	}
}
