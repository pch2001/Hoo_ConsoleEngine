#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class Player : public Actor
{

	// 발사 모드.
	enum class EFireMode
	{
		None = -1,
		OneShot,
		Repeat
	};


	RTTI_DECLARATIONS(Player, Actor);
public :
	Player();

	~Player();

	virtual void Tick(float deltaTime) override;

private :
	//오른쪽으로 이동하는 함수
	void MoveRight();

	//왼쪽으로 이동하는 함수
	void MoveLeft();

	//탄약 발사 함수
	void Fire();

	//연속 발사 함수
	void FireInterval();

	//발사 가능여부 확인 함수.
	bool CanShoot() const;

private :
	//발사모드 
	EFireMode fireMode = EFireMode::None;

	//타이머 변수.
	Timer timer;

	//경과 시간 
	//float elapsedTime = 0.0f;

	//연사 시간 간격
	//float fireInterval = 0.2f;

};