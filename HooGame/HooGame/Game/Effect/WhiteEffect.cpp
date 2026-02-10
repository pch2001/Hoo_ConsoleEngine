#include "WhiteEffect.h"
#include "Render/Renderer.h"
#include "Actor/Enemy.h"

#include <iostream>
WhiteEffect::WhiteEffect(Vector2 position, Actor* actor) : super(" ",position), actor(actor), rootPosition(position)
{
    sortingOrder = 2;
    targetWidth = (actor != nullptr) ? actor->GetWidth() : 1;
    targetHeight = (actor != nullptr) ? actor->GetHeigth() : 1;

    this->position.x = rootPosition.x - 3;
    this->position.y = rootPosition.y - 1;

    this->width = (targetWidth * 3) + 4;
    this->height = targetHeight + 2;

    myLayer = CollisionLayer::Enemy;
    targetLayer = CollisionLayer::Player;

}

WhiteEffect::~WhiteEffect()
{
}

void WhiteEffect::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    elapsedTime += deltaTime;

    // 전체 지속 시간이 끝나면 삭제
    if (elapsedTime > (warningDuration + attackDuration+2.0f))
    {
        Enemy* enemy = static_cast<Enemy*>(actor);
        enemy->SetisAttacking(false);
        this->Destroy();
    }
}

void WhiteEffect::Draw()
{

    if (isWarning = (elapsedTime < warningDuration)) {
        icon = "*"; // 예고
    }
    else if (elapsedTime < warningDuration + 0.1f) {
        icon = " "; // 공격 직전 아주 잠깐 반짝이거나 비워둠 (플레이어 반응 시간)
    }
    else {
        icon = "X"; // 실제 공격
    }
    Color drawColor = isWarning ? Color::White : Color::Red;

    for (int ix = (int)position.x; ix < (int)position.x + width; ix++)
    {
        for (int iy = (int)position.y; iy < (int)position.y + height; iy++)
        {
            Vector2 drawPos = { ix, iy };
            Renderer::Get().Submit(icon, drawPos, drawColor);
        }
    }


}
