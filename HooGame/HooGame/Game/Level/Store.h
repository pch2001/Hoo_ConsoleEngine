#pragma once

#include "BaseMenuLevel.h"

class Store : public BaseMenuLevel
{
	RTTI_DECLARATIONS(Store, BaseMenuLevel)

public :
	Store();
	~Store();

	virtual void Draw() override;
	virtual void Tick(float deltaTime) override;
	void LoadLine();

private :
	std::vector<MapCharTxt> mapData;

};

