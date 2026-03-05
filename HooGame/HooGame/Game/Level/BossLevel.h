#pragma once
#include "Level/Level.h"
#include "BaseMenuLevel.h"
#include "Engine/Engine.h"
using namespace Wanted;

struct MapChar5
{
	std::string character;
	Vector2 pos;
};
class BPlayer;

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


	BPlayer* GetBPlayerActor() { return player; }
	std::vector<std::vector<int>>& GetNavigationGrid() { return navigationGrid; }

private :
	BPlayer* player = nullptr;
	std::vector<MapChar5> mapData;
	std::vector<MapChar5> backgroundData;

	std::vector<std::vector<int>> navigationGrid;

	const int width = Engine::Get().GetWidth();
	const int height = Engine::Get().GetHeight();
};

