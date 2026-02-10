#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Level/BaseMenuLevel.h"
#include <vector>


using namespace Wanted;

struct MapChar
{
	char character;
	Vector2 pos;
};


class MainLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(MainLevel, BaseMenuLevel)

public :
	MainLevel();
	~MainLevel();

	virtual void Draw() override;

	//virtual void Overlap() override;

	//void LoadMap(const char* filename);

private :
	std::vector<MapChar> mapData;
};

