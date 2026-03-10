#include "ExplosionEffect.h"
#include "Render/Renderer.h"
#include "Actor/BPlayer.h"
#include "Actor/Ground.h"
#include "Level/BossLevel.h"
#include "WarningEffect.h"

ExplosionEffect::ExplosionEffect(const Vector2& position, int power, Color color) : super(" ",position), power(power)
{
	EffectColor = color;
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
/*
void Submit(
			const char* text,
			const Vector2& position,
			Color color = Color::White,
			int sortingOrder = 0,
			int bgColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			bool isbgimage = false
		);*/

void ExplosionEffect::Draw()
{
	super::Draw();
	
	float radius = currentpower / 2.0f;
	Vector2 center = GetPosition();
	for (int y = -radius; y <= radius; ++y) {
		for (int x = -radius; x <= radius; ++x) {
			if ((x * x) + (y * y) <= (radius * radius)) {
				Renderer::Get().Submit(" ", Vector2(center.x + x, center.y + y), Color::White, 20, SetChangeColortoBackGroundColor(EffectColor), true);
			}
		}
	}
}

void ExplosionEffect::OnOverlap(Actor* actor)
{
	

}

int ExplosionEffect::SetChangeColortoBackGroundColor(Color color)
{
	if (Color::White == color)
	{
		return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	}
	// 노란색: 빨간색 + 초록색 (R + G)
	else if (Color::YELLOW == color)
	{
		return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	}
	// 빨간색: 빨간색만 사용 (R)
	else if (Color::Red == color)
	{
		return BACKGROUND_RED | BACKGROUND_INTENSITY;
	}

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
