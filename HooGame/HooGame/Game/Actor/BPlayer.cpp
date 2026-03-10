#include "BPlayer.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Level/BossLevel.h"
#include "Game/Game.h"
#include "Effect/WarningEffect.h"
#include "Actor/PlayerAttack.h"


#include<iostream>
#include <string>
BPlayer::BPlayer() : super("P", Vector2(3,3), Color::White)
{
	gravity = false;
	sortingOrder = 10;
	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::None;
	HP = Game::Get().GetMaxHP();
	moveTimer = 1 - Game::Get().GetMaxSpeed();
	MaxHP = HP;
	UIUpdate();
}

BPlayer::~BPlayer()
{
}

void BPlayer::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	moveTimer.Tick(deltaTime);
	if (moveTimer.IsTimeOut())
	{
		if (Input::Get().GetKey(VK_UP) || Input::Get().GetKey('W') || Input::Get().GetKey('w')) Move(0, -1);
		if (Input::Get().GetKey(VK_DOWN) || Input::Get().GetKey('S') || Input::Get().GetKey('s')) Move(0, 1);
		if (Input::Get().GetKey(VK_LEFT) || Input::Get().GetKey('A') || Input::Get().GetKey('a')) Move(-1, 0);
		if (Input::Get().GetKey(VK_RIGHT) || Input::Get().GetKey('D') || Input::Get().GetKey('d')) Move(1, 0);
		moveTimer.Reset();
	}

	if (Input::Get().GetKeyDown(VK_CONTROL)) { GetOwner()->AddNewActor(new PlayerAttack(dir, this)); }

	
	UIUpdate();

}

void BPlayer::Move(int x, int y)
{
	float nextX = position.x + x;
	float nextY = position.y + y;

	dir = Vector2((float)x, (float)y);
	
	/*if (position.x <= 1 || position.y <= 1 || position.x >= Engine::Get().GetWidth()-1 || position. >= Engine::Get().GetHeight() + 1)
		return;*/

	if (nextX <= 1 || nextY <= 1 || nextX >= Engine::Get().GetWidth() - 1 || nextY >= Engine::Get().GetHeight() - 2)
	{
		return;
	}
	Vector2 nextPos = Vector2(nextX,nextY);
	

	/*nextPos.x = Util::Clamp<int>((int)nextPos.x, 2, Engine::Get().GetWidth() - 1);
	nextPos.y = Util::Clamp<int>((int)nextPos.y, 2, Engine::Get().GetHeight() +1);*/
	this->SetPosition(nextPos);
}

void BPlayer::Damaged(int x)
{
	BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	level->AddNewActor(new WarningEffect());

	Renderer::Get().StartShake(0.5f, 4);
	SetHP(x);
	if (GetHP() > 0)
	{
		UIUpdate();
	}
	else
		Die();

}

void BPlayer::Die()
{
	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());

	Game::Get().EndGame();
}

void BPlayer::UIUpdate()
{
	int Widgeth = Engine::Get().GetWidth();
	int Height = Engine::Get().GetHeight();

	float hpRatio = GetHP()/GetMaxHp();
	
	int currentBar = static_cast<int>(Widgeth * hpRatio);

	for (int i = 1; i < currentBar-1; i++)
	{
		Renderer::Get().Submit("*",Vector2(i, 1), Color::Green, 10);
	}
	

	static std::string str = "money : ";
	Renderer::Get().Submit(str.c_str(), Vector2(Widgeth / 2 - 8, 2), Color::White, 10);

	static std::string str2;
	str2 = std::to_string(GetPoint());
	Renderer::Get().Submit(str2.c_str(), Vector2(Widgeth / 2, 2), Color::White, 10);

}

void BPlayer::Attack(Vector2 dir)
{
	GetOwner()->AddNewActor(new PlayerAttack(dir, this));
}

