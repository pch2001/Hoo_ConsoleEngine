#include "BossLevel.h"
#include "Actor/BPlayer.h"
#include "Actor/Item.h"
#include "Actor/Ground.h"
#include "Actor/BossEnemy.h"
#include "Actor/Hyeonmu5.h"

#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Game/Game.h"
#include "Effect/Effect.h"
#include "Actor/Mine.h"
#include "Math/Vector2.h"

BossLevel::BossLevel()
{
	player = new BPlayer();
	AddNewActor(player);
	AddNewActor(new BossEnemy());
	LoadLine();

	AddNewActor(new Mine(Vector2(3, height - 3)));
	AddNewActor(new Mine(Vector2(width -3, 5)));
}
BossLevel::~BossLevel()
{

}
void BossLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	Vector2 cameraPos = Renderer::Get().GetCameraPosition();

	int cameraX = Renderer::Get().GetCameraPosition().x;
	int cameraY = Renderer::Get().GetCameraPosition().y;

	if (Input::Get().GetMouseButtonDown(1) || Input::Get().GetMouseButtonDown(0))
	{
		Vector2 mousePos = Input::Get().MousePosition();
		int gridX = static_cast<int>(mousePos.x + 0.5f);
		int gridY = static_cast<int>(mousePos.y + 0.5f);

		if (Input::Get().GetMouseButtonDown(1) && player->GetPoint() < 5)
		{
			player->SetPoint(-5);
			AddNewActor(new Hyeonmu5(Vector2((float)gridX + cameraX, (float)gridY + cameraY)));
		}
		else if (Input::Get().GetMouseButtonDown(0) || player->GetPoint() <= 0)
		{
			AddNewActor(new Ground(Vector2((float)gridX + cameraX, (float)gridY + cameraY)));
			navigationGrid[gridY][gridX] = 1;
			player->SetPoint(-1);
			player->UIUpdate();
		}
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE)) { Game::Get().ToggleMenu();	return; }
	if (Input::Get().GetKeyDown(VK_TAB)) { pathLine = !pathLine; }



	// Todo : 턴제 진행
	stateTimer -= deltaTime;

	switch (currentState)
	{
	case EStageState::Farming:


		break;
	case EStageState::maintenance:

		break;
	case EStageState::battle :

		break;
	default:
		break;
	}



}
void BossLevel::Draw()
{
	super::Draw();
	Vector2 cameraPos = Renderer::Get().GetCameraPosition();


	for (const auto& item : mapData)
	{
		Renderer::Get().Submit(item.character.c_str(),Vector2(item.pos.x + cameraPos.x, item.pos.y),Color::Red,3 );
	}
	for (const auto& item : backgroundData)
	{
		if (cameraPos.x > 0)
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x+ cameraPos.x, item.pos.y + cameraPos.y), Color::White, 3);
		}
		else
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x, item.pos.y), Color::White, 3);
		}
	}
}

void BossLevel::LoadScene()
{

}

void BossLevel::LoadLine()
{
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


