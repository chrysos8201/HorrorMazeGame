#include "pch.h"
#include "Enemy.h"
#include "Astar.h"
#include "GameManager.h"
#include "Player.h"
#include <time.h>
#include "SoundManager.h"

void Enemy_Update(Enemy* enemy)
{
	Enemy_CheckState(enemy);
	Enemy_SoundState(enemy);
}

void Enemy_SetMoveTimeInterval(Enemy* enemy, float timeInterval)
{
	enemy->moveTimeInterval = timeInterval * 100;
}

void Enemy_Init(Enemy* enemy, Pos pos)
{
	// ���� ������ ���� �ʱ�ȭ
	enemy->soundState = ENEMY_SOUND_BGM;
	enemy->isOnSoundEnemy = false;
	enemy->isOnSoundBGM= false;



	// �ð� ������ �ʱ�ȭ
	Enemy_SetMoveTimeInterval(enemy, ENEMY_INIT_TIME_INTERVAL);
	enemy->oldTime = 0.f;
	enemy->curTime = 0.f;



	enemy->enemyState = IDLE;

	enemy->pos.y = pos.y;
	enemy->pos.x = pos.x;
	Pos oldPos = { 0,0 };
	enemy->oldPlayerPos = oldPos;


	// ȸ�� �ݰ� ����
	Enemy_SetRadiusToFindPlayer(enemy, ENEMY_INIT_RADIUS);

	// �ʱ�ȭ �� �� ���� ��ġ�� dest�� ����
	//Pos randPos = GetRandomPosition();
	enemy->dest.y = pos.y;
	enemy->dest.x = pos.x;


	// ��ã��� ���� �ʱ�ȭ
	enemy->pathMap = createHashMap(HASH_KEY);

	Pos InitPos = { 0,0 };
	for (int i = 0; i < 1000; i++)
	{
		enemy->pathArr[i] = InitPos;
	}
	enemy->pathIndex = 0;
	enemy->pathSize = 0;

	// �ϴ� ���� ������ ����
	Enemy_SetPosition(enemy, GetRandomPosition());
}

void Enemy_SetPosition(Enemy* enemy, Pos dest)	// �� �Լ��� dest������ ��θ� ����� �� �� �̵����� �ʽ��ϴ�~!
{
	// path�� ���ִٸ� �޸� ���� �� ���ο� path�� �޾ƿ�
	if (enemy->pathMap != NULL)
	{
		clearHashMap(enemy->pathMap);
	}

	// �Ű������� tempPosition
	Pos tempPos = { enemy->pos.y, enemy->pos.x };

	/// A* ��ã�� ���� �� pathArr�� �޾ƿ���
	// �ʱ�ȭ
	{
		enemy->pathIndex = 0;
		enemy->pathSize = 0;
		enemy->dest = dest;
	}
	// �� ã��
	enemy->pathMap = Astar(tempPos, dest);
	Pos p = dest;
	while (true)
	{
		enemy->pathArr[enemy->pathIndex] = p;
		Pos parentPos = get(enemy->pathMap, p);
		
		if (PosOperator_IsSame(p, parentPos))
		{
			break;
		}
		p = parentPos;
		enemy->pathIndex++;
		enemy->pathSize++;
	}

	// TODO: reverse �Լ� ���� �� pathIndex���� �ʱ�ȭ �� ���� pathIndex ����� ��
	reverse(enemy->pathArr, enemy->pathSize);			// HashMap�� �ƴ϶� Array�� �ѱ� ��! - �Ǽ���

	// ��ΰ� ������ ���� �̵������ Player�� ���󰥶� ���� �Ȼ���
	enemy->pathIndex = 1;		
	Enemy_Move(enemy);	
}

Pos Enemy_GetPosition(Enemy* enemy)
{
	return enemy->pos;
}

void Enemy_Move(Enemy* enemy)		// �� �Լ��� �̹� �ִ� ��θ� ���� �̵��ϴ� �Լ�
{
	// pathArr�� pathIndex�� ���� ������ �̵�
	enemy->pos = enemy->pathArr[enemy->pathIndex];
	enemy->pathIndex++;
}

void Enemy_State_Move(Enemy* enemy)
{

	// ���� �÷��̾ ã�´�.
	if (Enemy_CheckToFindPlayer(enemy))
	{
		Enemy_SetState(enemy, FIND);
		return;
	}


	// ������ ��ġ���� �����ߴ����� �Ǻ��Ѵ�.
	if (Enemy_CheckIsArrive(enemy))
	{
		// �����Ͽ��� ��� Idle�� �ٲ۴�.
		Enemy_SetState(enemy, IDLE);
	}
	else
	{
		if (enemy->pathSize == 0)	// ��ΰ� ���� ���
		{
			Pos randomPos = GetRandomPosition();
			Enemy_SetPosition(enemy, randomPos);
		}
		else
		{
			// �������� �ʾ��� ��� ��� ������ ��ġ���� �̵�
			Enemy_Move(enemy);
		}
	}
}

