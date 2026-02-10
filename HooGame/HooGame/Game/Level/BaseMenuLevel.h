#pragma once

#include "Level/Level.h"
#include "Math/Color.h"

#include <vector>
#include <iostream>
using namespace Wanted;

struct MenuItem
{
	using OnSelected = void(*)();

	MenuItem(const char* text, OnSelected onselected) : onselected(onselected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	char* text = nullptr;
	OnSelected onselected = nullptr;
};



class BaseMenuLevel : public Level
{
	RTTI_DECLARATIONS(BaseMenuLevel, Level)
public :
	BaseMenuLevel();
	~BaseMenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

protected :
	std::vector<MenuItem*> items;

private :

};

