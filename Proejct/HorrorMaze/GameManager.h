#pragma once
#include "Struct.h"

typedef struct
{
	Player* player;
	Enemy* enemy;
}GameManager;

// �ϳ����� Player�� Enemy�� ����
GameManager* GetInstance();

void MemoryAllClear();
