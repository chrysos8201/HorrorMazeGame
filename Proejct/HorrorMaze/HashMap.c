#include "pch.h"
//#include "HashMap.h"

// 해시맵 초기화 함수
HashMap* createHashMap(int size) {
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	map->table = (Entry**)calloc(size, sizeof(Entry*));
	map->size = size;
	return map;
}

// 해시 값 계산 함수
int hash(Pos key) {
	// Key 값을 적절히 변형하여 리턴
	return ((key.y * 31) + key.x) % HASH_KEY;
}

// 엔트리 추가 함수
void put(HashMap* map, Pos key, Pos value) {
	int index = hash(key);
	Entry* entry = map->table[index];
	// Chaining Map 방식을 사용하여 해시 충돌 처리
	while (entry != NULL) {
		if (entry->key.y == key.y && entry->key.x == key.x) {
			// Key가 이미 존재하면 Value를 갱신
			entry->value.y = value.y;
			entry->value.x = value.x;
			return;
		}
		entry = entry->next;
	}
	// 새로운 Key와 Value를 추가해주기 위해 Entry 구조체 생성
	entry = (Entry*)malloc(sizeof(Entry));
	entry->key = key;
	entry->value.y = value.y;
	entry->value.x = value.x;
	entry->next = map->table[index];
	map->table[index] = entry;
}

// Value 반환 함수
Pos get(HashMap* map, Pos key) {
	int index = hash(key);
 	Entry* entry = map->table[index];
	while (entry != NULL) {
		if (entry->key.y == key.y && entry->key.x == key.x) {
			//Pos ret = entry->value;
			return entry->value; // Key에 대응하는 Value를 리턴
		}
		entry = entry->next;
	}
	Pos ret = { -1,-1 };
	return ret; // Key가 존재하지 않으면 -1 리턴
}

// 해시맵 메모리 해제 함수
void clearHashMap(HashMap* map) {
	for (int i = 0; i < map->size; i++) {
		//if (map == NULL) break;
		Entry* entry = map->table[i];
		while (entry != NULL) {
			Entry* temp = entry;
			entry = entry->next;
			free(temp); // Entry 메모리 해제
		}
		map->table[i] = NULL;
	}
	free(map->table);
	free(map);
}