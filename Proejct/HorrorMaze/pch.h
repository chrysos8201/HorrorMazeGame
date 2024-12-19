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

// 전체 맵
int map[HEIGHT][WIDTH];

// 최저 코스트 갱신
int best[HEIGHT][WIDTH];

//출력용 queue
#pragma endregion Astar

// 만든 맵을 불러옴
void InitMap();

// Pos 비교 연산자
int PosOperator_IsSame(Pos pos, Pos other);

// 벽 체크용 함수
bool IsWall(Pos pos);

// Pos 배열 뒤집기 - Astar에서 사용 중
void reverse(Pos arr[], int size);

