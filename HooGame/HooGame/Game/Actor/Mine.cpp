#include "Mine.h"
#include "Level/BossLevel.h"
#include "Engine/Engine.h"
#include "BPlayer.h"
#include "Core/Input.h"
#include "Math/Vector2.h"

Mine::Mine(const Vector2& position = Vector2::Zero) : super("M", position, Color::Brown,false)
{
	sortingOrder = 20;
	targetplayer = nullptr;
	myLayer = CollisionLayer::Ground;
	targetLayer = CollisionLayer::Player;
}

Mine::~Mine()
{
}

void Mine::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (isOnOverlap)
	{
		if (!targetplayer)
			return;
		if (Input::Get().GetKeyDown(VK_SPACE))
			targetplayer->SetPoint(1);
		EndOverlap(targetplayer);
	}
}

void Mine::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<BPlayer>())
	{
		ChangeImage("_");
		BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
		level->GetBPlayerActor()->SetisMine();
		targetplayer = level->GetBPlayerActor();
		isOnOverlap = true;
	}
	
}

void Mine::EndOverlap(Actor* actor)
{
	isOnOverlap = false;
	ChangeImage("M");
}

