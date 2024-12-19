#pragma once


#define INT32_MAX 2147483647
#define bool  _Bool
#define false 0
#define true  1


// Update�� ����
#define FIXED_UPDATE_TIME (1.0f / 60.0f)


#define MAX_PQ_ELEMENT 500
#define MAX_QUEUE_ELEMENT 500
#define HASH_KEY 10007 // �Ҽ��� ����ϴ� ���� �ؽ� �浹�� �ּ�ȭ�� �� ���� by GPT



// ���� ũ��
#define WIDTH 40
#define HEIGHT 40

///////////////////////// Player ////////////////////////////////

// �÷��̾��� �þ� ó���� ���� ����
#define FIND_INDEX 15

// �÷��̾��� �̵� �ӵ�
#define PLAYER_INIT_MOVE_TIME_INTERVAL 0.3f
// �÷��̾��� ȸ�� �ӵ�
#define PLAYER_INIT_ROTATE_TIME_INTERVAL 0.3f

// ���� ���� �� ����
#define ENEMY_COLOR FOREGROUND_RED
#define	WALL_COLOR FOREGROUND_GREEN




///////////////////////// Enemy ///////////////////////////////s/

// Enemy �ʱ�ȭ
#define ENEMY_INIT_RADIUS 10		// Player�� ã�� ���� ����
#define ENEMY_INIT_TIME_INTERVAL 0.82	// Enemy�� �����̴� �ð� ������ ����