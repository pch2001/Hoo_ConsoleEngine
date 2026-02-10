#pragma once

#include "Common/Common.h"
#include "Util/EngineTimer.h"
#include "Actor/Actor.h"

#include <vector>

namespace Wanted
{
	class Actor;
	class Engine;
	
	class WANTED_API Physics
	{
	public :

		Physics(Engine* engine);
		~Physics();

		void StartGravity(Actor* actor);
		// 충돌 시 각자 분류해서 알려줌
		void ProcessCollision(const std::vector<Actor*>& actors);

		bool IsOnGround(Actor* actor, const std::vector<Actor*>& actors);

		void BeginPlay();
		void Tick(float deltaTime);
		void ClearActors() { gravityActors.clear(); }
	
	private:
		std::vector<Actor*> gravityActors;
		Engine* ownerEngine; // 엔진 주소를 직접 보관
		EngineTimer timer{ 0.1f };

	};
}


