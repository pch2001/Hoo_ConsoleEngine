#include "SelectedLevel.h"
#include "GameLevel.h"
#include "Game/Game.h"
#include "Render/Renderer.h"
#include "MainLevel.h"
#include "Store.h"
#include "Util/Util.h"

SelectedLevel::SelectedLevel()
{
	items.emplace_back(new MenuItem("difficult 1", []() { Game::Get().RestartGame(100); }));
	items.emplace_back(new MenuItem("difficult 2", []() { Game::Get().RestartGame(150); }));
	items.emplace_back(new MenuItem("difficult 3", []() { Game::Get().RestartGame(200); }));
	items.emplace_back(new MenuItem("difficult 4", []() { Game::Get().RestartGame(300); }));
	items.emplace_back(new MenuItem("Boss", []() { Game::Get().BossGame(); }));
	items.emplace_back(new MenuItem("Store", []() {Game::Get().StoreEntry(); }));

	mapData = LoadLineDraw();
}

SelectedLevel::~SelectedLevel()
{

}

void SelectedLevel::Draw()
{
	int cameraX = Renderer::Get().GetCameraPosition().x;

	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 2.5f + cameraX, Engine::Get().GetHeight() / 3 + ix * 2), textColor);

		Util::SetConsoleTextColor(textColor);
	}
	for (const auto& item : mapData) {
		Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraX, item.pos.y), Color::Red);
	}
}