#pragma once

#include "BaseMenuLevel.h"

class Store : public BaseMenuLevel
{
	RTTI_DECLARATIONS(Store, BaseMenuLevel)

public :
	Store();
	~Store();

	virtual void Draw() override;
	void LoadLine();


private :
	std::vector<MapCharTxt> mapData;
	std::string moneyText = "Money : ";
	std::string moneyInt;

	std::string price1Level;
	std::string price1Text = "Level,  HP Upgrade Price : ";
	std::string price1Int;
	
	std::string price2Level;
	std::string price2Text = "Level,  Speed Upgrade Price : "; 
	std::string price2Int;

};

