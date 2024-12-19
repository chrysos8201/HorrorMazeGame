#include "pch.h"
#include "Item_Compass.h"


void Item_Compass(Player* player)
{
	switch (player->dir)
	{
	case DIR_UP:
	{
		ScreenPrintColor(120, 10, "N", FOREGROUND_RED);
		ScreenPrintColor(118, 11, "W", 7);
		ScreenPrintColor(122, 11, "E", 7);
		ScreenPrintColor(120, 12, "S", 7);
	}
	break;
	case DIR_RIGHT:
	{
		ScreenPrintColor(120, 10, "E", 7);
		ScreenPrintColor(122, 11, "S", 7);
		ScreenPrintColor(120, 12, "W", 7);
		ScreenPrintColor(118, 11, "N", FOREGROUND_RED);
	}
	break;
	case DIR_DOWN:
	{
		ScreenPrintColor(120, 10, "S", 7);
		ScreenPrintColor(122, 11, "W", 7);
		ScreenPrintColor(120, 12, "N", FOREGROUND_RED);
		ScreenPrintColor(118, 11, "E", 7);
	}
	break;
	case DIR_LEFT:
	{
		ScreenPrintColor(120, 10, "W", 7);
		ScreenPrintColor(122, 11, "N", FOREGROUND_RED);
		ScreenPrintColor(120, 12, "E", 7);
		ScreenPrintColor(118, 11, "S", 7);
	}
	break;
	}
}