#pragma once

#include "Common/Common.h"
#include <Windows.h>


namespace Wanted
{
	// 콘솔에 텍스트 색상 등을 지정할 때 사용할
	// 색상 열거형
	enum class WANTED_API Color : unsigned short
	{
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		Black = 0,
		White = Blue | Green | Red,
	};
}