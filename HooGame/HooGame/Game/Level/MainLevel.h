#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <vector>


using namespace Wanted;

struct MapChar
{
	char character;
	Vector2 pos;
};

struct MenuItem
{

	using OnSelected = void (*) ();

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

class MainLevel : public Level
{
	RTTI_DECLARATIONS(MainLevel, Level)

public :
	MainLevel();
	~MainLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	//virtual void Overlap() override;

	void LoadMap(const char* filename);

private :

	int currentIndex = 0;
	Color selectedColor = Color::Green;

	Color unselectedColor = Color::White;

	std::vector<MenuItem*> items;

	std::vector<MapChar> mapData;
};

