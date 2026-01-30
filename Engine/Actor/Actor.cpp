#include "Actor.h"
#include <iostream>
#include <Windows.h>
#include <Util/Util.h>

namespace Wanted
{
	Actor::Actor(const char image, const Vector2& position) : image(image), position(position)
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::BeginPlay()
	{
		// 이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::Draw()
	{
		Util::SetConsolePosition(position);
		//이동한 좌표에서 글자 그리기
		std::cout << image;

	}
	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 액터의 좌표로 콘솔 좌표 위치 이동
		Util::SetConsolePosition(position);

		// 해당 위치의 글자 값 지우기 (빈칸 그리기)
		std::cout << ' ';

		// 새로운 위치 설정
		position = newPosition;
	}
}