#pragma once
// RandomFunction.h

#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction() {
		// GetTickCount ��ǻ�� Ű�������� ��������� �ð��� �޾ƿ��� �Լ�
		srand(GetTickCount());
	}
	~RandomFunction() {}

	inline int GetInt(int num) { return rand() % num; }
	// ���̰� �����ϰ� �޾ƿ��� �Լ�
	inline int GetFromInto(int fromNum, int toNum) {
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};

#define RND RandomFunction::GetSingleton()