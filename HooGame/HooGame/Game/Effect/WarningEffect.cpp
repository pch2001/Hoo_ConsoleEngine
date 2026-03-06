#include "WarningEffect.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"

WarningEffect::WarningEffect()
{
	int width = Engine::Get().GetWidth();
	int height = Engine::Get().GetHeight();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Renderer::Get().Submit(" ", Vector2(x, y), Color::White, 20, BACKGROUND_RED, true);
		}
	}

}

WarningEffect::~WarningEffect()
{

}



void WarningEffect::Tick(float DeltaTime)
{
	super::Tick(DeltaTime);
	endTime.Tick(DeltaTime);
	if (endTime.IsTimeOut())
	{
		this->Destroy();
	}

}

void WarningEffect::Draw()
{

}
