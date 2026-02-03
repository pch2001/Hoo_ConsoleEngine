#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel 
	: public Wanted::Level, 
	public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

<<<<<<< HEAD
	// ÀÌº¥Æ® ÇÔ¼ö ¿À¹ö¶óÀÌµå.
	virtual void Draw() override;

private:
=======
private :
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)

	// °ÔÀÓ¿¡¼­ »ç¿ëÇÒ ¸ÊÀ» ·ÎµåÇÏ´Â ÇÔ¼ö.
	void LoadMap(const char* filename);
<<<<<<< HEAD

	// Inherited via ICanPlayerMove
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition, 
		const Wanted::Vector2& nextPosition) override;

	// °ÔÀÓ Å¬¸®¾î È®ÀÎ ÇÔ¼ö.
	bool CheckGameClear();

private:
	// È¹µæÇØ¾ßÇÏ´Â ¸ñÇ¥ Á¡¼ö.
	int targetScore = 0;

	// °ÔÀÓ Å¬¸®¾î ¿©ºÎ¸¦ ¾Ë·ÁÁÖ´Â º¯¼ö.
	bool isGameClear = false;
=======
	virtual bool CanMove (const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition);

>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
};
