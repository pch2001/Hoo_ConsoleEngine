#pragma once
#include "Level/Level.h"
#include "BaseMenuLevel.h"
#include "Engine/Engine.h"

#include <map>

using namespace Wanted;

struct MapChar5
{
	std::string character;
	Vector2 pos;
};

enum class EStageState
{
	Farming,
	maintenance,
	battle,
};
struct StageConfig
{
	float duration;
	std::string text;
	Color bgColor;
};

class BPlayer;
class Mine;
class BossEnemy;
class guidedMissile;

class BossLevel : public Level
{
	RTTI_DECLARATIONS(BossLevel, Level)

public :
	BossLevel();
	~BossLevel();
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	void LoadScene();
	void LoadLine();

	void SpawnItem();
	void StageUIUpdate();

	void Stageing(float deltaTime);
	void SetState(EStageState newState);


	BPlayer* GetBPlayerActor() { return player; }
	std::vector<std::vector<int>>& GetNavigationGrid() { return navigationGrid; }
	BossEnemy* GetBossEnemy() { return boss; }
	bool pathLine = true;

	std::string boomCount = " 0";


	std::vector<guidedMissile*> activeMissiles;

	void UpdatemisileList();
	void AddMissile(guidedMissile* missile);

private :

	EStageState currentState = EStageState::Farming;
	float stateTime = 0.0f;
	int currentTurn = 1;

	BPlayer* player = nullptr;
	Mine* mine1 = nullptr;
	Mine* mine2 = nullptr;
	BossEnemy* boss = nullptr;

	std::vector<MapChar5> mapData;
	std::vector<MapChar5> backgroundData;

	std::vector<std::vector<int>> navigationGrid;

	const int width = Engine::Get().GetWidth();
	const int height = Engine::Get().GetHeight();

	std::string stateText = "no start ";
	std::string timeText = "time : ";
	std::string timeCount = " 0";
	std::string boomText = "Boom Time : ";
	Color stateColor = Color::White;

	std::map<EStageState, StageConfig> stageSettings =
	{
		{EStageState::Farming, { 1.0f, "Farm Time", Color::White }},
		{EStageState::maintenance, { 1.0f, "Maintenance Time", Color::Brown }},
		{EStageState::battle, { 20.0f, "Battle Time", Color::Red }},
	};
};

