#include "Store.h"
#include "Render/Renderer.h"
#include "Game/Game.h"
#include <functional>
#include <iostream>

Store::Store()
{
	mapData = LoadLineDraw();

	items.emplace_back(new MenuItem("Back Lobby", []() { Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Buy MaxHP", []() { Game::Get().BuyMaxHP(); }));
	items.emplace_back(new MenuItem("Buy Speed", []() { Game::Get().BuyMaxSpeed(); }));
	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitEngine(); }));
	
}
Store::~Store()
{
}

void Store::Draw()
{
	int cameraX = Renderer::Get().GetCameraPosition().x;
	moneyInt = std::to_string(Game::Get().GetMoney()).c_str();
	Renderer::Get().Submit(moneyText.c_str(), Vector2(3, 3), Color::Red);
	Renderer::Get().Submit(moneyInt.c_str(), Vector2(3 + moneyText.size(), 3), Color::Red);



	for (const auto& item : mapData) {
		Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraX, item.pos.y), Color::Red);
	}
	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;

		if (ix == 1)
		{
			price1Level = std::to_string(Game::Get().GetMaxHPLevel());
			Renderer::Get().Submit(price1Level.c_str(), Vector2(2, Engine::Get().GetHeight() / 2 + ix * 2), textColor);

			Renderer::Get().Submit(price1Text.c_str(), Vector2(4, Engine::Get().GetHeight() / 2 + ix * 2), textColor);
			
			price1Int = std::to_string(Game::Get().GetMaxHP() * 2).c_str();
			Renderer::Get().Submit(price1Int.c_str(), Vector2(4 + price1Text.size(), Engine::Get().GetHeight() / 2 + ix * 2), textColor);
		}
		if (ix == 2)
		{
			price2Level = std::to_string(Game::Get().GetMaxSpeedLevel());
			Renderer::Get().Submit(price2Level.c_str(), Vector2(2, Engine::Get().GetHeight() / 2 + ix * 2), textColor);

			Renderer::Get().Submit(price2Text.c_str(), Vector2(4 , Engine::Get().GetHeight() / 2 + ix * 2), textColor);
			
			price2Int = std::to_string(Game::Get().GetMaxSpeedLevel() * 20).c_str();
			Renderer::Get().Submit(price2Int.c_str(), Vector2(4+ price2Text.size(), Engine::Get().GetHeight() / 2 + ix * 2), textColor);
		}
		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 2 + cameraX - strlen(items[ix]->text)
			, Engine::Get().GetHeight() / 2 + ix * 2), textColor);
	}
}