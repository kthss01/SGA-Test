#pragma once
// RandomFunction.h

#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction() {
		// GetTickCount 컴퓨터 키고나서부터 현재까지의 시간을 받아오는 함수
		srand(GetTickCount());
	}
	~RandomFunction() {}

	inline int GetInt(int num) { return rand() % num; }
	// 사이값 랜덤하게 받아오는 함수
	inline int GetFromInto(int fromNum, int toNum) {
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};

#define RND RandomFunction::GetSingleton()