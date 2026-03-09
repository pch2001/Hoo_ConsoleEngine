#include "Effect.h"
#include "Level/Level.h"
#include "Level/BossLevel.h"

#include "WhiteEffect.h"
#include "RedEffect.h"
#include "guidedMissile.h"

#include "Actor/Enemy.h"
#include "Actor/Enemy2.h"
#include "Actor/BossEnemy.h"

Effect::Effect(Vector2 position, Actor* actor, float effectTime) : rootPosition(position), effectTime(effectTime)
{
	effectTimer = effectTime;
	EnemyActor = actor;
}

Effect::~Effect()
{

}

void Effect::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	effectTimer.Tick(deltaTime);
	if (effectTimer.IsTimeOut())
	{
		if (EnemyActor->IsTypeOf<Enemy>())
		{
			GetOwner()->AddNewActor(new WhiteEffect(rootPosition, EnemyActor));
		}
		else if (EnemyActor->IsTypeOf<Enemy2>())
		{
			GetOwner()->AddNewActor(new RedEffect());
		}
		else if (EnemyActor->IsTypeOf<BossEnemy>())
		{
			BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
			level->AddMissile(new guidedMissile(SpawnDirection(0, 2), EnemyActor));
		}

		effectTimer.Reset();
		this->Destroy();
	}
}

Vector2 Effect::SpawnDirection(int x, int y)
{
	return Vector2(rootPosition.x + x, rootPosition.y + y);
}
