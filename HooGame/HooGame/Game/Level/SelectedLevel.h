#pragma once
#include "BaseMenuLevel.h"
#include "Math/Vector2.h"
#include <vector>

class SelectedLevel : public BaseMenuLevel
{


	RTTI_DECLARATIONS(SelectedLevel, BaseMenuLevel)

public :
	SelectedLevel();
	~SelectedLevel();

	virtual void Draw() override;

private :
	std::vector<MapCharTxt> mapData;

};

