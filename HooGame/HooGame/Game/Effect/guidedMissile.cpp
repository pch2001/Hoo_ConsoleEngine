#include "guidedMissile.h"
#include "Navigation/Node.h"
#include "Navigation/Astar.h"
#include "Level/BossLevel.h"
#include "Engine/Engine.h"

#include "Render/Renderer.h"
#include "Actor/BPlayer.h"

guidedMissile::guidedMissile(Vector2 position, Actor* enemytActor) : super("O", position), Enemyactor(enemytActor)
{
	sortingOrder = 14;
	Guide();
}

guidedMissile::~guidedMissile()
{
}

void guidedMissile::Guide()
{

	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (!currentLevel) return;

	BPlayer* player = currentLevel->GetBPlayerActor();
	if (!player) return;
	
	Node* startNode = new Node(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y));
	Node* endNode = new Node(static_cast<int>(player->GetPosition().x), static_cast<int>(player->GetPosition().y));

	Astar astar;
	auto path = astar.FindPath(startNode, endNode, currentLevel->GetNavigationGrid());
}

void guidedMissile::Tick(float deltaTime)
{
}

void guidedMissile::Draw()
{
	super::Draw(); // 상위 클래스 그리기 호출
	Renderer::Get().Submit("0", Vector2(position), Color::Green);
}
