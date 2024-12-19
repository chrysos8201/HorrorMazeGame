#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
//static GameManager gameManager;


// Singleton?
GameManager* GetInstance()
{
	static GameManager* instance = NULL;
	if (instance == NULL)
	{
		instance = malloc(sizeof(*instance));
		instance->player = malloc(sizeof(Player));
		instance->enemy = malloc(sizeof(Enemy));
	}

	return instance;
}




void MemoryAllClear()
{
	// Enemy는 hashmap을 해제해야 하므로 내부적으로 Delete함수를 만들어 사용함.
	Enemy_Delete(GetInstance()->enemy);
	free(GetInstance()->player);
	free(GetInstance()->enemy);
	free(GetInstance());
}


