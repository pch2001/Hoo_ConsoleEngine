#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

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

	//인터페이스 확인
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	//dynamic_cast가 계속 프레임마다 호출하는건 좋지 않기 떄문에
	// canPlayerMoveInterface을 전역변수로 선언해서 데이터 영역에 한번만 공유하도록 선언
	// 이후에는 변환안함
	//오너십 확인(null확인)
	if (!canPlayerMoveInterface && GetOwner())
	{
		//인터페이스로 형변환 
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

	}

	//이동
	if (Wanted::Input::Get().GetKeyDown(VK_RIGHT) && GetPosition().x < 40) {
		//이동 가능 여부 판단
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if(canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		/*Wanted::Vector2 newPosition = GetPosition();
		newPosition.x += 1;
		SetPosition(newPosition);*/
	}
	if (Wanted::Input::Get().GetKeyDown(VK_LEFT) && GetPosition().x > 0) {
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		/*Wanted::Vector2 newPosition = GetPosition();
		newPosition.x -= 1;
		SetPosition(newPosition);*/
	}
	if (Wanted::Input::Get().GetKeyDown(VK_UP) && GetPosition().y > 0) {
		Vector2 newPosition(GetPosition().x, GetPosition().y-1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

	/*	Wanted::Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);*/
	}
	if (Wanted::Input::Get().GetKeyDown(VK_DOWN) && GetPosition().y < 20) {
		Vector2 newPosition(GetPosition().x, GetPosition().y+1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		/*Wanted::Vector2 newPosition = GetPosition();
		newPosition.y += 1;
		SetPosition(newPosition);*/
	}



	//std::cout 
	//	<< "TestActor::Tick(). deltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void Player::Draw()
{
	Actor::Draw();
}
