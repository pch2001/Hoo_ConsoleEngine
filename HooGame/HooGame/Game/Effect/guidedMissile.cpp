#include "guidedMissile.h"
#include "Navigation/Node.h"
#include "Navigation/Astar.h"
#include "Level/BossLevel.h"
#include "Engine/Engine.h"
#include "Effect/ExplosionEffect.h"
#include "Effect/WarningEffect.h"

#include "Render/Renderer.h"
#include "Actor/BPlayer.h"
#include "Actor/Hyeonmu5.h"

guidedMissile::guidedMissile(Vector2 position, Actor* enemytActor) : super("O", position), Enemyactor(enemytActor)
{
	gravity = false;		 
	sortingOrder = 14;
	//Renderer::Get().Submit("0", Vector2(position), Color::Green);

	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;

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
	
	

	startNode = new Node(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y));
	endNode = new Node(static_cast<int>(player->GetPosition().x), static_cast<int>(player->GetPosition().y));

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

void guidedMissile::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	delay.Tick(deltaTime);
	if (delay.IsTimeOut())
	{
		Guide();
		delay.Reset();

	}
	
}

void guidedMissile::Draw()
{
	super::Draw(); // 상위 클래스 그리기 호출

}

void guidedMissile::OnOverlap(Actor* actor)
{
	BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	if (!level) return;

	if (actor->IsTypeOf<BPlayer>())
	{
		BPlayer* player = level->GetBPlayerActor();
		if (player)
		{
			level->AddNewActor(new ExplosionEffect(actor->GetPosition(), 5) );
			level->AddNewActor(new WarningEffect());
			player->Damaged(-1);
			this->Destroy();
		}
			
	}
	if (actor->IsTypeOf<Hyeonmu5>())
	{

		level->AddNewActor(new ExplosionEffect(actor->GetPosition(), 10));
		actor->Destroy();
		this->Destroy();
	}
}
