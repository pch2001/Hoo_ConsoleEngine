#pragma once
#include "Level/Level.h"
#include "BaseMenuLevel.h"
using namespace Wanted;

struct MapChar5
{
	std::string character;
	Vector2 pos;
};

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


	
	std::vector<std::vector<int>>& GetNavigationGrid() { return navigationGrid; }

private :
	class BPlayer* player = nullptr;
	std::vector<MapChar5> mapData;
	std::vector<MapChar5> backgroundData;

	std::vector<std::vector<int>> navigationGrid;

};

