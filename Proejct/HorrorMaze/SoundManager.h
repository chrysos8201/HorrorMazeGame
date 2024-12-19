#pragma once
#include <fmod.h>
void SoundManager_Init();

void SoundManager_Exit();

// 플레이하고싶은 사운드, 채널넘버를 입력해서 사운드 재생
void SoundManager_PlaySound(int sound_number);

// 이펙트 플레이 함수
void SoundManager_PlayEffect(int sound_number);
void SoundManager_StopEffect();

// 플레이하고 있는 채널에서 음악을 멈춘다
void SoundManager_StopSound();


/// 출처 : 이기태


