#pragma once

// 출처 : 이기태

extern char ContentPath[256];
extern char RelativePath[256];

void PathManager_Init();
char* GetRelativePath(const char* _filepath);
