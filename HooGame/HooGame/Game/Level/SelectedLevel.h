#pragma once
#include "BaseMenuLevel.h"

class SelectedLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(SelectedLevel, BaseMenuLevel)

public :
	SelectedLevel();
	~SelectedLevel();

	virtual void Draw() override;


private :


};

