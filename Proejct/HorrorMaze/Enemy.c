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
	// 사운드 관리용 변수 초기화
	enemy->soundState = ENEMY_SOUND_BGM;
	enemy->isOnSoundEnemy = false;
	enemy->isOnSoundBGM= false;



	// 시간 관리용 초기화
	Enemy_SetMoveTimeInterval(enemy, ENEMY_INIT_TIME_INTERVAL);
	enemy->oldTime = 0.f;
	enemy->curTime = 0.f;



	enemy->enemyState = IDLE;

	enemy->pos.y = pos.y;
	enemy->pos.x = pos.x;
	Pos oldPos = { 0,0 };
	enemy->oldPlayerPos = oldPos;


	// 회전 반경 설정
	Enemy_SetRadiusToFindPlayer(enemy, ENEMY_INIT_RADIUS);

	// 초기화 할 때 현재 위치를 dest로 설정
	//Pos randPos = GetRandomPosition();
	enemy->dest.y = pos.y;
	enemy->dest.x = pos.x;


	// 길찾기용 변수 초기화
	enemy->pathMap = createHashMap(HASH_KEY);

	Pos InitPos = { 0,0 };
	for (int i = 0; i < 1000; i++)
	{
		enemy->pathArr[i] = InitPos;
	}
	enemy->pathIndex = 0;
	enemy->pathSize = 0;

	// 일단 랜덤 포지션 생성
	Enemy_SetPosition(enemy, GetRandomPosition());
}

void Enemy_SetPosition(Enemy* enemy, Pos dest)	// 이 함수는 dest까지의 경로를 만들어 줄 뿐 이동하지 않습니다~!
{
	// path가 차있다면 메모리 해제 후 새로운 path를 받아옴
	if (enemy->pathMap != NULL)
	{
		clearHashMap(enemy->pathMap);
	}

	// 매개변수용 tempPosition
	Pos tempPos = { enemy->pos.y, enemy->pos.x };

	/// A* 길찾기 시작 및 pathArr에 받아오기
	// 초기화
	{
		enemy->pathIndex = 0;
		enemy->pathSize = 0;
		enemy->dest = dest;
	}
	// 길 찾기
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

	// TODO: reverse 함수 구현 후 pathIndex으로 초기화 및 현재 pathIndex 기억할 것
	reverse(enemy->pathArr, enemy->pathSize);			// HashMap이 아니라 Array를 넘길 것! - 실수함

	// 경로가 생기자 마자 이동해줘야 Player를 따라갈때 텀이 안생김
	enemy->pathIndex = 1;		
	Enemy_Move(enemy);	
}

Pos Enemy_GetPosition(Enemy* enemy)
{
	return enemy->pos;
}

void Enemy_Move(Enemy* enemy)		// 이 함수는 이미 있는 경로를 따라 이동하는 함수
{
	// pathArr에 pathIndex의 값을 꺼내와 이동
	enemy->pos = enemy->pathArr[enemy->pathIndex];
	enemy->pathIndex++;
}

void Enemy_State_Move(Enemy* enemy)
{

	// 먼저 플레이어를 찾는다.
	if (Enemy_CheckToFindPlayer(enemy))
	{
		Enemy_SetState(enemy, FIND);
		return;
	}


	// 지정한 위치까지 도착했는지를 판별한다.
	if (Enemy_CheckIsArrive(enemy))
	{
		// 도착하였을 경우 Idle로 바꾼다.
		Enemy_SetState(enemy, IDLE);
	}
	else
	{
		if (enemy->pathSize == 0)	// 경로가 없을 경우
		{
			Pos randomPos = GetRandomPosition();
			Enemy_SetPosition(enemy, randomPos);
		}
		else
		{
			// 도착하지 않았을 경우 계속 지정한 위치까지 이동
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
		// 1. 플레이어를 찾는다. 없을 경우 Move로 변경
		if (Enemy_CheckToFindPlayer(enemy))
		{
			Enemy_SetState(enemy, FIND);
		}
		else if (Enemy_CheckIsArrive(enemy))
		{
			Enemy_SetSoundState(enemy, ENEMY_SOUND_BGM);
			// 도착하였을 경우 랜덤포지션으로 바꾼다.
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
		// sound 출력
		/*if (enemy->isMusicOn == false)
		{
			SoundManager_PlaySound(SOUND_ENEMY);
			enemy->isMusicOn = true;
		}*/
		//Enemy_PlaySound(SOUND_ENEMY);
		// 플레이어의 위치를 가져오고
		Enemy_SetPosition(enemy, Player_GetPosition(GetInstance()->player));
		// Move 로 변경
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


// 범위 내에 Player가 있는지를 검사한다.
// 만약 범위 내의 Player가 있어도 이전 찾은 위치와 같다면 false를 반환한다.
bool Enemy_CheckToFindPlayer(Enemy* enemy)
{
	// TODO: 주변 범위에서 Player를 찾는다. 찾을 경우 true 반환
	int radius = enemy->radiusToFindPlayer;

	Pos currentPosition = enemy->pos;
	Pos playerPosition = Player_GetPosition(GetInstance()->player);

	if (PosOperator_IsSame(enemy->oldPlayerPos, playerPosition))
	{
		// Player를 이미 찾았는데 이전 위치와 같을 경우
		//Enemy_StopSound(enemy);
		return false;
	}
	
	// 맵 밖을 벗어나는 Pos를 검사해도 딱히 문제는 없을듯 함.
	for (int y = currentPosition.y - radius; y <= currentPosition.y + radius; y++)
	{
		for (int x = currentPosition.x - radius; x <= currentPosition.x + radius; x++)
		{
			int nx = x - currentPosition.x;
			int ny = y - currentPosition.y;
			if ((nx * nx + ny * ny) <= radius * radius + radius / 1.3)
			{
				// Player의 Pos와 일치할 경우 true 반환
				if (y == playerPosition.y && x == playerPosition.x)
				{
					// 찾은 Player의 이전 위치 갱신
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
	// TODO : 랜덤 포지션을 받아와야 한다.
	Pos randomPos = { 0,0 };
	int randomY = rand() % HEIGHT;
	int randomX = rand() % WIDTH;
	randomPos.y = randomY;
	randomPos.x = randomX;
	while (true)
	{
		if (IsWall(randomPos) == false)	//벽이 없을 경우
			break;
		else
		{
			// TODO: 다시 랜덤 값 뽑기;
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



