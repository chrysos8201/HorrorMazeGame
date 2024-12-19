#include "pch.h"
#include "Renderer.h"
#include <Windows.h>
#include <time.h>



// player 화살표
char playerCharacter[] = { 'U','L','D','R' };


#pragma region Screen
//int nFieldWidth = HEIGHT;
int nFieldWidth = 120;
//int nFieldHeight = WIDTH;
int nFieldHeight = 120;
unsigned char* pField = NULL;

int nScreenWidth = 120;			//Console Screen Size X (columns)
int nScreenHeight = 120;			//Console Screen Size Y (rows)

#pragma endregion Screen

int currentTime = 0;




int curTime, oldTime;

#define BUF_SIZE 3600

// 콘솔 접근 인덱스
static int g_nScreenIndex;
// 콘솔 2개
static HANDLE g_hScreen[2];
// 누적 프레임
int g_numOfFrame;
// 분당 프레임
int g_numOfFPS;

int deltaTime;
// 콘솔에 출력할 char 포인터
char* FPSTextInfo;


// Wall
Data_Wall dataWall[FIND_INDEX];

// Enemy
Data_Enemy dataEnemy[FIND_INDEX];

/// <summary>
/// 더블 버퍼링을 위한 콘솔 2개를 준비하는 함수
/// </summary>
void ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


	// 커서를 숨긴다.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);


	// 벽 초기화
	for (int i = 0; i < FIND_INDEX; i++)
	{
		InitWallTextData(&dataWall[i], i + 1);
	}

	// dataEnemy 초기화
	for (int i = 0; i < FIND_INDEX ; i++)
	{
		InitEnemyTextData(&dataEnemy[i], i + 1);
	}
}

/// <summary>
/// 화면에 보여줄 콘솔을 스위칭하는 함수
/// </summary>
void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}


/// <summary>
/// 스크린을 빈 공간으로 지우는 함수
/// 현재 콘솔을 다 쓰고나면 다음 콘솔로 바꾸어주면서 이전 콘솔의 내용은 깨끗하게 지우고 다시 출력하기 위해 사용
/// </summary>
void ScreenClear()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', nScreenHeight * nScreenWidth, Coor, &dw);
}

/// <summary>
/// char* 버퍼의 내용을 콘솔에 출력하는 함수
/// x, y는 출력을 시작할 콘솔의 위치
/// </summary>
void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD cursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], cursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}
/// <summary>
/// char* 버퍼의 내용을 콘솔에 출력하는 함수, 색 추가
/// x, y는 출력을 시작할 콘솔의 위치
/// </summary>
void ScreenPrintColor(int x, int y, char* string, int color)
{
	DWORD dw;
	COORD cursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], cursorPosition);
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}
/// <summary>
/// char* 버퍼의 내용을 콘솔에 출력하는 함수, 여러 줄을 사용할 때 사용
/// x, y는 출력을 시작할 콘솔의 위치
/// </summary>
void ScreenPrintPro(int x, int y, char* string, int width, int height)
{
	DWORD dw;
	COORD cursorPosition = { x,y };

	int index = 0;
	for (int dy = 0; dy < height; dy++)
	{
		char* str = (char*)malloc(sizeof(char) * width + 1);
		memset(str, '\0', sizeof(char) * width + 1);
		for (int j = 0; j < width + 1; j++)
		{
			str[j] = string[j + index];
		}
		str[width] = '\0';
		index += width;
		SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], cursorPosition);
		WriteFile(g_hScreen[g_nScreenIndex], str, strlen(str), &dw, NULL);
		cursorPosition.Y++;
		free(str);
	}
}
/// <summary>
/// char* 버퍼의 내용을 콘솔에 출력하는 함수, 여러 줄을 사용할 때 사용, 색 추가 버전
/// x, y는 출력을 시작할 콘솔의 위치
/// </summary>
void ScreenPrintProColor(int x, int y, char* string, int width, int height, int color)
{
	DWORD dw;
	COORD cursorPosition = { x,y };
	

	int index = 0;
	for (int dy = 0; dy < height; dy++)
	{
		char* str = (char*)malloc(sizeof(char) * width + 1);
		memset(str, '\0', sizeof(char) * width + 1);
		for (int j = 0; j < width + 1; j++)
		{
			str[j] = string[j + index];
		}
		str[width] = '\0';
		index += width;
		SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], cursorPosition);
		SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
		WriteFile(g_hScreen[g_nScreenIndex], str, strlen(str), &dw, NULL);
		cursorPosition.Y++;
		free(str);
	}
}

