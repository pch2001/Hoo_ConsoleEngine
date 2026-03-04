#include "Effect.h"
#include "Level/Level.h"

#include "WhiteEffect.h"
#include "RedEffect.h"
#include "guidedMissile.h"

#include "Actor/Enemy.h"
#include "Actor/Enemy2.h"
#include "Actor/BossEnemy.h"

Effect::Effect(Vector2 position, Actor* actor, float effectTime) : rootPosition(position), effectTime(effectTime)
{
	effectTimer = effectTime;
	targetActor = actor;
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
		if (targetActor->IsTypeOf<Enemy>())
		{
			GetOwner()->AddNewActor(new WhiteEffect(rootPosition, targetActor));
		}
		else if (targetActor->IsTypeOf<Enemy2>())
		{
			GetOwner()->AddNewActor(new RedEffect());
		}
		else if (targetActor->IsTypeOf<BossEnemy>())
		{
			GetOwner()->AddNewActor(new guidedMissile(rootPosition, targetActor));
		}

		effectTimer.Reset();
		this->Destroy();
	}
}
