#pragma once
//#include "pch.h"
#include "Struct.h"

void InitPQ(PQ* pq);

/// PQNode의 대입 연산자
void PQNodeOperator_Insert(PQNode* node, PQNode* other);

/// PQ에다 PQNode insert
void PushPQLower(PQ* q, PQNode data);
/// PQ에서 PQNode delete
PQNode PopPQLower(PQ* q);

void PushPQUpper(PQ* pq, PQNode data);
PQNode PopPQUpper(PQ* q);

int CheckEmptyPQ(PQ* pq);

PQNode TopPQ(PQ* pq);

/// c 우선순위큐 출처 (AS센터): https://velog.io/@qlwb7187/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0%EC%9A%B0%EC%84%A0%EC%88%9C%EC%9C%84%ED%81%90C