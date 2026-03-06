#include "PlayerAttack.h"
#include "Actor/Player.h"
#include "Enemy.h"
#include "Actor/BPlayer.h"

PlayerAttack::PlayerAttack(const Vector2& position, Player* player) : super("/",position, Color::White), rightAttack(player->IsRightDirection()), xPosition(static_cast<float>(player->GetPosition().x))
{
	sortingOrder = 10;

	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::Enemy;
	arriveTimer.Reset();
}


PlayerAttack::PlayerAttack(Vector2 dir, BPlayer* player) : super("/",player->GetPosition())
{
	sortingOrder = 10;

	direction = dir;
	Vector2 startPos = player->GetPosition() + dir;
	SetPosition(startPos);

	xPosition = startPos.x;
	yPosition = startPos.y;
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

	xPosition += direction.x * moveSpeed * deltaTime;
	yPosition += direction.y * moveSpeed * deltaTime;
	
	Vector2 newPosition = { xPosition, yPosition };

	// 위치 갱신
	SetPosition(newPosition);

	arriveTimer.Tick(deltaTime);

	if (arriveTimer.IsTimeOut())
	{
		Destroy();
	}
}

#include "Actor/Ground.h"
#include "Effect/guidedMissile.h"
#include "Actor/BossEnemy.h"
void PlayerAttack::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<Enemy>() || actor->IsTypeOf<Ground>() || actor->IsTypeOf<guidedMissile>() || actor->IsTypeOf<BossEnemy>())
	{
		Destroy();
	}

}
