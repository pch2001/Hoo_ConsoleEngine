#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Actor/Player.h"

using namespace Wanted;

struct MapChar4
{
	//const char* character;
	std::string character;
	Vector2 pos;


	MapChar4(std::string c, Vector2 p) : character(c), pos(p) {}
	MapChar4() : character(""), pos(Vector2()) {}
};
class GameLevel : public Level
{
	// RTTI 등록.
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(int level = 100);


	void PlusScore();
	int GetScore() { return score; }

private:

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;


	void UpdateMap();//무한 맵

	void SpawnNextPattern(int index); //다음 맵 패턴
	void LoadScene(); // 테두리


private:
	//마지막으로 생성된 지점 저장

	int lastSpawnX = 0;

	float cameraX = 0.0f;
	
	int score = 0;

	int spawnRange = 0;
	//Actor* player;
	
	std::vector<MapChar4> mapData;

};
