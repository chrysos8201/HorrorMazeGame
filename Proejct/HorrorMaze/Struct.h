#pragma once
#include "Define.h"

typedef long long mclock;	// 시간에 사용하는 타입

enum E_Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4
};

typedef struct
{
	int y, x;
} Pos;

typedef struct
{
	int f, g;
	Pos pos;
}PQNode;

typedef struct
{
	Pos queue[MAX_QUEUE_ELEMENT];
	int front, rear, queue_size;
}Queue;

typedef struct
{
	PQNode heap[MAX_PQ_ELEMENT];
	int heap_size;
}PQ;

// 해시맵 엔트리 구조체
typedef struct Entry {
	struct Entry* next; // Chaining Map을 위한 포인터
	Pos key;
	Pos value;
} Entry;

// 해시맵 구조체
typedef struct HashMap {
	Entry** table; // Chaining Map을 위한 포인터 배열
	int size; // 해시맵 크기
} HashMap;


#pragma region Scene
enum E_Scene
{
	E_SCENE_MENU,
	E_SCENE_GAME,
	E_SCENE_GAMEOVER,
	E_SCENE_GAMECLEAR,
};

enum E_Scene currentScene;		// 현재 씬
#pragma endregion Scene







// Player
typedef struct
{
	// 시간
	mclock moveTimeInterval;		// 움직이기 위해 필요한 시간
	mclock oldTime;
	mclock curTime;

	mclock rotateTimeInterval;		// 회전하기 위해 필요한 시간
	mclock oldRotateTime;
	mclock curRotateTime;

	enum E_Dir dir;
	Pos pos;
}Player;


// Enemy
typedef struct
{
	enum E_EnemyState enemyState;

	// 시간
	mclock moveTimeInterval;		// 움직이기 위해 필요한 시간
	mclock oldTime;
	mclock curTime;

	// 현재 Pos
	Pos pos;

	// 목적지 Pos
	Pos dest;

	// 이전 플레이어의 위치를 기록하기 위한 Pos
	Pos oldPlayerPos;

	// 길찾기용 변수
	HashMap* pathMap;

	Pos pathArr[1000];	// 현재 위치부터 목적지까지의 경로를 저장함
	int pathIndex;		// 현재 인덱스 관리
	int pathSize;		// 현재 pathArr에 얼마나 차있는지 저장할 변수

	// 탐지 반경
	int radiusToFindPlayer;

	// 사운드 한번만 출력하기 위해 체크하는 변수
	enum E_ENEMY_CURRENT_SOUND soundState;
	bool isOnSoundEnemy;
	bool isOnSoundBGM;

}Enemy;


// Wall의 위치에 따른 그림 데이터
typedef struct  
{
	Pos pos;			//  이 Pos는 화면에 표시하기 위한 Pos임 (맵에 사용하지 않음)
	int size;
	char* wall;
	int width, height;
}Data_Wall;

// Enemy의 위치에 따른 그림 데이터
typedef struct  
{
	Pos pos;
	int size;
	char* enemy;
	int width, height;
}Data_Enemy;


// SoundData
enum E_Sound
{
	SOUND_FOOTSTEP,
	SOUND_BGM,
	SOUND_ENEMY,
	SOUND_GAMEOVER,
	SOUND_COUNT = 5,	// + 1
};

enum E_ENEMY_CURRENT_SOUND
{
	ENEMY_SOUND_BGM,
	ENEMY_SOUND_ENEMY,
};
//#define SOUND_COUNT 5
