#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "BaseMenuLevel.h"

#include <vector>


using namespace Wanted;

struct MapChar3
{
	const char* character;
	Vector2 pos;
};

class EndLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(EndLevel, BaseMenuLevel)

public:
	EndLevel();
	~EndLevel();
	virtual void Draw() override;

	void LoadScene();
private:

	std::vector<MapChar3> mapData3;


};

