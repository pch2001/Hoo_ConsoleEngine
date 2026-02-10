#include "PlayerAttack.h"
#include "Actor/Player.h"
#include "Enemy.h"

PlayerAttack::PlayerAttack(const Vector2& position, Player* player) : super("/",position, Color::White), rightAttack(player->IsRightDirection()), xPosition(static_cast<float>(player->GetPosition().x))
{
	sortingOrder = 1;

	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::Enemy;

}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer.Tick(deltaTime);

	if (timer.IsTimeOut())
	{
		currentFrameIndex = (currentFrameIndex + 1) % 3;

		// 2. 바뀐 인덱스의 이미지로 변경
		ChangeImage(frames[currentFrameIndex]);
		timer.Reset();
	}

	if (rightAttack)
	{
		xPosition += moveSpeed * deltaTime;
	}
	else
	{
		xPosition += -moveSpeed * deltaTime;
	}

	Vector2 newPosition = GetPosition();
	newPosition.x = static_cast<int>(xPosition);

	// 위치 갱신
	SetPosition(newPosition);


}

void PlayerAttack::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<Enemy>())
	{
		Destroy();
	}

}