void Enemy_CheckState(Enemy* enemy)
{
	switch (Enemy_GetState(enemy))
	{
	case IDLE:
	{
		// 1. �÷��̾ ã�´�. ���� ��� Move�� ����
		if (Enemy_CheckToFindPlayer(enemy))
		{
			Enemy_SetState(enemy, FIND);
		}
		else if (Enemy_CheckIsArrive(enemy))
		{
			Enemy_SetSoundState(enemy, ENEMY_SOUND_BGM);
			// �����Ͽ��� ��� �������������� �ٲ۴�.
			Pos randomPos = GetRandomPosition();
			Enemy_SetPosition(enemy, randomPos);
			Enemy_SetState(enemy, MOVE);
		}
		else
		{
			Enemy_SetState(enemy, ENEMY_SOUND_BGM);
			Enemy_SetState(enemy, MOVE);
		}
	}
	break;
	case MOVE:
	{
		enemy->curTime = clock() / 10;

		if (enemy->curTime - enemy->oldTime >= enemy->moveTimeInterval)
		{
			Enemy_State_Move(enemy);
			enemy->oldTime = enemy->curTime;
		}
		return;
	}
	break;

	case FIND:
	{
		Enemy_SetSoundState(enemy, ENEMY_SOUND_ENEMY);
		// sound ���
		/*if (enemy->isMusicOn == false)
		{
			SoundManager_PlaySound(SOUND_ENEMY);
			enemy->isMusicOn = true;
		}*/
		//Enemy_PlaySound(SOUND_ENEMY);
		// �÷��̾��� ��ġ�� ��������
		Enemy_SetPosition(enemy, Player_GetPosition(GetInstance()->player));
		// Move �� ����
		Enemy_SetState(enemy, MOVE);
	}
	break;

	default:
	break;
	}
}


void Enemy_SetState(Enemy* enemy, enum E_EnemyState state)
{
	enemy->enemyState = state;
}

enum E_EnemyState Enemy_GetState(Enemy* enemy)
{
	return enemy->enemyState;
}


// ���� ���� Player�� �ִ����� �˻��Ѵ�.
// ���� ���� ���� Player�� �־ ���� ã�� ��ġ�� ���ٸ� false�� ��ȯ�Ѵ�.
bool Enemy_CheckToFindPlayer(Enemy* enemy)
{
	// TODO: �ֺ� �������� Player�� ã�´�. ã�� ��� true ��ȯ
	int radius = enemy->radiusToFindPlayer;

	Pos currentPosition = enemy->pos;
	Pos playerPosition = Player_GetPosition(GetInstance()->player);

	if (PosOperator_IsSame(enemy->oldPlayerPos, playerPosition))
	{
		// Player�� �̹� ã�Ҵµ� ���� ��ġ�� ���� ���
		//Enemy_StopSound(enemy);
		return false;
	}
	
	// �� ���� ����� Pos�� �˻��ص� ���� ������ ������ ��.
	for (int y = currentPosition.y - radius; y <= currentPosition.y + radius; y++)
	{
		for (int x = currentPosition.x - radius; x <= currentPosition.x + radius; x++)
		{
			int nx = x - currentPosition.x;
			int ny = y - currentPosition.y;
			if ((nx * nx + ny * ny) <= radius * radius + radius / 1.3)
			{
				// Player�� Pos�� ��ġ�� ��� true ��ȯ
				if (y == playerPosition.y && x == playerPosition.x)
				{
					// ã�� Player�� ���� ��ġ ����
					enemy->oldPlayerPos = playerPosition;
					return true;
				}
			}
		}
	}
	return false;
}

void Enemy_SetRadiusToFindPlayer(Enemy* enemy, int radius)
{
	enemy->radiusToFindPlayer = radius;
}

bool Enemy_CheckIsArrive(Enemy* enemy)
{
	return PosOperator_IsSame(enemy->pos, enemy->dest);
}

Pos GetRandomPosition()
{
	// TODO : ���� �������� �޾ƿ;� �Ѵ�.
	Pos randomPos = { 0,0 };
	int randomY = rand() % HEIGHT;
	int randomX = rand() % WIDTH;
	randomPos.y = randomY;
	randomPos.x = randomX;
	while (true)
	{
		if (IsWall(randomPos) == false)	//���� ���� ���
			break;
		else
		{
			// TODO: �ٽ� ���� �� �̱�;
			randomY = rand() % HEIGHT;
			randomX = rand() % WIDTH;
			randomPos.y = randomY;
			randomPos.x = randomX;
		}
	}
	return randomPos;
}

void Enemy_Delete(Enemy* enemy)
{
	clearHashMap(enemy->pathMap);
}

void Enemy_SoundState(Enemy* enemy)
{
	switch (enemy->soundState)
	{
	case ENEMY_SOUND_BGM:
	{
		if (enemy->isOnSoundBGM == false)
		{
			enemy->isOnSoundEnemy = false;
			SoundManager_StopSound(SOUND_ENEMY);
			SoundManager_PlaySound(SOUND_BGM);
			enemy->isOnSoundBGM = true;
		}
	}
	break;
	case ENEMY_SOUND_ENEMY:
	{
		if (enemy->isOnSoundEnemy == false)
		{
			enemy->isOnSoundBGM = false;
			SoundManager_StopSound(SOUND_BGM);
			SoundManager_PlaySound(SOUND_ENEMY);
			enemy->isOnSoundEnemy = true;
		}
	}
	break;
	default:
		break;
	}
}

void Enemy_SetSoundState(Enemy* enemy, enum E_ENEMY_CURRENT_SOUND state)
{
	enemy->soundState = state;
}



