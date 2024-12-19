#pragma once
#include "Struct.h"



void Player_Update(Player* player);

void Player_FixedUpdate(Player* player);

void Player_SetMoveTimeInterval(Player* player, float timeInterval);

void Player_SetRotateTimeInterval(Player* player, float timeInterval);


// Player�� ����� ��ġ�� �����Ѵ�.
void Player_Init(Player* player, Pos pos);

void Player_KeyProcessMove(Player* player);
void Player_KeyProcessRotate(Player* player);
Pos  Player_GetPosition(Player* player);

void Player_SetPosition(Player* player, Pos nextpos);

// �÷��̾��� �þ߿� ���̴� ���� Ȯ�� �� ����Ѵ�.
void Player_Sight(Player* player);

void Player_CheckGameClear(Pos pos);
