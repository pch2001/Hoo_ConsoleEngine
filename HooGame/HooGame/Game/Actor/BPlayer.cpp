#include "BPlayer.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Engine/Engine.h"

#include<iostream>
BPlayer::BPlayer() : super("P", Vector2::Zero, Color::White)
{
	sortingOrder = 10;
	myLayer = CollisionLayer::Player;
	targetLayer = CollisionLayer::None;
}

BPlayer::~BPlayer()
{
}

void BPlayer::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKey(VK_UP) || Input::Get().GetKey('W') || Input::Get().GetKey('w')) Move(0, -1);
	if (Input::Get().GetKey(VK_DOWN) || Input::Get().GetKey('S') || Input::Get().GetKey('s')) Move(0, 1);
	if (Input::Get().GetKey(VK_LEFT) || Input::Get().GetKey('A') || Input::Get().GetKey('a')) Move(-1, 0);
	if (Input::Get().GetKey(VK_RIGHT) || Input::Get().GetKey('D') || Input::Get().GetKey('d')) Move(1, 0);
}

void BPlayer::Move(int x, int y)
{
	position.x += x;
	position.y += y;

	Vector2 nextPos = position;
	nextPos.x = Util::Clamp<int>((int)nextPos.x, 0, Engine::Get().GetWidth() - 1);
	nextPos.y = Util::Clamp<int>((int)nextPos.y, 0, Engine::Get().GetHeight() - 1);
	this->SetPosition(nextPos);
}
