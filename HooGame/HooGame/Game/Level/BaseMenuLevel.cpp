#include "BaseMenuLevel.h"
#include "Core/Input.h"


BaseMenuLevel::BaseMenuLevel()
{
	currentIndex = 0;
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
