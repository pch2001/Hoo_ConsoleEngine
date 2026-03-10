#include "EndLevel.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <iostream>
#include "BossLevel.h"


EndLevel::EndLevel()
{
	items.emplace_back(new MenuItem("Retry Game", []() { Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitEngine(); }));
	mapData = LoadLineDraw();
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

		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 3.5 *(ix+1) + cameraX, Engine::Get().GetHeight() / 2 ), textColor);

		Util::SetConsoleTextColor(textColor);
	}
	for (const auto& item : mapData) {
		Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraX, item.pos.y), Color::Red);
	}

}
