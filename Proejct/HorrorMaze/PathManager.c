#include "pch.h"
#include "PathManager.h"

char ContentPath[256];
char RelativePath[256];

void PathManager_Init()
{
	// 상대경로를 아스키 코드로 받는 함수
	GetCurrentDirectoryA(255, ContentPath);

}

char* GetRelativePath(const char* _filepath)
{
	// 경로상에 한글파일이 있으면 문제가 생기므로 한글파일을 영어로 바꿔서 사용해 주세요

	// 첫번째 문자를 \0 초기화해서 문자열이 텅빈것처럼 행돔함
	RelativePath[0] = '\0';

	strcat_s(RelativePath, sizeof(RelativePath), ContentPath);

	strcat_s(RelativePath, sizeof(RelativePath), _filepath);

	return RelativePath;
}
