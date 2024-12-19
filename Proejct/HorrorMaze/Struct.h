#pragma once
#include "Define.h"

typedef long long mclock;	// �ð��� ����ϴ� Ÿ��

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

// �ؽø� ��Ʈ�� ����ü
typedef struct Entry {
	struct Entry* next; // Chaining Map�� ���� ������
	Pos key;
	Pos value;
} Entry;

// �ؽø� ����ü
typedef struct HashMap {
	Entry** table; // Chaining Map�� ���� ������ �迭
	int size; // �ؽø� ũ��
} HashMap;


#pragma region Scene
enum E_Scene
{
	E_SCENE_MENU,
	E_SCENE_GAME,
	E_SCENE_GAMEOVER,
	E_SCENE_GAMECLEAR,
};

enum E_Scene currentScene;		// ���� ��
#pragma endregion Scene







// Player
typedef struct
{
	// �ð�
	mclock moveTimeInterval;		// �����̱� ���� �ʿ��� �ð�
	mclock oldTime;
	mclock curTime;

	mclock rotateTimeInterval;		// ȸ���ϱ� ���� �ʿ��� �ð�
	mclock oldRotateTime;
	mclock curRotateTime;

	enum E_Dir dir;
	Pos pos;
}Player;


// Enemy
typedef struct
{
	enum E_EnemyState enemyState;

	// �ð�
	mclock moveTimeInterval;		// �����̱� ���� �ʿ��� �ð�
	mclock oldTime;
	mclock curTime;

	// ���� Pos
	Pos pos;

	// ������ Pos
	Pos dest;

	// ���� �÷��̾��� ��ġ�� ����ϱ� ���� Pos
	Pos oldPlayerPos;

	// ��ã��� ����
	HashMap* pathMap;

	Pos pathArr[1000];	// ���� ��ġ���� ������������ ��θ� ������
	int pathIndex;		// ���� �ε��� ����
	int pathSize;		// ���� pathArr�� �󸶳� ���ִ��� ������ ����

	// Ž�� �ݰ�
	int radiusToFindPlayer;

	// ���� �ѹ��� ����ϱ� ���� üũ�ϴ� ����
	enum E_ENEMY_CURRENT_SOUND soundState;
	bool isOnSoundEnemy;
	bool isOnSoundBGM;

}Enemy;


// Wall�� ��ġ�� ���� �׸� ������
typedef struct  
{
	Pos pos;			//  �� Pos�� ȭ�鿡 ǥ���ϱ� ���� Pos�� (�ʿ� ������� ����)
	int size;
	char* wall;
	int width, height;
}Data_Wall;

// Enemy�� ��ġ�� ���� �׸� ������
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
