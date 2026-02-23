#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Ground.h"
#include "Actor/Cloud.h"
#include "Actor/Enemy.h"
#include "Actor/Item.h"
#include "Actor/DeathLine.h"
#include "Actor/Coin.h"

#include "Render/Renderer.h"
#include "Engine/Engine.h"
#include "Util/Util.h"

#include <iostream>

using namespace Wanted;

GameLevel::GameLevel(int level) : spawnRange(level)
{
	player = new Player();
	AddNewActor(player);
}


void GameLevel::PlusScore()
{
	score++;
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	int targetCameraX = player->GetPosition().x - (Engine::Get().GetWidth() / 2);
	if (targetCameraX < 0) targetCameraX = 0;

	// 렌더러에 카메라 위치 전달
	Renderer::Get().SetCameraPosition({ static_cast<int>(targetCameraX), 0 });
	UpdateMap();
	
	static char scoreBuffer[64];
	int currentScore = GetScore();
	sprintf_s(scoreBuffer, sizeof(scoreBuffer), "Score : %d", currentScore);

	
	Renderer::Get().Submit(scoreBuffer, Vector2(targetCameraX+ Engine::Get().GetWidth() / 2, 0), Color::White, 10);


	for (Actor* actor : actors)
	{
		if (actor == player) continue;

		if (actor->GetPosition().x*2 < targetCameraX)
		{
			if (actor->IsTypeOf<Cloud>() || actor->IsTypeOf<Ground>() || actor->IsTypeOf<DeathLine>())
				actor->Destroy();
		}
	}


}
 
void GameLevel::Draw()
{
	super::Draw();
}

void GameLevel::UpdateMap()
{
	// 마지막으로 생성된 땅의 위치를 추적하는 변수
	int playerX = player->GetPosition().x;
	int screenWidth = Engine::Get().GetWidth();

	int height = Wanted::Engine::Get().GetHeight();

	//플레이어가 끝에 다다르기 전에 미리 다음 땅을 생성
	if (lastSpawnX < playerX + screenWidth)
	{
		lastSpawnX++;

		AddNewActor(new DeathLine(Vector2(lastSpawnX, height-1)));

		int r = Util::Random(1, spawnRange);
		if (r < 20)
		{
			AddNewActor(new Ground(Vector2(lastSpawnX, height -2)));

			if (r% 10 == 0 || r%4 == 0)
			{
				AddNewActor(new Enemy(Vector2(lastSpawnX, height - 3)));

			}
			else if (r % 3 == 0)
			{
				AddNewActor(new Coin(Vector2(lastSpawnX, height - 4)));

			}
			if (r % 7 == 0)
			{
				AddNewActor(new Item(Vector2(lastSpawnX, height - 5)));
				//AddNewActor(new Cloud(Vector2(lastSpawnX, 7)));

			}
		}
		else if(r<70)
		{
			AddNewActor(new Ground(Vector2(lastSpawnX, height - 2)));
		}
		int minx = Util::Random(1, 4);
		int maxx = Util::Random(1, 7);
		for (int i = minx; i < maxx; i++)
		{
			AddNewActor(new Cloud(Vector2(lastSpawnX, i)));
		}
		
	}
}


void GameLevel::SpawnNextPattern(int index)
{
	int height = Wanted::Engine::Get().GetHeight();
	if (index <= 2)
	{
		for (int i = 0; i < 20; ++i) {
			AddNewActor(new Ground(Vector2(lastSpawnX + i, height - 1)));
			if (i % 8 == 0) 
				AddNewActor(new Cloud(Vector2(lastSpawnX + i, 3)));
		}
		for (int i = 0; i < 20; i += 5)
			AddNewActor(new Item(Vector2(lastSpawnX + i, height - 5)));
	}
	else if (index < 4)
	{
		for (int i = 0; i < 20; ++i) {
			AddNewActor(new Ground(Vector2(lastSpawnX + i, height - 1)));
			// 10번째 칸에 적 배치
			if (i == 10 || i == 5)
			{
				Vector2 v = Vector2(lastSpawnX + i, height - 3);
				AddNewActor(new Enemy(v));

			}
		}
	}
	else if (index < 7)
	{
		for (int i = 0; i < 20; ++i) {
			// 7~10칸 사이는 땅을 생성하지 않음 (낭떠러지)
			if (i < 7 || i > 10) {
				AddNewActor(new Ground(Vector2(lastSpawnX + i, height - 1)));
			}
			else {
				// 낭떠러지 구간 공중에 구름 발판 배치
				if (i % 2 ==0)
					AddNewActor(new Cloud(Vector2(lastSpawnX + i, (i%3+5) )));
			}
		}
	}
}




