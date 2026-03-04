#include "BossLevel.h"
#include "Actor/BPlayer.h"
#include "Actor/Item.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Game/Game.h"

BossLevel::BossLevel()
{
	player = new BPlayer();
	AddNewActor(player);
}
BossLevel::~BossLevel()
{

}
void BossLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetMouseButtonDown(0))
	{
		Vector2 pos = Input::Get().MousePosition();
		AddNewActor(new Item(pos));
	}
	if (Input::Get().GetKeyDown(VK_ESCAPE)) { Game::Get().ToggleMenu();	return; }


	int targetCameraX = player->GetPosition().x - (Engine::Get().GetWidth() / 2);
	if (targetCameraX < 0) targetCameraX = 0;

	Renderer::Get().SetCameraPosition({ static_cast<int>(targetCameraX), 0 });



}
void BossLevel::Draw()
{
	super::Draw();
}

void BossLevel::LoadScene()
{

}