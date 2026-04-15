#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

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

struct MapCharTxt
{
	std::string character;
	Vector2 pos;

	MapCharTxt(const std::string& ch, const Vector2& p)
		: character(ch), pos(p) {
	}

	// 기본 생성자 (필요한 경우를 대비해 두는 것이 좋습니다)
	MapCharTxt() : character(""), pos(0.f, 0.f) {}
};

//===============================================================

class BaseMenuLevel : public Level
{

	RTTI_DECLARATIONS(BaseMenuLevel, Level)
public :
	BaseMenuLevel();
	~BaseMenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	void LoadLine();
	std::vector<MapCharTxt> LoadLineDraw();

protected :
	std::vector<MenuItem*> items;

	int currentIndex;

	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;
	std::vector<MapCharTxt> mapData;

};

