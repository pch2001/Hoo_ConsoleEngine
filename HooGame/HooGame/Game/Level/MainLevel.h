#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Level/BaseMenuLevel.h"
#include <vector>


using namespace Wanted;




class MainLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(MainLevel, BaseMenuLevel)

public :
	MainLevel();
	~MainLevel();

	virtual void Draw() override;

	void LoadMap(const char* image);

	std::vector<MapCharTxt> mapData2;
	std::vector<MapCharTxt> mapData;

};

