#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"

using namespace Wanted;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	

	_CrtSetBreakAlloc(158); 
	_CrtSetBreakAlloc(177);
	_CrtSetBreakAlloc(788);
	_CrtSetBreakAlloc(830);
	/*_CrtSetBreakAlloc(51649);

	_CrtSetBreakAlloc(51082);
	_CrtSetBreakAlloc(50993);
	_CrtSetBreakAlloc(23678);
	_CrtSetBreakAlloc(50320);
	_CrtSetBreakAlloc(25235);

	_CrtSetBreakAlloc(25759);
	_CrtSetBreakAlloc(45443);
	_CrtSetBreakAlloc(45082);
	_CrtSetBreakAlloc(44413);
	_CrtSetBreakAlloc(36527);*/

	/*_CrtSetBreakAlloc(964);
	_CrtSetBreakAlloc(958);
	_CrtSetBreakAlloc(1847);
	_CrtSetBreakAlloc(1858);
	_CrtSetBreakAlloc(1870);*/

	/*Engine engine;
	engine.SetNewLevel(new GameLevel());
	engine.Run();
	*/

	Game game;
	game.Run();

}