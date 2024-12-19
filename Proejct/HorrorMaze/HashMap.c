#include "pch.h"
//#include "HashMap.h"

// �ؽø� �ʱ�ȭ �Լ�
HashMap* createHashMap(int size) {
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	map->table = (Entry**)calloc(size, sizeof(Entry*));
	map->size = size;
	return map;
}

// �ؽ� �� ��� �Լ�
int hash(Pos key) {
	// Key ���� ������ �����Ͽ� ����
	return ((key.y * 31) + key.x) % HASH_KEY;
}

// ��Ʈ�� �߰� �Լ�
void put(HashMap* map, Pos key, Pos value) {
	int index = hash(key);
	Entry* entry = map->table[index];
	// Chaining Map ����� ����Ͽ� �ؽ� �浹 ó��
	while (entry != NULL) {
		if (entry->key.y == key.y && entry->key.x == key.x) {
			// Key�� �̹� �����ϸ� Value�� ����
			entry->value.y = value.y;
			entry->value.x = value.x;
			return;
		}
		entry = entry->next;
	}
	// ���ο� Key�� Value�� �߰����ֱ� ���� Entry ����ü ����
	entry = (Entry*)malloc(sizeof(Entry));
	entry->key = key;
	entry->value.y = value.y;
	entry->value.x = value.x;
	entry->next = map->table[index];
	map->table[index] = entry;
}

// Value ��ȯ �Լ�
Pos get(HashMap* map, Pos key) {
	int index = hash(key);
 	Entry* entry = map->table[index];
	while (entry != NULL) {
		if (entry->key.y == key.y && entry->key.x == key.x) {
			//Pos ret = entry->value;
			return entry->value; // Key�� �����ϴ� Value�� ����
		}
		entry = entry->next;
	}
	Pos ret = { -1,-1 };
	return ret; // Key�� �������� ������ -1 ����
}

// �ؽø� �޸� ���� �Լ�
void clearHashMap(HashMap* map) {
	for (int i = 0; i < map->size; i++) {
		//if (map == NULL) break;
		Entry* entry = map->table[i];
		while (entry != NULL) {
			Entry* temp = entry;
			entry = entry->next;
			free(temp); // Entry �޸� ����
		}
		map->table[i] = NULL;
	}
	free(map->table);
	free(map);
}