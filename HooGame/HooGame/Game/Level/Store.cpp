#include "Store.h"
#include "Render/Renderer.h"
#include "Game/Game.h"

Store::Store()
{
	mapData = LoadLineDraw();

	items.emplace_back(new MenuItem("Back Lobby", []() { Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitEngine(); }));

}
Store::~Store()
{
}

void Store::Draw()
{
	int cameraX = Renderer::Get().GetCameraPosition().x;

	for (const auto& item : mapData) {
		Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraX, item.pos.y), Color::Red);
	}
	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;


		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 2 + cameraX - strlen(items[ix]->text)
			, Engine::Get().GetHeight() / 2 + ix * 2), textColor);
	}
}

void Store::Tick(float deltaTime)
{

}
