#pragma once
#include "Struct.h"


// �ؽø� �ʱ�ȭ �Լ�
HashMap* createHashMap(int size);

// �ؽ� �� ��� �Լ�
int hash(Pos key);

// ��Ʈ�� �߰� �Լ�
void put(HashMap* map, Pos key, Pos value);

// Value ��ȯ �Լ�
Pos get(HashMap* map, Pos key);

// �ؽø� �޸� ���� �Լ�
void clearHashMap(HashMap* map);


// ��ó: GPT