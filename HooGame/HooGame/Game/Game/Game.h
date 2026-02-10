#pragma once

#include "Engine/Engine.h"
#include <vector>

using namespace Wanted;

enum class State
{
	GamePlay = 0,
	Menu = 1,
	End = 2,
	Length
};


class Game:public Engine
{
public :
	Game();
	~Game();
	
	void ToggleMenu();
	void EndGame();
	void RestartGame();
	static Game& Get();


	int GetScore() { return score; }
	void SetScore(int i) { score = i; }

private :

	std::vector<Level*> levels;
	State state = State::GamePlay;

	int score = 0;

	static Game* instance;

};

