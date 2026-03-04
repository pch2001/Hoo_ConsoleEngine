#include "guidedMissile.h"
#include "Navigation/Node.h"
#include "Navigation/Astar.h"
#include "Level/BossLevel.h"
#include "Engine/Engine.h"

guidedMissile::guidedMissile(Vector2 position, Actor* targetActor) : super("O", position), targetactor(targetActor)
{
	sortingOrder = 14;
}

guidedMissile::~guidedMissile()
{
}

void guidedMissile::Guide()
{

	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (!currentLevel) return;

	Node* startNode = new Node(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y));
	Node* goalNode = new Node(static_cast<int>(targetactor->GetPosition().x), static_cast<int>(targetactor->GetPosition().y));
	
	Astar astar;
	auto path = astar.FindPath(startNode, goalNode, currentLevel->GetNavigationGrid());
}

void guidedMissile::Tick(float deltaTime)
{
}

void guidedMissile::Draw()
{
}
