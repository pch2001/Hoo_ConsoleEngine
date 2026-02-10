#include "EndLevel.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <iostream>1


EndLevel::EndLevel()
{
	items.emplace_back(new MenuItem2("Again Try", []() { Game::Get().RestartGame(); }));

	items.emplace_back(new MenuItem2("Quit Game", []() { Game::Get().QuitEngine(); }));

}

EndLevel::~EndLevel()
{
	
	for (MenuItem2*& item : items)
	{
		delete item;
		item = nullptr;
	}
	items.clear();
}

void EndLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	int length = static_cast<int>(items.size());
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		currentIndex = (currentIndex + 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onselected();
	}


}

void EndLevel::Draw()
{

	int cameraX = Renderer::Get().GetCameraPosition().x;

	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;



		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 4 *(ix+1) + cameraX, Engine::Get().GetHeight() / 2 ), textColor);

		Util::SetConsoleTextColor(textColor);
	}


}
