#include "TestLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"	
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Util/Util.h"

#include <iostream>

/*
#: º®(Wall)
.: ¹Ù´Ú(Ground)
p: ÇÃ·¹ÀÌ¾î(Player)
b: ¹Ú½º(Box)
t: Å¸°Ù(Target)
*/


TestLevel::TestLevel()
{
	// TestActor ¾×ÅÍ¸¦ ·¹º§¿¡ Ãß°¡.
	//AddNewActor(new Player());
	LoadMap("Map2.txt");


}

<<<<<<< HEAD:Game/Level/SokobanLevel.cpp
void SokobanLevel::Draw()
{
	super::Draw();

	//°ÔÀÓ Å¬¸®¾îÀÎ °æ¿ì. ¸Ş½ÃÁö Ãâ·Â.
	if (isGameClear)
	{
		//ÄÜ¼Ö À§Ä¡ »ö»ó ¼³Á¤
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);
		
		//°ÔÀÓ Å¬¸®¾î ¸Ş½ÃÁö Ãâ·Â
		std::cout << "Game Clear!";

	}
}

void SokobanLevel::LoadMap(const char* filename)
=======
void TestLevel::LoadMap(const char* filename)
>>>>>>> parent of 5f4630c (í”Œë ˆì´ì–´ ì´ë™ ì—¬ë¶€ ë¬¸ì˜ ì¸í„°í˜ì´ìŠ¤ ì¶”ê°€ / RTTIì— IsTypeOf API ì¶”ê°€):Game/Level/TestLevel.cpp
{
	// ÆÄÀÏ ·Îµå
	// ÃÖÁ¾ ÆÄÀÏ °æ·Î ¸¸µé±â, -> ("../Assets/ filename")
	char path[2048] = { };
	sprintf_s(path, 2048, "../Assets/%s", filename);

	//ÆÄÀÏ ¿­±â
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	//¿¹¿ÜÃ³¸®
	if (!file)
	{
		//Ç¥ÁØ ¿À·ù ÄÜ¼Ö È°¿ë
		std::cerr << "Failed to open map file\n";

		//µğ¹ö±× ¸ğµå¿¡¼­ Áß´ÜÁ¡À¸·Î Áß´ÜÇØÁÖ´Â ±â´É
		__debugbreak();
	}
	// ¸Ê ÀĞ±â
	// ¸Ê Å©±â ÆÄ¾Ç : File Position Æ÷ÀÎÅÍ¸¦ ÆÄÀÏÀÇ ³¡À¸·Î ÀÌµ¿
	fseek(file, 0, SEEK_END);

	// ÀÌ À§Ä¡ ÀĞ±â.
	size_t fileSize = ftell(file);

	// File Position Ã³À½À¸·Î µÇµ¹¸®±â.
	rewind(file);

	// ÆÄÀÏ¿¡¼­ µ¥ÀÌÅÍ¸¦ ÀĞ¾î¿Ã ¹öÆÛ »ı¼º
	char* data = new char[fileSize + 1];

	// µ¥ÀÌÅÍ ÀĞ±â
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// ÀĞ¾î¿Â ¹®ÀÚ¿­À» ºĞ¼®(ÆÄ½Ì - Parsing)ÇØ¼­ Ãâ·Â.
	// ÀÎµ¦½º¸¦ »ç¿ëÇØ ÇÑ¹®ÀÚ¾¿ ÀĞ±â.
	int index = 0;

	//°´Ã¼¸¦ »ı¼ºÇÒ À§Ä¡ °ª
	Wanted::Vector2 position;


	while (true)
	{
		if (index >= fileSize)
		{
			break;
		}

		//Ä³¸¯ÅÍ ÀĞ±â
		char mapCharacter = data[index];
		++index;

		//°³Çà ¹®ÀÚ Ã³¸®.
		if (mapCharacter == '\n')
		{
			std::cout << "\n";
			//yÁÂÇ¥´Â ÇÏ³ª ´Ã¸®°í, x ÁÂÇ¥ ÃÊ±âÈ­.
			++position.y;
			position.x = 0;
			continue;
		}

		//ÇÑ ¹®ÀÚ¾¿ Ã³¸®
		/*
			#: º®(Wall)
			.: ¹Ù´Ú(Ground)
			p: ÇÃ·¹ÀÌ¾î(Player)
			b: ¹Ú½º(Box)
			t: Å¸°Ù(Target)
		*/

		switch (mapCharacter)
		{
		case '#':
		case '1':
			//std::cout << "#";
			AddNewActor(new Wall(position));
			break;
		case '.':
			//std::cout << " ";
			AddNewActor(new Ground(position));
			break;
		case 'p':
			//std::cout << "P";
			AddNewActor(new Player(position));
			AddNewActor(new Ground(position));
			break;
		case 'b':
			//std::cout << "B";
			//¹Ú½º´Â ÀÌµ¿ °¡´ÉÇÔ
			//¹Ú½º°¡ ¿Å°ÜÁ³À» ¶§ ±× ¹Ø¿¡ ¶¥ÀÌ ÀÖ¾î¾ß ÇÔ
			AddNewActor(new Box(position));
			AddNewActor(new Ground(position));
			break;
		case 't':
			//std::cout << "T";
			++targetScore;
			AddNewActor(new Target(position));
			break;
		default:
			break;

		}
		
		//x ÁÂÇ¥ Áõ°¡ Ã³¸®
		++position.x;

	}

	//»ç¿ëÇÑ ¹öÆÛ ÇØÁ¦.
	delete[] data;

	// ÆÄÀÏÀÌ Á¤»óÀûÀ¸·Î ¿­·ÈÀ¸¸é ´İ±â
	fclose(file);

}
<<<<<<< HEAD:Game/Level/SokobanLevel.cpp

