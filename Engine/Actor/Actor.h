#pragma once

#include "Common/RTTI.h"

namespace Wanted
{
	class WANTED_API Actor : public RTTI
	{
		// RTTI 코드 추가
	friend class RTTI; protected: static const size_t TypeIdClass() {
		static int runTimeTypeId = 0; return reinterpret_cast<size_t>(&runTimeTypeId);
	} public: virtual const size_t& GetType() const override {
		return Actor::TypeIdClass();
	} using super = RTTI; virtual bool Is(const size_t id) const override {
		if (id == TypeIdClass()) {
			return true;
		}
		else {
			return RTTI::Is(id);
		}
	} virtual bool Is(RTTI* const rtti) const override {
		return Is(rtti->GetType());
	}

	public:
		Actor();
		virtual ~Actor();

		// 게임 플레이 이벤트.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// Getter.
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		bool IsActive() const
		{
			return isActive && !destroyRequested;
		}

	protected:
		// 이미 BeginPlay 이벤트를 받았는지 여부.
		bool hasBeganPlay = false;

		// 활성화 상태 여부.
		bool isActive = true;

		// 현재 프레임에 삭제 요청 받았는지 여부.
		bool destroyRequested = false;
	};
}
