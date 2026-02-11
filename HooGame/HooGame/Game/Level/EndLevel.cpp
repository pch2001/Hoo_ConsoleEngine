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
	LoadScene();
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
	for (const auto& item : mapData3) {
		Renderer::Get().Submit(item.character, item.pos, Color::Red);
	}

}

void EndLevel::LoadScene()
{
	const int width = Engine::Get().GetWidth();
	const int height = Engine::Get().GetHeight();

	// ┌───────────────┐ (top)
	for (int x = 0; x < width; ++x)
	{
		mapData3.push_back({ "_", Vector2((float)x, 0.f) });
	}

	// │               │ (middle)
	for (int y = 1; y < height - 1; ++y)
	{
		mapData3.push_back({ "|", Vector2(0.f, (float)y) });
		mapData3.push_back({ "|", Vector2((float)(width - 1), (float)y) });
	}

	// └───────────────┘ (bottom)
	for (int x = 0; x < width; ++x)
	{
		mapData3.push_back({ "-", Vector2((float)x, (float)(height - 1)) });
	}
}
