#pragma once
#include <fmod.h>
void SoundManager_Init();

void SoundManager_Exit();

// �÷����ϰ���� ����, ä�γѹ��� �Է��ؼ� ���� ���
void SoundManager_PlaySound(int sound_number);

// ����Ʈ �÷��� �Լ�
void SoundManager_PlayEffect(int sound_number);
void SoundManager_StopEffect();

// �÷����ϰ� �ִ� ä�ο��� ������ �����
void SoundManager_StopSound();


/// ��ó : �̱���


