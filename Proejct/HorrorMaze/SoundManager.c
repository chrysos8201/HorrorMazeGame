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
	// FMOD �ý��� ��ü �ʱ�ȭ
	result = FMOD_System_Create(&fsystem, FMOD_VERSION);
	assert(!result);

	result = FMOD_System_Init(fsystem, 32, FMOD_INIT_NORMAL, NULL);
	assert(!result);

	// ���� ����
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
	// �ý��� ��ü ����
	FMOD_System_Release(fsystem);
}

void SoundManager_PlaySound(int sound_number)
{
	// ���� ���� �ε� �� ���
	FMOD_System_PlaySound(fsystem, sound[sound_number], NULL, 0, &channelMusic);
}

void SoundManager_PlayEffect(int sound_number)
{
	// ���� ���� �ε� �� ���
	FMOD_System_PlaySound(fsystem, sound[sound_number], NULL, 0, &channelEffect);
}
void SoundManager_StopEffect()
{
	FMOD_Channel_Stop(channelEffect);
}
void SoundManager_StopSound()
{
	// ��� ���� ���� ���߱�
	FMOD_Channel_Stop(channelMusic);
}

/// ��ó : �̱���
