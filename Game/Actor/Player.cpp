#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include <iostream>
#include <Windows.h>


Player::Player(const Wanted::Vector2& position) : super('P', position, Wanted::Color::Red)
{
	//그릭 우선순위설정
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// 상위 함수 호출.
	// C++는 부모함수 가리키는 포인터가 없음.
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	// Q키 종료.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: 게임 엔진 종료 요청.
		Wanted::Engine::Get().QuitEngine();
	}

	// 스페이스로 박스 생성
	if (Wanted::Input::Get().GetKeyDown(VK_SPACE))
	{			
		// 박스 생성
		if (owner)
		{
			GetOwner()->AddNewActor(new Box(GetPosition()));

		}
	}

	//이동
	if (Wanted::Input::Get().GetKey(VK_RIGHT) && GetPosition().x < 40) {
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);
	}
	if (Wanted::Input::Get().GetKey(VK_LEFT) && GetPosition().x > 0) {
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);
	}
	if (Wanted::Input::Get().GetKey(VK_UP) && GetPosition().y > 0) {
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);
	}
	if (Wanted::Input::Get().GetKey(VK_DOWN) && GetPosition().y < 20) {
		Wanted::Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);
	}



	//std::cout 
	//	<< "TestActor::Tick(). deltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void Player::Draw()
{
	Actor::Draw();
}
