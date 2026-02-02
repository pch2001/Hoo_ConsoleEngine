#include "Box.h"



Box::Box(const Wanted::Vector2& newPosition): super('B', newPosition, Wanted::Color::Blue)
{
	sortingOrder = 7;	
}
