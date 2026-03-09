#include "Cheongung2.h"
#include "Level/BossLevel.h"
#include "Navigation/Astar.h"
#include "Effect/guidedMissile.h"
#include "Effect/ExplosionEffect.h"

Cheongung2::Cheongung2(const Vector2& position) : super("C", position, Color::Red, false)
{
	sortingOrder = 10;
	myLayer = CollisionLayer::PlayerAttack;
	targetLayer = CollisionLayer::Enemy;

}


Cheongung2::~Cheongung2()
{
	
}

void Cheongung2::Shotdown()
{

	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (!currentLevel) return;

	BPlayer* player = currentLevel->GetBPlayerActor();
	if (!player) return;

	enemymisilelists = currentLevel->activeMissiles;

	if (enemymisilelists.empty())
		return;


	guidedMissile* target = enemymisilelists[0];
	if (target == nullptr || target->DestroyRequested())
		return;

	startNode = new Node(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y));
	endNode = new Node(static_cast<int>(target->GetPosition().x), static_cast<int>(target->GetPosition().y));

	Astar astar;
	std::vector<Node*> path;

	path = astar.FindPath(startNode, endNode, currentLevel->GetNavigationGrid(), currentLevel->pathLine);

	if (path.empty())
		return;

	Node* nextPosition = path[0];
	if (path.size() > 1)
		nextPosition = path[1];

	position.x = (float)nextPosition->position.x;
	position.y = (float)nextPosition->position.y;

}

void Cheongung2::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	delay.Tick(deltaTime);
	if (delay.IsTimeOut())
	{
		Shotdown();
		delay.Reset();

	}

}

void Cheongung2::Draw()
{
	super::Draw();

}

void Cheongung2::OnOverlap(Actor* actor)
{
	BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (!level) return;

	if (actor->IsTypeOf<guidedMissile>())
	{
		level->AddNewActor(new ExplosionEffect(actor->GetPosition(), 10));
		actor->Destroy();
		this->Destroy();

	}

}
