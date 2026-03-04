#pragma once
#include "BaseMenuLevel.h"
#include "Math/Vector2.h"
#include <vector>

class SelectedLevel : public BaseMenuLevel
{

	struct MapChar8
	{
		std::string character;
		Vector2 pos;
	};


	RTTI_DECLARATIONS(SelectedLevel, BaseMenuLevel)

public :
	SelectedLevel();
	~SelectedLevel();

	virtual void Draw() override;
	void LoadLine();


private :
	std::vector<MapChar8> mapData;

};

