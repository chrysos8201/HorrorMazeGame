#pragma once
#include "Struct.h"


// 해시맵 초기화 함수
HashMap* createHashMap(int size);

// 해시 값 계산 함수
int hash(Pos key);

// 엔트리 추가 함수
void put(HashMap* map, Pos key, Pos value);

// Value 반환 함수
Pos get(HashMap* map, Pos key);

// 해시맵 메모리 해제 함수
void clearHashMap(HashMap* map);


// 출처: GPT