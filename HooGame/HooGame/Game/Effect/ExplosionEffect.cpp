#include "ExplosionEffect.h"
#include "Render/Renderer.h"

ExplosionEffect::ExplosionEffect(const Vector2& position, int power) : super(" ",position), power(power)
{
	sortingOrder = 20;
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::BoomEffect(int power)
{
	float radius = power / 2;
	Vector2 center = GetPosition();
	for (int y = -radius; y <= radius; ++y)
	{
		for (int x = -radius; x <= radius; ++x)
		{
			float temp = (x * x) + (y * y);
			if (temp <= (radius * radius))
			{
				int white = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
				Renderer::Get().Submit(" ", Vector2(center.x + x, center.y + y), Color::White, 20, white, true);
			}
		}
	}
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
	
	BoomEffect(currentpower);

}
