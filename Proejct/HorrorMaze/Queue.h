#pragma once
#include "Struct.h"
// Queue ��ó: https://hellmath.tistory.com/8


void InitQueue(Queue* q);
void ClearQueue(Queue* q);
void PushQueue(Queue* q, Pos pos);
const Pos FrontQueue(Queue* q);
Pos PopQueue(Queue* q);

// ���Կ�����
void QueueOperator_Insert(Queue* q, Queue* other);

