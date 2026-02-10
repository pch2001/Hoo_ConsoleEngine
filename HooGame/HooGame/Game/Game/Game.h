#pragma once

#include "Engine/Engine.h"
#include <vector>

using namespace Wanted;

enum class State
{
	Menu = 0,
	Select =1,
	GamePlay = 2,
	End = 3,
	Length
};


class Game:public Engine
{
public :
	Game();
	~Game();
	
	void ToggleMenu();
	void EndGame();
	void RestartGame(int level);
	static Game& Get();


	int GetScore() { return score; }
	void SetScore(int i) { score = i; }

private :

	std::vector<Level*> levels;
	State state = State::GamePlay;

	int score = 0;

	static Game* instance;

};

