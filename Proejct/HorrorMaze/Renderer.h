#pragma once
#include "Define.h"



void ScreenInit();
/// <summary>
/// ȭ�鿡 ������ �ܼ��� ����Ī�ϴ� �Լ�
/// </summary>
void ScreenFlipping();

/// <summary>
/// ��ũ���� �� �������� ����� �Լ�
/// ���� �ܼ��� �� ������ ���� �ַܼ� �ٲپ��ָ鼭 ���� �ܼ��� ������ �����ϰ� ����� �ٽ� ����ϱ� ���� ���
/// </summary>
void ScreenClear();

/// <summary>
/// char* ������ ������ �ֿܼ� ����ϴ� �Լ�
/// x, y�� ����� ������ �ܼ��� ��ġ
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="string"></param>
void ScreenPrint(int x, int y, char* string);
void ScreenPrintColor(int x, int y, char* string, int color);
void ScreenPrintPro(int x, int y, char* string, int height, int width);
void ScreenPrintProColor(int x, int y, wchar_t* string, int height, int width);

void DrawScreen(Player* player, Enemy* enemy);


// �� �׸��� ���� �Լ�
void DrawWall(int index);
void DrawEscapeWall(int index);

// Enemy �׸��� ���� �Լ�
void DrawEnemy(int index);


void InitWallTextData(Data_Wall* wall, int index);
void InitEnemyTextData(Data_Enemy* dataEnemy, int index);
