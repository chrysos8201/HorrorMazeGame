#pragma once
#include "Struct.h"
// Queue 출처: https://hellmath.tistory.com/8


void InitQueue(Queue* q);
void ClearQueue(Queue* q);
void PushQueue(Queue* q, Pos pos);
const Pos FrontQueue(Queue* q);
Pos PopQueue(Queue* q);

// 대입연산자
void QueueOperator_Insert(Queue* q, Queue* other);

