#include "WarningEffect.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"

WarningEffect::WarningEffect()
{
	int width = Engine::Get().GetWidth();
	int height = Engine::Get().GetHeight();

	for (int x = 0; x < width; x++)
	{
		if (x % 2 == 0)
		{
			Renderer::Get().Submit(" ", Vector2(x, 0), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, 1), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, 2), Color::White, 20, BACKGROUND_RED, true);

			Renderer::Get().Submit(" ", Vector2(x, height), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, height -1), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, height - 2), Color::White, 20, BACKGROUND_RED, true);
		}
		else
		{
			Renderer::Get().Submit(" ", Vector2(x, 0), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, 1), Color::White, 20, BACKGROUND_RED, true);

			Renderer::Get().Submit(" ", Vector2(x, height), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(x, height - 1), Color::White, 20, BACKGROUND_RED, true);
		}
	}
	for (int y = 0; y < height; y++)
	{
		if (y % 2 == 0)
		{
			Renderer::Get().Submit(" ", Vector2(0, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(1, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(2, y), Color::White, 20, BACKGROUND_RED, true);

			Renderer::Get().Submit(" ", Vector2(width, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(width-1, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(width - 2, y), Color::White, 20, BACKGROUND_RED, true);
		}
		else
		{
			Renderer::Get().Submit(" ", Vector2(0, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(1, y), Color::White, 20, BACKGROUND_RED, true);

			Renderer::Get().Submit(" ", Vector2(width, y), Color::White, 20, BACKGROUND_RED, true);
			Renderer::Get().Submit(" ", Vector2(width-1, y), Color::White, 20, BACKGROUND_RED, true);
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
