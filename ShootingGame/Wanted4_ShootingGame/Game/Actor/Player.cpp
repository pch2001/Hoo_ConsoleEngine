#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

Player::Player() : super("<<=A=>>", Vector2::Zero, Color::Green)
{

	// 생성 위치 설정
	int xPosition = (Engine::Get().GetWidth() / 2) - width ;
	int yPosition = (Engine::Get().GetHeight() - 2);
	SetPosition(Vector2(xPosition, yPosition));


}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//좌우 방향키 입력처리
	if (Input::Get().GetKey(VK_LEFT))
	{
		MoveLeft();
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		MoveRight();
	}

}

void Player::MoveRight()
{
	//오른쪽 이동 처리
	position.x += 1;

	//좌표 검사
	if (position.x + width > Engine::Get().GetWidth())
	{
		position.x -= 1;
	}
}

void Player::MoveLeft()
{
	//왼쪽 이동 처리
	position.x -= 1;

	//좌표 검사
	if (position.x < 0)
	{
		position.x = 0;
	}
}
