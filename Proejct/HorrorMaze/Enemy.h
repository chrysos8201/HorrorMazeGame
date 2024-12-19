#pragma once
#include "Struct.h"
#include "Define.h"



enum E_EnemyState
{
	IDLE = 0,	// Idle�� ������ Pos���� �̵��Ͽ��� ��� ���� �ൿ ������ ���� State
	MOVE,
	FIND,
};

// Enemy�� Update�Լ�
void Enemy_Update(Enemy* enemy);


// Enemy�� checkState�� �ð� ������ �����Ѵ�.
void Enemy_SetMoveTimeInterval(Enemy* enemy, float timeInterval);

// Enemy�� �ʱ�ȭ �ϰ� ������ �����ǿ� �����Ѵ�.
void Enemy_Init(Enemy* enemy, Pos pos);

// Enemy�� ������ ��ġ�� A*�� ���� ã�´�.
void Enemy_SetPosition(Enemy* enemy, Pos pos);

Pos Enemy_GetPosition(Enemy* enemy);

// Enemy�� ���� ��ġ�� ������. (path���� ���� ��)
void Enemy_Move(Enemy* enemy);

// Enemy�� ���� State�� üũ
void Enemy_CheckState(Enemy* enemy);

// Enemy�� State Get,Set 
void Enemy_SetState(Enemy* enemy,enum E_EnemyState state);
enum E_EnemyState Enemy_GetState(Enemy* enemy);

// Enemy �ֺ� ���� ���� �÷��̾ �ִ����� �˻��Ѵ�.
bool Enemy_CheckToFindPlayer(Enemy* enemy);
bool Enemy_CheckToFindPlayer_SOUND(Enemy* enemy);


// Enemy�� ȸ�� �ݰ��� �����Ѵ�.
void Enemy_SetRadiusToFindPlayer(Enemy* enemy, int radius);

// Enemy�� ������ ��ġ(dest)���� �����ߴ����� �Ǻ�
bool Enemy_CheckIsArrive(Enemy* enemy);

// ���� ������ ���� �޾ƿ´�.
Pos GetRandomPosition();

// Enemy�� �޸� ����
void Enemy_Delete(Enemy* enemy);

// ���� Enemy���� BGM�� �÷��̵ǰ� �ִ����� �˻��Ͽ� ������ ����Ѵ�.

void Enemy_SoundState(Enemy* enemy);

void Enemy_SetSoundState(Enemy* enemy, enum E_ENEMY_CURRENT_SOUND state);
