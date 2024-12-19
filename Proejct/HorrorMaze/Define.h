#pragma once


#define INT32_MAX 2147483647
#define bool  _Bool
#define false 0
#define true  1


// Update문 관리
#define FIXED_UPDATE_TIME (1.0f / 60.0f)


#define MAX_PQ_ELEMENT 500
#define MAX_QUEUE_ELEMENT 500
#define HASH_KEY 10007 // 소수를 사용하는 것이 해시 충돌을 최소화할 수 있음 by GPT



// 맵의 크기
#define WIDTH 40
#define HEIGHT 40

///////////////////////// Player ////////////////////////////////

// 플레이어의 시야 처리의 갯수 관리
#define FIND_INDEX 15

// 플레이어의 이동 속도
#define PLAYER_INIT_MOVE_TIME_INTERVAL 0.3f
// 플레이어의 회전 속도
#define PLAYER_INIT_ROTATE_TIME_INTERVAL 0.3f

// 적과 벽의 색 결정
#define ENEMY_COLOR FOREGROUND_RED
#define	WALL_COLOR FOREGROUND_GREEN




///////////////////////// Enemy ///////////////////////////////s/

// Enemy 초기화
#define ENEMY_INIT_RADIUS 10		// Player를 찾기 위한 범위
#define ENEMY_INIT_TIME_INTERVAL 0.82	// Enemy가 움직이는 시간 사이의 간격