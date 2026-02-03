#include <iostream>
#include "Engine/Engine.h"
<<<<<<< HEAD
#include "Game/Game.h"
=======
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
#include "Level/SokobanLevel.h"

using namespace Wanted;



int main()
{
<<<<<<< HEAD
	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	//Game game;
	//game.Run();

	//=========================================================


	//¿¹½Ã ¹è¿­
	const int width = 3;
	const int height = 3;
=======
	Wanted::Engine engine;
	engine.SetNewLevel(new SokobanLevel());
	engine.Run();
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)

	CHAR_INFO charArray[width * height] = { };
	charArray[2 * height + 1].Char.AsciiChar = 'P';
	charArray[2 * height + 1].Attributes = FOREGROUND_GREEN;

	charArray[0 * height + 1].Char.AsciiChar = '#';
	charArray[0 * height + 1].Attributes = FOREGROUND_RED;


	COORD position = {};
	COORD screenSize;
	screenSize.X = 3;
	screenSize.Y = 3;

	SMALL_RECT writeRegion{ 0, 0, static_cast<short> (width), static_cast<short> (height) };

	// ¹®ÀÚ ¹è¿­À» ÇÑ¹ø¿¡ ÄÜ¼Ö·Î ³Ñ°Ü¼­ ±×¸± ¶§ »ç¿ëÇÏ´Â ÇÔ¼ö.
	WriteConsoleOutputA(
		GetStdHandle(STD_OUTPUT_HANDLE), charArray, screenSize, position, &writeRegion
	);

	//CreateConsoleScreenBuffer();
	

	std::cin.get();
}