#pragma once
#include "Struct.h"
#include "Define.h"



enum E_EnemyState
{
	IDLE = 0,	// Idle은 지정한 Pos까지 이동하였을 경우 다음 행동 지정을 위한 State
	MOVE,
	FIND,
};

// Enemy의 Update함수
void Enemy_Update(Enemy* enemy);


// Enemy의 checkState의 시간 간격을 설정한다.
void Enemy_SetMoveTimeInterval(Enemy* enemy, float timeInterval);

// Enemy를 초기화 하고 지정한 포지션에 생성한다.
void Enemy_Init(Enemy* enemy, Pos pos);

// Enemy의 지정한 위치를 A*로 길을 찾는다.
void Enemy_SetPosition(Enemy* enemy, Pos pos);

Pos Enemy_GetPosition(Enemy* enemy);

// Enemy를 다음 위치로 보낸다. (path에서 꺼낼 것)
void Enemy_Move(Enemy* enemy);

// Enemy의 현재 State를 체크
void Enemy_CheckState(Enemy* enemy);

// Enemy의 State Get,Set 
void Enemy_SetState(Enemy* enemy,enum E_EnemyState state);
enum E_EnemyState Enemy_GetState(Enemy* enemy);

// Enemy 주변 범위 내의 플레이어가 있는지를 검사한다.
bool Enemy_CheckToFindPlayer(Enemy* enemy);
bool Enemy_CheckToFindPlayer_SOUND(Enemy* enemy);


// Enemy의 회전 반경을 설정한다.
void Enemy_SetRadiusToFindPlayer(Enemy* enemy, int radius);

// Enemy가 지정한 위치(dest)까지 도착했는지를 판별
bool Enemy_CheckIsArrive(Enemy* enemy);

// 랜덤 포지션 값을 받아온다.
Pos GetRandomPosition();

// Enemy의 메모리 해제
void Enemy_Delete(Enemy* enemy);

// 현재 Enemy전용 BGM이 플레이되고 있는지를 검사하여 음악을 재생한다.

void Enemy_SoundState(Enemy* enemy);

void Enemy_SetSoundState(Enemy* enemy, enum E_ENEMY_CURRENT_SOUND state);
