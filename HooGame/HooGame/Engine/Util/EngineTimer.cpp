#include "EngineTimer.h"


namespace Wanted
{
	EngineTimer::EngineTimer(float targetTime) : targetTime(targetTime)
	{
	}

	void EngineTimer::Tick(float deltaTime)
	{
		// 경과 시간 업데이트.
		elapsedTime += deltaTime;
	}

	void EngineTimer::Reset()
	{
		elapsedTime = 0.0f;
	}

	bool EngineTimer::IsTimeOut() const
	{
		return elapsedTime >= targetTime;
	}

	void EngineTimer::SetTargetTime(float newTargetTime)
	{
		targetTime = newTargetTime;
	}


}