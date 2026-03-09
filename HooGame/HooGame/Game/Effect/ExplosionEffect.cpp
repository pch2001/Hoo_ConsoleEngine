#include "ExplosionEffect.h"
#include "Render/Renderer.h"
#include "Actor/BPlayer.h"
#include "Actor/Ground.h"
#include "Level/BossLevel.h"
#include "WarningEffect.h"

ExplosionEffect::ExplosionEffect(const Vector2& position, int power) : super(" ",position), power(power)
{
	sortingOrder = 20;
	myLayer = CollisionLayer::EnemyAttack;
	targetLayer = CollisionLayer::Ground;
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	delaytimer.Tick(deltaTime);
	if (delaytimer.IsTimeOut())
	{
		if (currentpower < power)
		{
			currentpower++;

			float radius = currentpower / 2.0f;
			Vector2 center = GetPosition();
			for (int y = -radius; y <= radius; ++y) {
				for (int x = -radius; x <= radius; ++x) {
					if ((x * x) + (y * y) <= (radius * radius)) {
						CheckIsVailed(Vector2(center.x + x, center.y + y));
					}
				}
			}


			delaytimer.Reset();
		}
	}
	
	dietimer.Tick(deltaTime);
	if (dietimer.IsTimeOut())
		this->Destroy();
}

void ExplosionEffect::Draw()
{
	super::Draw();
	
	float radius = currentpower / 2.0f;
	Vector2 center = GetPosition();
	for (int y = -radius; y <= radius; ++y) {
		for (int x = -radius; x <= radius; ++x) {
			if ((x * x) + (y * y) <= (radius * radius)) {
				int white = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
				Renderer::Get().Submit(" ", Vector2(center.x + x, center.y + y), Color::White, 20, white, true);
			}
		}
	}
}

void ExplosionEffect::OnOverlap(Actor* actor)
{
	

}

void ExplosionEffect::CheckIsVailed(Vector2 checkPosition)
{
	

	BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (level)
	{
		for (Actor* actor : level->GetActors())
		{
			if (actor == this || actor->DestroyRequested())continue;

			if (actor->IsTypeOf<BPlayer>() || actor->IsTypeOf<Ground>())
			{
				if (actor->GetPosition() == checkPosition)
				{
					if (actor->IsTypeOf<Ground>())
					{
						actor->Destroy();

					}
					if (actor->IsTypeOf<BPlayer>())
					{
						if (firstattack)
							return;

						firstattack = true;

						BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
						if(level->GetBPlayerActor())
							level->GetBPlayerActor()->Damaged(-1);
						level->AddNewActor(new WarningEffect());
					}
				}
			}

		}
	}


}
