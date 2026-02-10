#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "BaseMenuLevel.h"

#include <vector>


using namespace Wanted;

class EndLevel : public BaseMenuLevel
{
	RTTI_DECLARATIONS(EndLevel, BaseMenuLevel)

public:
	EndLevel();
	~EndLevel();
	virtual void Draw() override;

private:



};

