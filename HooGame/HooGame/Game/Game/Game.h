#pragma once

#include "Engine/Engine.h"
#include <vector>

using namespace Wanted;

enum class State
{
	Menu = 0,
	Select =1,
	GamePlay = 2,
	Boss = 3,
	End = 4,
	Store =5,
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
	void BossGame();
	static Game& Get();

	void StoreEntry();

	int GetScore() { return score; }
	void SetScore(int i) { score = i; }

private :

	std::vector<Level*> levels;
	State state = State::GamePlay;

	int score = 0;

	static Game* instance;

};

