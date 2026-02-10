#include "Coin.h"
#include "Player.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"

Coin::Coin(const Vector2& position) : super("C", position, Color::YELLOW)
{
	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::Player;
}

Coin::~Coin()
{
}

void Coin::Tick(float deltaTime)
{
	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		currentFrameIndex = (currentFrameIndex + 1) % 3;

		// 2. 바뀐 인덱스의 이미지로 변경
		ChangeImage(frames[currentFrameIndex]);
		timer.Reset();
	}
}

void Coin::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<Player>())
	{
		Level* currentLevel = Game::Get().GetMainLevel();

		GameLevel* gameLevel = static_cast<GameLevel*>(currentLevel);
		if (gameLevel)
		{
			gameLevel->PlusScore();
		}

		this->Destroy();
	}
}

