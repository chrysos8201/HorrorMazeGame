#include "pch.h"
#include "Player.h"
#include "Enemy.h"
#include <Windows.h>
#include <time.h>
#include "Renderer.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "Define.h"

#define FIXED_UPDATE_TIME (1.0f / 60.0f)

const int pdy[] = { -1, 0, 1, 0 };
const int pdx[] = { 0, -1, 0, 1 };


// �þ� üũ�� ���� ���� ����
const int sdy[FIND_INDEX] = { -3, -3, -3, -3, -3,
							  -2, -2, -2, -2, -2,
								  -1, -1, -1,
								   0,      0 };
const int sdx[FIND_INDEX] = { -2, 2, -1, 1, 0,
							  -2, 2, -1, 1, 0,
							     -1,  1, 0,
							     -1,     1 };


void Player_Update(Player* player)
{
	// Player�� �þ� üũ��
	Player_Sight(player);

	// �Ʒ� �ð� ���� �������� �Է� ��� �ð��� ���� ��
	player->curTime = clock() / 10;
	if (player->curTime - player->oldTime >= player->moveTimeInterval)
	{
		Player_KeyProcessMove(player);
		player->oldTime = player->curTime;
	}

	player->curRotateTime = clock() / 10;
	if (player->curRotateTime - player->oldRotateTime >= player->rotateTimeInterval)
	{
		Player_KeyProcessRotate(player);
		player->oldRotateTime = player->curRotateTime;
	}
}

void Player_FixedUpdate(Player* player)
{
	float elapsed_time = 0.0f;
	float fixed_update_timer = 0.0f;

	mclock old_time = clock();

	while (1) {
		// ������Ʈ �ֱ⸦ �����.
		mclock new_time = clock();
		float delta_time = (float)(new_time - old_time) / CLOCKS_PER_SEC;
		old_time = new_time;
		elapsed_time += delta_time;
		fixed_update_timer += delta_time;

		// ������ �ֱ⿡ �°� �Լ��� ȣ���Ѵ�.
		if (fixed_update_timer >= FIXED_UPDATE_TIME) {
			//printf("Fixed Update - elapsed time: %f\n", elapsed_time);
			Player_KeyProcessMove(player);
			fixed_update_timer -= FIXED_UPDATE_TIME;
		}

		//if (elapsed_time >= 5.0f) break;
	}
}

void Player_SetMoveTimeInterval(Player* player, float timeInterval)
{
	player->moveTimeInterval = timeInterval * 100;
}
void Player_SetRotateTimeInterval(Player* player, float timeInterval)
{
	player->rotateTimeInterval = timeInterval * 100;
}



void Player_Init(Player* player, Pos pos)
{

	// �ð� ������ �ʱ�ȭ
	Player_SetMoveTimeInterval(player, PLAYER_INIT_MOVE_TIME_INTERVAL);
	player->oldTime = 0;
	player->curTime = 0;

	Player_SetRotateTimeInterval(player, PLAYER_INIT_ROTATE_TIME_INTERVAL);
	player->oldRotateTime = 0;
	player->curRotateTime = 0;


	// �ٶ󺸴� ����
	player->dir = DIR_RIGHT;

	// ��ġ
	player->pos.y = pos.y;
	player->pos.x = pos.x;
}

void Player_KeyProcessRotate(Player* player)
{
	/// Rotate
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) || (GetAsyncKeyState(0x41) & 0x8001))
	{
		player->dir = (player->dir + 1) % DIR_COUNT;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) || (GetAsyncKeyState(0x44) & 0x8001))
	{
		player->dir = (player->dir - 1 + DIR_COUNT) % DIR_COUNT;
	}
}

void Player_KeyProcessMove(Player* player)
{
	bool isMusicOn = false;
	/// Move Forward or Back
	if ((GetAsyncKeyState(VK_UP) & 0x8001))
	{
		SoundManager_StopEffect();
		SoundManager_PlayEffect(SOUND_FOOTSTEP);
		Pos np;
		np.y = player->pos.y + pdy[player->dir];
		np.x = player->pos.x + pdx[player->dir];
		Player_CheckGameClear(np);
		if (!IsWall(np)) 
		{
			Player_SetPosition(player, np);
		}
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0x8001))
	{
		SoundManager_StopEffect();
		SoundManager_PlayEffect(SOUND_FOOTSTEP);
		Pos np;
		np.y = player->pos.y - pdy[player->dir];
		np.x = player->pos.x - pdx[player->dir];
		Player_CheckGameClear(np);
		if (!IsWall(np))
		{
			Player_SetPosition(player, np);
		}
	}
}

Pos Player_GetPosition(Player* player)
{
	return player->pos;
}

void Player_SetPosition(Player* player, Pos nextpos)
{
	player->pos = nextpos;
}

void Player_Sight(Player* player)
{
	for (int i = 0; i < FIND_INDEX; i++)
	{
		Pos cp = player->pos;

		switch (player->dir)
		{
		case DIR_UP:
		{
			cp.y = cp.y + sdy[i];
			cp.x = cp.x + sdx[i];
		}
		break;
		case DIR_LEFT:
		{
			cp.y = cp.y - sdx[i];
			cp.x = cp.x + sdy[i];
		}
		break;
		case DIR_DOWN:
		{
			cp.y = cp.y - sdy[i];
			cp.x = cp.x - sdx[i];
		}
		break;
		case DIR_RIGHT:
		{
			cp.y = cp.y + sdx[i];
			cp.x = cp.x - sdy[i];
		}
		break;
		}
		// �� ������ üũ
		if (cp.y < 0 || cp.y > HEIGHT - 1 || cp.x < 0 || cp.x > WIDTH - 1) continue;

		// ���� ���� ������ �� ��ġ�� �� ���
		if (IsWall(cp))
		{
			// Ż�ⱸ�̸� �ٸ� ������ ���
			if (map[cp.y][cp.x] == 2)
			{
				DrawEscapeWall(i);
			}
			else
			{
				DrawWall(i);
			}
		}
		// Enemy ��ġ üũ
		if (PosOperator_IsSame(cp, Enemy_GetPosition(GetInstance()->enemy)))
		{
			DrawEnemy(i);
		}
	}
	// ���� ����
	ScreenFlipping();
}


void Player_CheckGameClear(Pos pos)
{
	if (map[pos.y][pos.x] == 2)
	{
		currentScene = E_SCENE_GAMECLEAR;
	}
}