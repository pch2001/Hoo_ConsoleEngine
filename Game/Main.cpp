#include <iostream>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/SokobanLevel.h"

using namespace Wanted;



int main()
{
	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

	//Game game;
	//game.Run();

	//=========================================================


	//예시 배열
	const int width = 3;
	const int height = 3;

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

	// 문자 배열을 한번에 콘솔로 넘겨서 그릴 때 사용하는 함수.
	WriteConsoleOutputA(
		GetStdHandle(STD_OUTPUT_HANDLE), charArray, screenSize, position, &writeRegion
	);

	//CreateConsoleScreenBuffer();
	

	std::cin.get();
}