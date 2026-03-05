#include "BossLevel.h"
#include "Actor/BPlayer.h"
#include "Actor/Item.h"
#include "Actor/BossEnemy.h"

#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Game/Game.h"
#include "Effect/Effect.h"

BossLevel::BossLevel()
{
	player = new BPlayer();
	AddNewActor(player);
	AddNewActor(new BossEnemy());
	LoadLine();
}
BossLevel::~BossLevel()
{

}
void BossLevel::Tick(float deltaTime)
{

	int targetCameraX = player->GetPosition().x - (Engine::Get().GetWidth() / 2);
	int targetCameraY = player->GetPosition().y - (Engine::Get().GetHeight() / 2);

	int cameraX = Renderer::Get().GetCameraPosition().x;
	int cameraY = Renderer::Get().GetCameraPosition().y;

	super::Tick(deltaTime);
	if (Input::Get().GetMouseButtonDown(0))
	{
		Vector2 pos = Input::Get().MousePosition();
		AddNewActor(new Item(Vector2(pos.x + cameraX, pos.y + cameraY)));
	}
	if (Input::Get().GetKeyDown(VK_ESCAPE)) { Game::Get().ToggleMenu();	return; }


	
	//if (targetCameraX < 0) targetCameraX = 0;


	//Renderer::Get().SetCameraPosition({ static_cast<int>(targetCameraX), static_cast<int>(targetCameraY) });
}
void BossLevel::Draw()
{
	super::Draw();


	int targetCameraX = player->GetPosition().x - (Engine::Get().GetWidth() / 2);
	int targetCameraY = player->GetPosition().y - (Engine::Get().GetHeight() / 2);
	int cameraX = Renderer::Get().GetCameraPosition().x;
	int cameraY = Renderer::Get().GetCameraPosition().y;

	for (const auto& item : mapData)
	{
		Renderer::Get().Submit(item.character.c_str(),Vector2(item.pos.x +cameraX, item.pos.y),Color::Red);
	}
	for (const auto& item : backgroundData)
	{
		if (cameraX > 0)
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x+cameraX, item.pos.y + cameraY), Color::White);
		}
		else
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x, item.pos.y), Color::White);
		}
	}
}

void BossLevel::LoadScene()
{

}

void BossLevel::LoadLine()
{
	const int width = Engine::Get().GetWidth();
	const int height = Engine::Get().GetHeight();

	navigationGrid.assign(height, std::vector<int>(width, 0));

	for (int x = 0; x < width; ++x)
	{
		navigationGrid[0][x] = 1;
		mapData.push_back({ "_", Vector2((float)x, 0.f) });
		mapData.push_back({ "-", Vector2((float)x, (float)(height - 1)) });

	}
	for (int y = 1; y < height - 1; ++y)
	{
		navigationGrid[y][0] = 1; // Left wall
		navigationGrid[y][width - 1] = 1; // Right wall
		mapData.push_back({ "|", Vector2(0.f, (float)y) });
		mapData.push_back({ "|", Vector2((float)(width - 1), (float)y) });
	}


	for (int x = 1; x < width-1; ++x)
	{
		for (int y = 1; y < height-1; ++y)
		{
			navigationGrid[y][x] = 0;
			if ((x + y) % 2 == 0)
				backgroundData.push_back({".", Vector2((float)x, (float)y )});
		}
	}
}

