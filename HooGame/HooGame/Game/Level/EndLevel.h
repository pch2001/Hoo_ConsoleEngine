#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include <vector>


using namespace Wanted;

struct MenuItem2



{

	using OnSelected = void (*) ();

	MenuItem2(const char* text, OnSelected onselected) : onselected(onselected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);

	}

	~MenuItem2()
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

class EndLevel : public Level
{
	RTTI_DECLARATIONS(EndLevel, Level)

public:
	EndLevel();
	~EndLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:

	int currentIndex = 0;
	Color selectedColor = Color::Green;

	Color unselectedColor = Color::White;

	std::vector<MenuItem2*> items;

};