void DrawScreen(Player* player, Enemy* enemy)
{
	//ScreenClear();
	char* drawMap = (char*)malloc(sizeof(char) * (HEIGHT * WIDTH + 1));
	//wchar_t* drawMap= (wchar_t*)malloc(sizeof(wchar_t) *(HEIGHT * WIDTH + 1));


	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == 0)
				drawMap[y * WIDTH + x] = '.';
			else
				drawMap[y * WIDTH + x] = 'W';
		}
	}

	drawMap[player->pos.y * WIDTH + player->pos.x] = playerCharacter[player->dir];
	drawMap[enemy->pos.y * WIDTH + enemy->pos.x] = 'E';
	drawMap[enemy->dest.y * WIDTH + enemy->dest.x] = 'D';
	//drawMap[HEIGHT * WIDTH - 1] = '8';
	drawMap[HEIGHT * WIDTH] = '\0';

	//ScreenPrintPro(120, 20, drawMap, WIDTH, HEIGHT);
	int COLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	ScreenPrintProColor(120, 20, drawMap, WIDTH, HEIGHT, COLOR_WHITE);
	free(drawMap);
}

void DrawWall(int index)
{
	ScreenPrintWall(&dataWall[index]);
}
void DrawEscapeWall(int index)
{
	ScreenPrintEscapeWall(&dataWall[index]);
}
void DrawEnemy(int index)
{
	ScreenPrintEnemy(&dataEnemy[index]);
}




#pragma region WallText

void InitWallTextData(Data_Wall* dataWall, int index)
{
	switch (index)
	{
	case 1:
	{
		dataWall->pos.y = 25;
		dataWall->pos.x = 4;
		dataWall->wall = "[----------]9 [          ] 9[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] /[__________]/ ";
		dataWall->width = 14;
		dataWall->height = 15;

		dataWall->size = dataWall->width * dataWall->height;

	}
	break;

	case 3:
	{
		dataWall->pos.y = 25;
		dataWall->pos.x = 16;
		dataWall->wall = "[----------]9 [          ] 9[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] |[          ] /[__________]/ ";
		dataWall->width = 14;
		dataWall->height = 15;

		dataWall->size = dataWall->width * dataWall->height;
	}
	break;

	case 5:
	{
		dataWall->pos.y = 25;
		dataWall->pos.x = 28;
		dataWall->wall = "[----------][          ][          ][          ][          ][          ][          ][          ][          ][          ][          ][__________]";
		dataWall->width = 12;
		dataWall->height = 15;

		dataWall->size = dataWall->width * dataWall->height;
	}
	break;

	case 2:
	{
		dataWall->pos.y = 25;
		dataWall->pos.x = 50;
		dataWall->wall = " /[----------]/ [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]6 [          ] 6[__________]";
		dataWall->width = 14;
		dataWall->height = 15;
	}
	break;
	case 4:
	{
		dataWall->pos.y = 25;
		dataWall->pos.x = 38;
		dataWall->wall = " /[----------]/ [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]| [          ]6 [          ] 6[__________]";
		dataWall->width = 14;
		dataWall->height = 15;
	}
	break;
	case 6:
	{
		dataWall->pos.y = 19;
		dataWall->pos.x = 3;
		dataWall->wall = "      9             9             9             9             9             9             ]            ]            ]            ]            ]            ]            ]            ]            ]            ]            ]            ]           /           /           /           /           /           /      ";
		dataWall->width = 13;
		dataWall->height = 25;
	}
	break;
	case 7:	//
	{
		dataWall->pos.y = 19;
		dataWall->pos.x = 52;
		dataWall->wall = "      /           /           /           /           /           /           [            [            [            [            [            [            [            [            [            [            [            [             6             6             6             6             6             6      ";
		dataWall->width = 13;
		dataWall->height = 25;
	}
	break;
	case 8:
	{
		dataWall->pos.y = 19;
		dataWall->pos.x = 4;
		dataWall->wall = "-----------------]9                       ] 9                      ]  9                     ]   9                    ]    9                   ]     9                  ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]      ]                 ]     /                  ]    /                   ]   /                    ]  /                     ] /     _________________]/      ";
		dataWall->width = 25;
		dataWall->height = 25;
	}
	break;
	case 10:
	{
		dataWall->pos.y = 19;
		dataWall->pos.x = 22;
		dataWall->wall = "[----------------------][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][                      ][______________________]";
		dataWall->width = 24;
		dataWall->height = 25;
	}
	break;		
	case 9:
	{
		dataWall->pos.y = 19;
		dataWall->pos.x = 39;
		dataWall->wall = "      /[-----------------     / [                     /  [                    /   [                   /    [                  /     [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                 [      [                  6     [                   6    [                    6   [                     6  [                      6 [                       6[_________________";
		dataWall->width = 25;
		dataWall->height = 25;
	}
	break;
	case 11:
	{
		dataWall->pos.y = 11;
		dataWall->pos.x = 4;
		dataWall->wall = "---------]9                 ] 9                ]  9               ]   9              ]    9             ]     9            ]      9           ]       9          ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]        ]         ]       /          ]      /           ]     /            ]    /             ]   /              ]  /               ] /       _________]/        ";
		dataWall->width = 19;
		dataWall->height = 40;
	}
	break;
	case 13:
	{
		dataWall->pos.y = 11;
		dataWall->pos.x = 14;
		dataWall->wall = "[--------------------------------------][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][                                      ][______________________________________]";
		dataWall->width = 40;
		dataWall->height = 40;
	}
	break;
	case 12:
	{
		dataWall->pos.y = 11;
		dataWall->pos.x = 45;
		dataWall->wall = "        /[---------       / [               /  [              /   [             /    [            /     [           /      [          /       [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [         [        [          6       [           6      [            6     [             6    [              6   [               6  [                6 [                 6[_________";
		dataWall->width = 19;
		dataWall->height = 40;
	}
	break;
	case 14:
	{
		dataWall->pos.y = 1;
		dataWall->pos.x = 4;
		dataWall->wall = "9          9          9          9          9          9          9          9          9          9         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         ]         /        /        /        /        /        /        /        /        /        /         ";
		dataWall->width = 10;
		dataWall->height = 60;
	}
	break;
	case 15:
	{
		dataWall->pos.y = 1;
		dataWall->pos.x = 54;
		dataWall->wall = "         /        /        /        /        /        /        /        /        /        /         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         [         6          6          6          6          6          6          6          6          6          6";
		dataWall->width = 10;
		dataWall->height = 60;
	}
	break;
	}
}