bool SokobanLevel::CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition)
{

	//·¹º§¿¡ ÀÖ´Â ¹Ú½º ¾×ÅÍ ¸ğÀ¸±â
	//¹Ú½º´Â ÇÃ·¹ÀÌ¾î°¡ ¹Ğ±â µî Ãß°¡ÀûÀ¸·Î Ã³¸®ÇØ¾ßÇÏ±â ¶§¹®
	std::vector<Actor*> boxes;

	for (Actor* const actor : actors)
	{
		//¾×ÅÍ°¡ ¹Ú½º Å¸ÀÔÀÎÁö È®ÀÎ
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}
	// ÀÌµ¿ÇÏ·Á´Â À§Ä¡¿¡ ¹Ú½º°¡ ÀÖ´ÂÁö È®ÀÎ
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		//À§Ä¡ ºñ±³.
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box;
			break;
		}
	}
	//°æ¿ìÀÇ ¼ö Ã³¸®.
	//1.ÀÌµ¿ÇÏ·Á´Â °÷¿¡ ¹Ú½º°¡ ÀÖ´Â °æ¿ì
	if (boxActor)
	{
		// #1 : ¹Ú½º°¡ ÀÌµ¿½ÃÅ°·Á´Â À§Ä¡¿¡ ´Ù¸¥ ¹Ú½º°¡ ¶Ç ÀÖ´ÂÁö È®ÀÎ.
		//		µÎ À§Ä¡ »çÀÌ¿¡¼­ ÀÌµ¿ ¹æÇâ ±¸ÇÏ±â. (º¤ÅÍÀÇ »¬¼À È°¿ë)
		// ÀÌµ¿ ·ÎÁ÷¿¡¼­ µÎ º¤ÅÍ¸¦ ´õÇÑ´Ù´Â °ÍÀº
		// µÑ Áß ÇÏ³ª´Â À§Ä¡(Location)ÀÌ°í ´Ù¸¥ ÇÏ³ª´Â º¤ÅÍ(Vector).                                                                                                         
		Vector2 direction = nextPosition - playerPosition;
		Vector2 newPosition = boxActor->GetPosition() + direction;
	
		//¹Ú½º °Ë»ö
		for (Actor* const otherBox : boxes)
		{
			// ¾Õ¿¡¼­ °Ë»öÇÑ ¹Ú½º¿Í °°´Ù¸é °Ç³Ê¶Ù±â.
			if (otherBox == boxActor)
			{
				continue;
			}

			// ´Ù¸¥ ¹Ú½º°¡ ÀÖ´ÂÁö È®ÀÎ.
			if (otherBox->GetPosition() == newPosition)
			{
				// µÎ °³ÀÇ ¹Ú½º°¡ °ãÃÄÁø ¹æÇâÀ¸·Î´Â ÀÌµ¿ ¸øÇÔ.
				return false;
			}
		}

		// °Ë»ö
		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == newPosition)
			{
				//# 2: º®ÀÌ¸é ÀÌµ¿ºÒ°¡
				if (actor->IsTypeOf<Wall>())
				{
					return false;
				}

				//#3: ±×¶ó¿îµå or Å¸°ÙÀÌ¸é ÀÌµ¿ °¡´É
				if (actor->IsTypeOf<Ground>() || actor->IsTypeOf<Target>())
				{
					//¹Ú½º ÀÌµ¿ Ã³¸®
					boxActor->SetPosition(newPosition);
						//Á¡¼öÃ³¸®
						isGameClear = CheckGameClear();
						//ÇÃ·¹ÀÌ¾î ÀÌµ¿ Ã³¸®
						return true;
				}
			}
		}

	}

	//2. ÀÌµ¿ÇÏ·Á´Â °÷¿¡ ¹Ú½º°¡ ¾ø´Â °æ¿ì
	// -> ÀÌµ¿ÇÏ·Á´Â °÷¿¡ ÀÖ´Â ¾×ÅÍ°¡ º®ÀÌ ¾Æ´Ï¸é ÀÌµ¿ °¡´É.
	for (Actor* const actor : actors)
	{
		//¸ÕÀú. ÀÌµ¿ÇÏ·Á´Â À§Ä¡¿¡ ÀÖ´Â ¾×ÅÍ °Ë»ö
		if (actor->GetPosition() == nextPosition)
		{
			//ÀÌ ¾×ÅÍ°¡ º®ÀÎÁö È®ÀÎ.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}
			//±×¶ó¿îµå ¶Ç´Â Å¸°Ù
			return true;
		}
	}




	//¿¡·¯
	return false;
}

