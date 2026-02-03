#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

<<<<<<< HEAD
#include "Game/Game.h"

=======
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>


Player::Player(const Vector2& position)
	: super('P', position, Color::Red)
{
<<<<<<< HEAD
	// ±×¸®±â ¿ì¼±¼øÀ§ ³ô°Ô ¼³Á¤.
=======
	//±×¸¯ ¿ì¼±¼øÀ§¼³Á¤
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// »óÀ§ ÇÔ¼ö È£Ãâ.
	// C++´Â ºÎ¸ğÇÔ¼ö °¡¸®Å°´Â Æ÷ÀÎÅÍ°¡ ¾øÀ½.
	Actor::BeginPlay();

	std::cout << "TestActor::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
<<<<<<< HEAD
	super::Tick(deltaTime);

	// ESCÅ° Ã³¸®.
	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// ¸Ş´º È°¼ºÈ­.
		Game::Get().ToggleMenu();
		return;
	}
=======
	Actor::Tick(deltaTime);
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)

	// QÅ° Á¾·á.
	if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		// Todo: °ÔÀÓ ¿£Áø Á¾·á ¿äÃ».
		Wanted::Engine::Get().QuitEngine();
	}

<<<<<<< HEAD
	// ½ºÆäÀÌ½º·Î ¹Ú½º »ı¼º.
	// vk->virtual key.
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		// ¹Ú½º »ı¼º.
=======
	// ½ºÆäÀÌ½º·Î ¹Ú½º »ı¼º
	if (Wanted::Input::Get().GetKeyDown(VK_SPACE))
	{			
		// ¹Ú½º »ı¼º
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition()));
		}
	}

<<<<<<< HEAD
	// ÀÎÅÍÆäÀÌ½º È®ÀÎ.
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	// ¿À³Ê½Ê È®ÀÎ (null È®ÀÎ).
	if (!canPlayerMoveInterface && GetOwner())
	{
		// ÀÎÅÍÆäÀÌ½º·Î Çüº¯È¯.
=======
	//ÀÎÅÍÆäÀÌ½º È®ÀÎ
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	//dynamic_cast°¡ °è¼Ó ÇÁ·¹ÀÓ¸¶´Ù È£ÃâÇÏ´Â°Ç ÁÁÁö ¾Ê±â ‹š¹®¿¡
	// canPlayerMoveInterfaceÀ» Àü¿ªº¯¼ö·Î ¼±¾ğÇØ¼­ µ¥ÀÌÅÍ ¿µ¿ª¿¡ ÇÑ¹ø¸¸ °øÀ¯ÇÏµµ·Ï ¼±¾ğ
	// ÀÌÈÄ¿¡´Â º¯È¯¾ÈÇÔ
	//¿À³Ê½Ê È®ÀÎ(nullÈ®ÀÎ)
	if (!canPlayerMoveInterface && GetOwner())
	{
		//ÀÎÅÍÆäÀÌ½º·Î Çüº¯È¯ 
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

<<<<<<< HEAD
	// ÀÌµ¿.
	if (Input::Get().GetKeyDown(VK_RIGHT) && GetPosition().x < 20)
	{
		// ÀÌµ¿ °¡´É ¿©ºÎ ÆÇ´Ü.
=======
	//ÀÌµ¿
	if (Wanted::Input::Get().GetKeyDown(VK_RIGHT) && GetPosition().x < 40) {
		//ÀÌµ¿ °¡´É ¿©ºÎ ÆÇ´Ü
>>>>>>> parent of e79c575 (ë©”ë‰´ ë ˆë²¨ ì¶”ê°€ ë° ë ˆë²¨ ì „í™˜ ì ìš©)
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x += 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown(VK_LEFT) && GetPosition().x > 0)
	{
		// ÀÌµ¿ °¡´É ¿©ºÎ ÆÇ´Ü.
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x -= 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown(VK_DOWN) && GetPosition().y < 15)
	{
		// ÀÌµ¿ °¡´É ¿©ºÎ ÆÇ´Ü.
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.y += 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown(VK_UP) && GetPosition().y > 0)
	{
		// ÀÌµ¿ °¡´É ¿©ºÎ ÆÇ´Ü.
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.y -= 1;
		//SetPosition(newPosition);
	}
}

void Player::Draw()
{
	Actor::Draw();
}
