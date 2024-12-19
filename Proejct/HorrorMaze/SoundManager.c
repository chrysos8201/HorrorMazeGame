#include "pch.h"
#include "SoundManager.h"
#include "PathManager.h"
#include "Struct.h"
#include <assert.h>
FMOD_SYSTEM* fsystem;
FMOD_SOUND* sound[SOUND_COUNT];
FMOD_RESULT result;
FMOD_CHANNEL* channelMusic;
FMOD_CHANNEL* channelEffect;

void SoundManager_Init()
{
	// FMOD 시스템 객체 초기화
	result = FMOD_System_Create(&fsystem, FMOD_VERSION);
	assert(!result);

	result = FMOD_System_Init(fsystem, 32, FMOD_INIT_NORMAL, NULL);
	assert(!result);

	// 사운드 장착
	result = FMOD_System_CreateSound(fsystem, GetRelativePath("footsteps.wav"), FMOD_DEFAULT, 0, &sound[SOUND_FOOTSTEP]);
	assert(!result);
	result = FMOD_System_CreateSound(fsystem, GetRelativePath("WhiteNoise.wav"), FMOD_DEFAULT, 0, &sound[SOUND_BGM]);
	assert(!result);
	result = FMOD_System_CreateSound(fsystem, GetRelativePath("Enemy.wav"), FMOD_DEFAULT, 0, &sound[SOUND_ENEMY]);
	assert(!result);
	result = FMOD_System_CreateSound(fsystem, GetRelativePath("GameOver.wav"), FMOD_DEFAULT, 0, &sound[SOUND_GAMEOVER]);
	assert(!result);

}

void SoundManager_Exit()
{
	// 시스템 객체 해제
	FMOD_System_Release(fsystem);
}

void SoundManager_PlaySound(int sound_number)
{
	// 사운드 파일 로드 및 재생
	FMOD_System_PlaySound(fsystem, sound[sound_number], NULL, 0, &channelMusic);
}

void SoundManager_PlayEffect(int sound_number)
{
	// 사운드 파일 로드 및 재생
	FMOD_System_PlaySound(fsystem, sound[sound_number], NULL, 0, &channelEffect);
}
void SoundManager_StopEffect()
{
	FMOD_Channel_Stop(channelEffect);
}
void SoundManager_StopSound()
{
	// 재생 중인 사운드 멈추기
	FMOD_Channel_Stop(channelMusic);
}

/// 출처 : 이기태
