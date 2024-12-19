#include "pch.h"
#include "Renderer.h"
#include "Player.h"
#include "TimeManager.h"
#include "SoundManager.h"
// Scene
#include "Scene.h"


int main()
{
#pragma region GameInit
	//Initialize
	system("mode con cols=175 lines=90 | title HorrorMaze");
	HWND hWnd = GetConsoleWindow();
	SetWindowPos(hWnd, HWND_TOP, 0, 0, 1, 1, SWP_NOSIZE);



	srand(time(NULL));

	SoundManager_Init();
	InitMap();

	currentScene = E_SCENE_MENU;
	bool isGameOver = false;

	// 플레이어와 몬스터의 초기 포지션 지정
	Pos playerPosition = { 1, 1 };
	Pos enemyPosition = { HEIGHT - 2 , WIDTH - 2};

	Player_Init(GetInstance()->player, playerPosition);
	Enemy_Init(GetInstance()->enemy, enemyPosition);
	//Enemy_Init(GetInstance()->enemy, GetInstance()->player->pos);	// Test

	// 그림 초기 설정 및 더블버퍼링 초기 세팅
	ScreenInit();
#pragma endregion GameInit


	while (true)
	{
		ScreenClear();
		switch (currentScene)
		{
		case E_SCENE_MENU:
		{
			Scene_Menu();
		}
		break;
		case E_SCENE_GAME:
		{
			Scene_Game();
			isGameOver = CheckGameOver();
		}
		break;
		case E_SCENE_GAMEOVER:
		{
			Scene_GameOver();
		}
		break;
		case E_SCENE_GAMECLEAR:
		{
			Scene_GameClear();
		}
		break;
		default:
			break;
		}
	}

	MemoryAllClear();
	return 0;
}