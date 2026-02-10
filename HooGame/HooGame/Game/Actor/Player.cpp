#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Render/Renderer.h"
#include "Actor/PlayerAttack.h"
#include "Physics/Physics.h"
#include "Enemy.h"
#include "Game/Game.h"
#include "Effect/WhiteEffect.h"
#include "DeathLine.h"
#include "Coin.h"

#include <iostream>

Player::Player() : super("p", Vector2::Zero, Color::Green){

	sortingOrder = 10;
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = Engine::Get().GetHeight() - 2;
	groundY = yPosition;
	 
	SetPosition(Vector2(0, 0));

	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::None;

	auto* physics = Engine::Get().GetPhysics();

	if (physics != nullptr)
	{
		physics->StartGravity(this);
	}

}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_ESCAPE))	{Game::Get().ToggleMenu();	return;	}
	if (Input::Get().GetKey(VK_LEFT) || Input::Get().GetKey('A') || Input::Get().GetKey('a')){MoveLeft();}
	if (Input::Get().GetKey(VK_RIGHT) || Input::Get().GetKey('d') || Input::Get().GetKey('D')){	MoveRight();}

	timer.Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_SPACE) && !isJumping &&isOnGround)
	{
		isJumping = true;
		isOnGround = false;
		jumpStepsRemaining = 4; 
	}
	if (isJumping)
	{
		timer.Tick(deltaTime);

		if (timer.IsTimeOut())
		{
			position.y -= (int)1.0f; 
			jumpStepsRemaining--;
			timer.Reset();

			if (jumpStepsRemaining <= 0)
			{
				isJumping = false;
			}
		}
	}

	if (Input::Get().GetKeyDown('R') || Input::Get().GetKeyDown('r'))
	{
		Attack();
	}


	invincibleTimer.Tick(deltaTime);
	if (invincibleBool)
	{
		blinkTimer.Tick(deltaTime);

		if (blinkTimer.IsTimeOut())
		{
			color = (color == Color::White) ? Color::Black : Color::White;
			blinkTimer.Reset();
		}
	}
	if (invincibleTimer.IsTimeOut())
	{
		color = Color::Green;
		invincibleBool = false;
		invincibleTimer.Reset();
		blinkTimer.Reset();
	}

}

void Player::OnOverlap(Actor* actor)
{
	if (invincibleBool) return;

	if (actor->IsTypeOf<DeathLine>())
	{
		Game::Get().EndGame();
	}
	if (actor->IsTypeOf<Coin>())
	{
		return;
	}
	invincibleBool = true;
	if (actor->IsTypeOf<Enemy>() || actor->IsTypeOf<WhiteEffect>())
	{
		int knockbackDist;
		if (actor->IsTypeOf<WhiteEffect>())
		{

			WhiteEffect* effect = static_cast<WhiteEffect*>(actor);

			if (!effect->IsActuallyAttacking())
			{
				return;
			}
			knockbackDist = 10;
		}
		else
		{
			knockbackDist = 3;
		}
		Downgrade();

		Vector2 myPos = GetPosition();
		Vector2 targetPos = actor->GetPosition();

		int diffX = (int)myPos.x - (int)targetPos.x;

		int pushX = 0;
		if (diffX > 0) pushX = 2;
		else if (diffX < 0) pushX = -1;
		else
		{
			// 좌표가 완전히 겹쳤을 때(diffX == 0)
			// 플레이어가 오른쪽을 보고 있었다면 왼쪽(-1)으로, 왼쪽을 보고 있었다면 오른쪽(1)으로 밀기
			pushX = rightDirection ? -2 : 2;
		}

		Vector2 nextPos = {
			myPos.x + (pushX * knockbackDist),
			myPos.y - (1 * knockbackDist) // Y축은 일단 그대로 둡니다.
		};

		this->blinkTimer = 0.1f;
		this->SetPosition(nextPos);
	}
}


void Player::MoveRight()
{
	position.x += 1;
	rightDirection = true;
	if (position.x + width > Renderer::Get().GetCameraPosition().x + Engine::Get().GetWidth())
	{
		position.x -= 1;
	}
}

void Player::MoveLeft()
{
	rightDirection = false;

	position.x -= 1;

	if (position.x < 0)
	{
		position.x = 0;
	}
}


void Player::Attack()
{
	GetOwner()->AddNewActor(new PlayerAttack(position, this));
}

void Player::Upgrade()
{
	if (currentLevel < images.size()-1)
	{
		currentLevel++;
	}
	ChangeImage(images[currentLevel].c_str());
}


void Player::Downgrade()
{
	if (currentLevel > 0)
	{
		currentLevel--;
	}
	else if (currentLevel <= 0)
	{
		Game::Get().EndGame();

	}
	ChangeImage(images[currentLevel].c_str());
}
