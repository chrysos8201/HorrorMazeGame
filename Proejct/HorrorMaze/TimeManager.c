#include "pch.h"
#include "TimeManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIXED_UPDATE_TIME (1.0f / 30.0f)

void FixedUpdate() {
	float elapsed_time = 0.0f;
	float fixed_update_timer = 0.0f;

	clock_t old_time = clock();

	while (1) {
		// 업데이트 주기를 맞춘다.
		clock_t new_time = clock();
		float delta_time = (float)(new_time - old_time) / CLOCKS_PER_SEC;
		old_time = new_time;
		elapsed_time += delta_time;
		fixed_update_timer += delta_time;

		// 고정된 주기에 맞게 함수를 호출한다.
		if (fixed_update_timer >= FIXED_UPDATE_TIME) {
			printf("Fixed Update - elapsed time: %f\n", elapsed_time);
			fixed_update_timer -= FIXED_UPDATE_TIME;
		}

		//if (elapsed_time >= 5.0f) break;
	}
}