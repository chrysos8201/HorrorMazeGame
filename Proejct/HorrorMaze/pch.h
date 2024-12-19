#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#include "Define.h"
#include "GameManager.h"

#include "Struct.h"
#include "MyError.h"
#include "PriorityQueue.h"
#include "Queue.h"
#include "HashMap.h"

#include "Astar.h"





#pragma region Astar

// ��ü ��
int map[HEIGHT][WIDTH];

// ���� �ڽ�Ʈ ����
int best[HEIGHT][WIDTH];

//��¿� queue
#pragma endregion Astar

// ���� ���� �ҷ���
void InitMap();

// Pos �� ������
int PosOperator_IsSame(Pos pos, Pos other);

// �� üũ�� �Լ�
bool IsWall(Pos pos);

// Pos �迭 ������ - Astar���� ��� ��
void reverse(Pos arr[], int size);

