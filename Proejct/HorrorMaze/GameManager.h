#pragma once
#include "Struct.h"

typedef struct
{
	Player* player;
	Enemy* enemy;
}GameManager;

// 하나씩의 Player와 Enemy를 만듦
GameManager* GetInstance();

void MemoryAllClear();
