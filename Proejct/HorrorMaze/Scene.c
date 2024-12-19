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
	ScreenPrint(10, 11, "������: ���Լ�");
	ScreenPrint(10, 14, "����Ű");
	ScreenPrint(10, 16, "����Ű �� �Ʒ� : �� �ڷ� �̵�");
	ScreenPrint(10, 17, "����Ű �� �� : �¿� ȸ�� ");

	ScreenPrint(10, 19, "�����ʰ� Ż���� �� (�Ķ��� ��Ż�� �̵�)");
	ScreenPrint(10, 20, "Press Space To Start");
	ScreenPrint(10, 22, "SPECIAL THANKS ������, �̱���");

	// SpaceŰ�� ���� �� Gameȭ������ �� �̵�
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

	// �̴ϸ� ���
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
	ScreenPrint(10, 22, "������ : ���Լ�");
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
