#include "BossEnemy.h"
#include "Engine/Engine.h"
#include "PlayerAttack.h"
#include "Effect/Effect.h"
#include "Level/BossLevel.h"


BossEnemy::BossEnemy() : super("B", Vector2(Engine::Get().GetWidth()/2, Engine::Get().GetHeight()/2 ), Color::Red)
{
	sortingOrder = 8;

	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;
}

BossEnemy::~BossEnemy()
{
}

#include "Core/Input.h"
#include "Game/Game.h"
#include "Render/Renderer.h"
void BossEnemy::Tick(float deltaTime)
{
	if (Input::Get().GetKey(VK_SPACE) || Input::Get().GetKey('p') || Input::Get().GetKey('P')) { 
		ChangeImage("K");
		MisileAttack(); 
	
	}


}

void BossEnemy::OnOverlap(Actor* actor)
{
}
void BossEnemy::MisileAttack()
{
	GetOwner()->AddNewActor(new Effect(this->GetPosition(), this, 1.f));
 	Vector2 effectPos = { position.x, position.y - 5 }; // 머리 
	Renderer::Get().Submit("!", effectPos, Color::Red);

}
