#pragma once
#include "Level/Level.h"
#include "BaseMenuLevel.h"
using namespace Wanted;
class BossLevel : public Level
{

	RTTI_DECLARATIONS(BossLevel, Level)

public :
	BossLevel();
	~BossLevel();
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	void LoadScene();

private :
	class BPlayer* player = nullptr;
};

