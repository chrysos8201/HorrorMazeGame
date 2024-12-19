#pragma once
#include "Define.h"



void ScreenInit();
/// <summary>
/// 화면에 보여줄 콘솔을 스위칭하는 함수
/// </summary>
void ScreenFlipping();

/// <summary>
/// 스크린을 빈 공간으로 지우는 함수
/// 현재 콘솔을 다 쓰고나면 다음 콘솔로 바꾸어주면서 이전 콘솔의 내용은 깨끗하게 지우고 다시 출력하기 위해 사용
/// </summary>
void ScreenClear();

/// <summary>
/// char* 버퍼의 내용을 콘솔에 출력하는 함수
/// x, y는 출력을 시작할 콘솔의 위치
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="string"></param>
void ScreenPrint(int x, int y, char* string);
void ScreenPrintColor(int x, int y, char* string, int color);
void ScreenPrintPro(int x, int y, char* string, int height, int width);
void ScreenPrintProColor(int x, int y, wchar_t* string, int height, int width);

void DrawScreen(Player* player, Enemy* enemy);


// 벽 그리기 위한 함수
void DrawWall(int index);
void DrawEscapeWall(int index);

// Enemy 그리기 위한 함수
void DrawEnemy(int index);


void InitWallTextData(Data_Wall* wall, int index);
void InitEnemyTextData(Data_Enemy* dataEnemy, int index);
