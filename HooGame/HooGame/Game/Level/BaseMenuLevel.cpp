#include "BaseMenuLevel.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

#include <iostream>
#include <string>
#include <vector>
BaseMenuLevel::BaseMenuLevel()
{
	currentIndex = 0;
	width = Engine::Get().GetWidth();
	height = Engine::Get().GetHeight();
	mapData.reserve((width + height) * 2);
}

BaseMenuLevel::~BaseMenuLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}
	items.clear();
}

void BaseMenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	int length = static_cast<int>(items.size());

	if (length==0)
		return;

	if (Input::Get().GetKeyDown(VK_RIGHT)|| Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_LEFT) || Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onselected();
	}
}

void BaseMenuLevel::Draw()
{


}

std::vector<MapCharTxt> BaseMenuLevel::LoadLineDraw()
{
	mapData.clear();



	if (width <= 0 || width > 500 || height <= 0 || height > 500) return mapData;

	// ┌───────────────┐ (top)
	for (int x = 0; x < width; ++x)
	{
		mapData.emplace_back( "_", Vector2((float)x, 0.f ));
	}

	// │               │ (middle)
	for (int y = 1; y < height - 1; ++y)
	{
		mapData.emplace_back( "|", Vector2(0.f, (float)y) );
		mapData.emplace_back( "|", Vector2((float)(width - 1), (float)y) );
	}

	// └───────────────┘ (bottom)
	for (int x = 0; x < width; ++x)
	{
		mapData.emplace_back( "-", Vector2((float)x, (float)(height - 1)));
		//mapData.emplace_back({ " ", Vector2((float)x, (float)(height - 1)) });
	}

	return mapData;
}

