#include "Actor.h"

namespace Wanted {

	Actor::Actor()
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::BeginPlay()
	{
		//이벤트를 받은 후에는 플래그 설정
		hasBeganPlay = true;

	}
	void Actor::Tick(float deltaTIme) {
		//

	}
	void Actor::Draw() {
		//

	}
}