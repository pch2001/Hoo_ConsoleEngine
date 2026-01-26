#include "TestActor.h"
#include <iostream>


void TestActor::BeginPlay()
{
	// override라 상위 함수 호출
	// C++는 부모 함수 가리키는 포인터가 없어 타입으로 가리켜야함
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void TestActor::Tick(float deltaTime)
{
	//std::cout<< "TestActor::Tick(). deltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << "\n";
}

void TestActor::Draw()
{
	Actor::Draw();
}
