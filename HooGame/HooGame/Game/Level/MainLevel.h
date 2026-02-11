#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Level/BaseMenuLevel.h"
#include <vector>


using namespace Wanted;

struct MapChar
{
	std::string character;
	Vector2 pos;
};
struct MapChar2
{
	const char* character;
	Vector2 pos;
};

class MainLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(MainLevel, BaseMenuLevel)

public :
	MainLevel();
	~MainLevel();

	virtual void Draw() override;

	void LoadMap(const char* image);
	void LoadLine();

	std::vector<MapChar> mapData;
	std::vector<MapChar2> mapData2;

};

