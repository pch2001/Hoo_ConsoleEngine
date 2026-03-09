#include "BossLevel.h"
#include "Actor/BPlayer.h"
#include "Actor/Item.h"
#include "Actor/Ground.h"
#include "Actor/BossEnemy.h"
#include "Actor/Hyeonmu5.h"
#include "Actor/Cheongung2.h"

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
	boss = new BossEnemy();
	AddNewActor(boss);
	LoadLine();

	mine1 = new Mine(Vector2(3, height - 3));
	mine2 = new Mine(Vector2(width - 3, 5));
	AddNewActor(mine1);
	AddNewActor(mine2);
}
BossLevel::~BossLevel()
{
	if (player) delete player;
	if (mine1) delete mine1;
	if (mine2) delete mine2;

}
void BossLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	

	if (Input::Get().GetMouseButtonDown(1) || Input::Get().GetMouseButtonDown(0))
		SpawnItem();

	if (Input::Get().GetKeyDown(VK_ESCAPE)) { Game::Get().ToggleMenu();	return; }
	if (Input::Get().GetKeyDown(VK_TAB)) { pathLine = !pathLine; }

	Stageing(deltaTime);
}

void BossLevel::Draw()
{
	super::Draw();
	StageUIUpdate();
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

void BossLevel::SpawnItem()
{

	Vector2 cameraPos = Renderer::Get().GetCameraPosition();
	Vector2 mousePos = Input::Get().MousePosition();
	int gridX = static_cast<int>(mousePos.x + 0.5f);
	int gridY = static_cast<int>(mousePos.y + 0.5f);


	Vector2 tempos = (Vector2((float)gridX + cameraPos.x, (float)gridY + cameraPos.y));
	Actor* tempCheongung = GetActorAt<Cheongung2>(tempos);
	if (tempCheongung)
		return;

	if (Input::Get().GetMouseButtonDown(1) && player->GetPoint() >= 5)
	{
		player->SetPoint(-5);
		Actor* tempactor = GetActorAt<Hyeonmu5>(tempos);

		if (tempactor)
		{
			tempactor->Destroy();
			AddNewActor(new Cheongung2(tempos));
		}
		else
		{
			AddNewActor(new Hyeonmu5(tempos));
		}
	}
	if (Input::Get().GetMouseButtonDown(0) && player->GetPoint() > 0)
	{
		AddNewActor(new Ground(tempos));
		navigationGrid[gridY][gridX] = 1;
		player->SetPoint(-1);
		player->UIUpdate();
	}

}

void BossLevel::StageUIUpdate()
{
	Vector2 cameraPos = Renderer::Get().GetCameraPosition();


	for (const auto& item : mapData)
	{
		Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraPos.x, item.pos.y), Color::Red, 3);
	}
	for (const auto& item : backgroundData)
	{
		if (cameraPos.x > 0)
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x + cameraPos.x, item.pos.y + cameraPos.y), stateColor, 3);
		}
		else
		{
			Renderer::Get().Submit(item.character.c_str(), Vector2(item.pos.x, item.pos.y), stateColor, 3);
		}
	}
	

	Renderer::Get().Submit(stateText.c_str(), Vector2(1, 2), Color::White, 3);
	Renderer::Get().Submit(timeText.c_str(), Vector2(1, 3), Color::White, 10);
	Renderer::Get().Submit(boomText.c_str(), Vector2(1, 4), Color::White, 10);
	Renderer::Get().Submit(boomCount.c_str(), Vector2(1+ boomText.size(), 4), Color::White, 10);

	Renderer::Get().Submit(timeCount.c_str(), Vector2(1 + timeText.size() , 3), Color::White, 10);

}

void BossLevel::Stageing(float deltaTime)
{

	stateTime += deltaTime;

	const auto& config = stageSettings[currentState];

	float remaing = config.duration - stateTime;
	if (remaing < 0) remaing = 0;
	timeCount = std::to_string(stageSettings[currentState].duration - stateTime);

	if (stateTime >= config.duration)
	{
		EStageState nextState;
		if (currentState == EStageState::Farming) nextState = EStageState::maintenance;
		else if (currentState == EStageState::maintenance) nextState = EStageState::battle;
		else nextState = EStageState::Farming;

		SetState(nextState);

	}


	
}

void BossLevel::SetState(EStageState newState)
{
	stateTime = 0.0f;
	currentState = newState;;
	stateText = stageSettings[currentState].text;
	stateColor = stageSettings[currentState].bgColor;

	switch (currentState)
	{
	case EStageState::Farming:
		mine1->SetIsMineTime(true);
		mine2->SetIsMineTime(true);
		break;
	case EStageState::maintenance:
		
		boss->SetAttackCountUI(currentTurn);
		break;
	case EStageState::battle:
		mine1->SetIsMineTime(false);
		mine2->SetIsMineTime(false);
		boss->StartAttack();
		break;
	default:
		break;
	}

}


