#include "EndLevel.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <iostream>1


EndLevel::EndLevel()
{
	items.emplace_back(new MenuItem("Retry Game", []() { Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitEngine(); }));
}

EndLevel::~EndLevel()
{
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
