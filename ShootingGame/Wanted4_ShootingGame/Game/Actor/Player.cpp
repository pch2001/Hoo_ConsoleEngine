#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/PlayerBullet.h"
#include "Level/Level.h"

Player::Player() : super("<<=A=>>", Vector2::Zero, Color::Green), fireMode(EFireMode::OneShot)
{
	// 생성 위치 설정
	int xPosition = (Engine::Get().GetWidth() / 2) - width ;
	int yPosition = (Engine::Get().GetHeight() - 2);
	SetPosition(Vector2(xPosition, yPosition));

	// 타이머 목표 시간 설정
	timer.SetTargetTime(0.2f);
}

Player::~Player()
{

}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//게임종료
		QuitGame();
	}

	// 경과 시간 업데이트
	//elapsedTime += deltaTime;
	timer.Tick(deltaTime);
	//좌우 방향키 입력처리
	if (Input::Get().GetKey(VK_LEFT))
	{
		MoveLeft();
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		MoveRight();
	}
	if (fireMode == EFireMode::OneShot)
	{
		if (Input::Get().GetKeyDown(VK_SPACE))
		{
			Fire();
		}
	}
	else if (fireMode == EFireMode::Repeat)
	{
		if (Input::Get().GetKey(VK_SPACE))
		{
			FireInterval();
		}
	}

	//발사 모드 전환
	if (Input::Get().GetKeyDown('R'))
	{
		int mode = static_cast<int>(fireMode);
		mode = 1 - mode;
		fireMode = static_cast<EFireMode>(mode);
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

void Player::Fire()
{
	// 경과 시간 초기화
	//elapsedTime = 0.0f;
	timer.Reset();

	// 위치 설정.
	Vector2 bulletPosition(position.x + (width / 2), position.y);

	// 액터 설정.
	GetOwner()->AddNewActor(new PlayerBullet(bulletPosition));

}

void Player::FireInterval()
{
	// 발사 가능 여부 확인
	if (!CanShoot())
	{
		return;
	}

	// 발사.
	Fire();

	// 

}


bool Player::CanShoot() const
{
	// 경과 시간 확인.
	// 발사 간격보다 더 많이 흘렀는지.

	return timer.IsTimeOut();
}
