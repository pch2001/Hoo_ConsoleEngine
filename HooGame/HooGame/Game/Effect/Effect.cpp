#include "Effect.h"
#include "Level/Level.h"
#include "WhiteEffect.h"
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
		GetOwner()->AddNewActor(new WhiteEffect(rootPosition, targetActor));
		effectTimer.Reset();

		this->Destroy();
	}
}
