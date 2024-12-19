#include "pch.h"
#include "Scene.h"
#include "Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "Item_Compass.h"

void Scene_Menu()
{
	ScreenPrint(10, 10, "HORROR MAZE");
	ScreenPrint(10, 11, "제작자: 강규석");
	ScreenPrint(10, 14, "조작키");
	ScreenPrint(10, 16, "방향키 위 아래 : 앞 뒤로 이동");
	ScreenPrint(10, 17, "방향키 좌 우 : 좌우 회전 ");

	ScreenPrint(10, 19, "죽지않고 탈줄할 것 (파란색 포탈로 이동)");
	ScreenPrint(10, 20, "Press Space To Start");
	ScreenPrint(10, 22, "SPECIAL THANKS 김유진, 이기태");

	// Space키를 누를 시 Game화면으로 씬 이동
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		currentScene = E_SCENE_GAME;
		//SoundManager_PlaySound(SOUND_BGM);
	}
	ScreenFlipping();
}


void Scene_Game()
{

	Item_Compass(GetInstance()->player);

	
	//bool isPlay = true;
	//if(channelMusic->isPlaying(&isPlay))
	if (CheckGameOver())
	{
		currentScene = E_SCENE_GAMEOVER;
	}

	// 미니맵 출력
	if(GetAsyncKeyState(VK_TAB)&0x8001)
		DrawScreen(GetInstance()->player, GetInstance()->enemy);
	// Update
	Player_Update(GetInstance()->player);
	Enemy_Update(GetInstance()->enemy, 0);
}

void Scene_GameOver()
{
	DrawEnemy(12);
	ScreenPrintColor(10, 10, "GameOver", FOREGROUND_RED);
	ScreenFlipping();
}

void Scene_GameClear()
{
	ScreenClear();
	ScreenPrint(10, 10, "Game Clear!!");
	ScreenPrint(10, 22, "제작자 : 강규석");
	ScreenFlipping();
}

bool CheckGameOver()
{
	if (PosOperator_IsSame(Player_GetPosition(GetInstance()->player), Enemy_GetPosition(GetInstance()->enemy)))
	{
		return true;
	}
	return false;
}