ScreenPrintWall(Data_Wall* wall)
{
	// 왠지는 모르겠지만 width랑 height를 반대로 넣어야 함. 근데 고치면 어떤 버그가 생길지 모르니 그냥 냅두겠어용

	//ScreenPrintPro(wall->pos.x, wall->pos.y, wall->wall, wall->width, wall->height);
	
	ScreenPrintProColor(wall->pos.x, wall->pos.y, wall->wall, wall->width, wall->height, WALL_COLOR);
}
ScreenPrintEscapeWall(Data_Wall* wall)
{
	ScreenPrintProColor(wall->pos.x, wall->pos.y, wall->wall, wall->width, wall->height, FOREGROUND_BLUE);
}
#pragma endregion WallText

#pragma region EnemyText

void InitEnemyTextData(Data_Enemy* dataEnemy, int index)
{
	switch (index)
	{
	case 1:
	{
		dataEnemy->pos.y = 25;
		dataEnemy->pos.x = 6;
		dataEnemy->enemy = "   OOO    OO   OO  O     O O  O O  OO       OO O   O O O OOO O  OO   OO    OOO   ";
		dataEnemy->width = 9;
		dataEnemy->height = 9;
	}
	break;
	case 3:
	{
		dataEnemy->pos.y = 25;
		dataEnemy->pos.x = 18;
		dataEnemy->enemy = "   OOO    OO   OO  O     O O  O O  OO       OO O   O O O OOO O  OO   OO    OOO   ";
		dataEnemy->width = 9;
		dataEnemy->height = 9;
	}
	break;
	case 5:
	{
		dataEnemy->pos.y = 25;
		dataEnemy->pos.x = 30;
		dataEnemy->enemy = "   OOO    OO   OO  O     O O  O O  OO       OO O   O O O OOO O  OO   OO    OOO   ";
		dataEnemy->width = 9;
		dataEnemy->height = 9;
	}
	break;
	case 2:
	{
		dataEnemy->pos.y = 25;
		dataEnemy->pos.x = 52;
		dataEnemy->enemy = "   OOO    OO   OO  O     O O  O O  OO       OO O   O O O OOO O  OO   OO    OOO   ";
		dataEnemy->width = 9;
		dataEnemy->height = 9;
	}
	break;
	case 4:
	{
		dataEnemy->pos.y = 25;
		dataEnemy->pos.x = 40;
		dataEnemy->enemy = "   OOO    OO   OO  O     O O  O O  OO       OO O   O O O OOO O  OO   OO    OOO   ";
		dataEnemy->width = 9;
		dataEnemy->height = 9;
	}
	break;

	case 6:
	{
		dataEnemy->pos.y = 19;
		dataEnemy->pos.x = 5;
		dataEnemy->enemy = "OOO          OO          OO          O         O    OOO   O  O   O  O  O   O   O O   O   O  OOO    O         O         O   O    O    O    O  OOO   O  OO     O       OO      OO     OOO       ";
		dataEnemy->width = 10;
		dataEnemy->height = 19;
	}
	break;
	
	case 7:
	{
		dataEnemy->pos.y = 19;
		dataEnemy->pos.x = 54;
		dataEnemy->enemy = "       OOO     OO      OO       O         O        O   OOO   O  O   O O   O   O O   O   O O    OOO  O         O          O    O    O    O     O   OOO   O     OO   OO          OO          OOO";
		dataEnemy->width = 10;
		dataEnemy->height = 19;
	}
	break;

	case 8:
	{
		dataEnemy->pos.y = 19;
		dataEnemy->pos.x = 6;
		dataEnemy->enemy = "       OOOOO            OO     OO        OO         OO     O             O    O             O   O   OOO   OOO   O  O  O   O O   O  O O   O   O O   O   OO   O   O O   O   OO    OOO   OOO    OO                 OO                 O O   O      O    O  O   O      O    O   O  OOO  OOO   O    O    OOOO     O     OO         OO        OO     OO            OOOOO       ";
		dataEnemy->width = 19;
		dataEnemy->height = 19;
	}
	break;

	case 9:
	{
		dataEnemy->pos.y = 19;
		dataEnemy->pos.x = 41;
		dataEnemy->enemy = "       OOOOO            OO     OO        OO         OO     O             O    O             O   O   OOO   OOO   O  O  O   O O   O  O O   O   O O   O   OO   O   O O   O   OO    OOO   OOO    OO                 OO                 O O   O      O    O  O   O      O    O   O  OOO  OOO   O    O    OOOO     O     OO         OO        OO     OO            OOOOO       ";
		dataEnemy->width = 19;
		dataEnemy->height = 19;
	}
	break;

	case 10:
	{
		dataEnemy->pos.y = 19;
		dataEnemy->pos.x = 24;
		dataEnemy->enemy = "       OOOOO            OO     OO        OO         OO     O             O    O             O   O   OOO   OOO   O  O  O   O O   O  O O   O   O O   O   OO   O   O O   O   OO    OOO   OOO    OO                 OO                 O O   O      O    O  O   O      O    O   O  OOO  OOO   O    O    OOOO     O     OO         OO        OO     OO            OOOOO       ";
		dataEnemy->width = 19;
		dataEnemy->height = 19;
	}
	break;

	case 13:
	{
		dataEnemy->pos.y = 11;
		dataEnemy->pos.x = 16;
		dataEnemy->enemy = "             OOOOOOOOO                        OO         OO                    OO             OO                OO                 OO             O                     O           O                       O         O    OOOOO        OOOOO   O       O    O     O      O     O   O      O   O       O    O       O  O     O   O         O  O         O  O    O   O         O  O         O  O   O    O         O  O         O   O  O    O         O  O         O   O O     O         O  O         O    OO      O       O    O       O     OO       O     O      O     O      OO        OOOOO        OOOOO       OO                                 OO                                 OO                                 OO                                 OO                                 O O                         O     O  O     O                   O     O   O     O                 O     O    O      O               O      O     O     O              O      O      O      OOO         OO       O       O       OOOOOOOOOO        O         O                       O           O                     O             OO                 OO                OO             OO                    OO         OO                        OOOOOOOOO             ";
		dataEnemy->width = 35;
		dataEnemy->height = 35;
	}
	break;

	case 11:
	{
		dataEnemy->pos.y = 11;
		dataEnemy->pos.x = 6;
		dataEnemy->enemy = "OO         O         O     O   O     O   O     O  O      O  O     O  O     O   O    O   O    O    O  O     O O      OO       O        O        O        O        O        OO      O O      O       O        O       O        O       O       O       O      OO       ";
		dataEnemy->width = 9;
		dataEnemy->height = 29;
	}
	break;
	
	case 12:
	{
		dataEnemy->pos.y = 11;
		dataEnemy->pos.x = 55;
		dataEnemy->enemy = "       OO      O       O       O   O   O   O    O  O    O  O     O  O    O   O    O   O   O    O   O     O  O      O O       OO        O        O        O        O         O      O O      O  O        O         O        O         O         O           O         OO";
		dataEnemy->width = 9;
		dataEnemy->height = 29;
	}
	break;

	default:
		break;

	}
}
ScreenPrintEnemy(Data_Enemy* enemy)
{
	// 왠지는 모르겠지만 width랑 height를 반대로 넣어야 함. 근데 고치면 어떤 버그가 생길지 모르니 그냥 냅두겠어용

	//ScreenPrintPro(wall->pos.x, wall->pos.y, wall->wall, wall->width, wall->height);
	ScreenPrintProColor(enemy->pos.x, enemy->pos.y, enemy->enemy, enemy->width, enemy->height, ENEMY_COLOR);
}
#pragma endregion EnemyText