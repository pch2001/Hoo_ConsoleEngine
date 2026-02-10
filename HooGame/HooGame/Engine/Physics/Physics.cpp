#include "Physics.h"
#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Engine/Engine.h"

#include <iostream>
using namespace Wanted;

Physics::Physics(Engine* ownerEngine) : ownerEngine(ownerEngine)
{
}

Physics::~Physics()
{
}

void Physics::StartGravity(Actor* actor)
{
    for (Actor* a : gravityActors)
    {
        if (a == actor)
            return;
    }
    gravityActors.emplace_back(actor);

}

void Physics::Tick(float deltaTime)
{
    timer.Tick(deltaTime);

    if (timer.IsTimeOut())
    {
        for (Actor* actor : gravityActors)
        {
            if (!actor->GetisJumping())
            {
                if (actor->myLayer == CollisionLayer::Ground)
                {
                    continue;
                }
                bool onGround = IsOnGround(actor, gravityActors);
                if (!onGround)
                {
                    Vector2 currentPos = actor->GetPosition();
                    int h = ownerEngine->GetHeight();
                    actor->SetPosition(Vector2(currentPos.x, currentPos.y + 1));
                }

            }
        }
        timer.Reset();
    }
}

void Physics::ProcessCollision(const std::vector<Actor*>& actors) {
    for (size_t i = 0; i < actors.size(); ++i) {
        for (size_t j = i + 1; j < actors.size(); ++j) {
            Actor* A = actors[i];
            Actor* B = actors[j];

            // 서로가 서로의 타겟 레이어에 포함되는지 확인
            if (A->targetLayer == B->myLayer || B->targetLayer == A->myLayer) {
                if (A->TestIntersect(B)) {
                    A->OnOverlap(B);
                    B->OnOverlap(A);
                }
            }
        }
    }
}

bool Wanted::Physics::IsOnGround(Actor* actor, const std::vector<Actor*>& actors)
{
    Vector2 originalPos = actor->GetPosition();

    Vector2 belowPos = { originalPos.x , originalPos.y + 1 };
    actor->SetPosition(belowPos);

    bool grounded = false;

    for (Actor* other : actors)
    {
        if (actor == other)
            continue;
        if (actor->TestIntersect(other))
        {
            grounded = true;
            actor->isOnGround = true;
            break;
        }
        else
        {
            actor->isOnGround = false;
        }
    }
    actor->SetPosition(originalPos);
    return grounded;
}