bool SokobanLevel::CheckGameClear()
{
	//Å¸°Ù À§¿¡ ÀÖ´Â ¹Ú½ºÀÇ ¼ö °ËÁõ
	int currentScore = 0;

	//¹è¿­¿¡ ¹Ú½º ¹× Å¸°Ù ÀúÀå.
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	//·¹º§¿¡ ¹èÄ¡µÈ ¹è¿­ ¼øÈ¸ÇÏ¸é¼­ µÎ ¾×ÅÍ ÇÊÅÍ¸µ.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
		// Å¸°ÙÀÇ °æ¿ì Å¸°Ù ¹è¿­¿¡ Ãß°¡.
		if (actor->IsTypeOf<Target>())
		{
			targets.emplace_back(actor);
		}
	}

	//Á¡¼ö È®ÀÎ(¹Ú½ºÀÇ À§Ä¡°¡ Å¸°ÙÀÇ À§Ä¡¿Í °°ÀºÁö ºñ±³)
	for (Actor* const box : boxes)
	{
		for (Actor* const target : targets)
		{
			//µÎ ¾×ÅÍÀÇ À§Ä¡°¡ °°À¸¸é Á¡¼ö +
			if (box->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
		}
	}

	return currentScore == targetScore;
}

=======
>>>>>>> parent of 5f4630c (í”Œë ˆì´ì–´ ì´ë™ ì—¬ë¶€ ë¬¸ì˜ ì¸í„°í˜ì´ìŠ¤ ì¶”ê°€ / RTTIì— IsTypeOf API ì¶”ê°€):Game/Level/TestLevel.cpp
