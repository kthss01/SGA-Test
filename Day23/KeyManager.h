#pragma once

#include "SingletonBase.h"
#include <bitset>		// 비트 단위로 변수 생성하는 녀석

using namespace std;	// bitset도 std 안에 있음

#define KEYMAX 256		// 큰값이라고 생각하면 됨

// keyManager 입력 관리 키 눌렀는지 뗐는지

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> m_keyUp;
	bitset<KEYMAX> m_keyDown;
public:
	KeyManager();
	~KeyManager();

	// Key를 한번만 눌렀는냐
	bool GetKeyDown(int key);
	// Key를 눌렀다 띄었느냐
	bool GetKeyUp(int key);
	// Key를 누르고 있는지
	bool GetKey(int key);
	// 한번 눌렀을 때 그 상태 유지하는 키 : 토글키, capslock 같은
	// 토글키인지
	bool GetToggleKey(int key);
};

#define INPUT KeyManager::GetSingleton()

// 프레임 워크 : 엔진보다 밑단계있는 녀석 정도로 생각하면 됨