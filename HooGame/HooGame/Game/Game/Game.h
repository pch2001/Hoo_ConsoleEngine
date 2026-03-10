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
class Game : public Engine
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

	void BuyMaxHP();
	void BuyMaxSpeed();


	void SetMoney(int money) { Money += money; }
	int GetMoney() { return Money; }
	int GetMaxHP() { return MaxHP; }
	float GetMaxSpeed() { return MaxSpeed; }
	int GetMaxSpeedLevel() { return MaxSpeedLevel; }
	int GetMaxHPLevel() { return MaxHPLevel; }

private :

	std::vector<Level*> levels;
	State state = State::GamePlay;

	int score = 0;

	static Game* instance;

	int MaxHP = 10;
	int MaxHPLevel = 1;


	float MaxSpeed = 0.98;
	int MaxSpeedLevel = 1;
	int SpeedPrice = 10;
	int Money = 100000;

};

