#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
	// 키 값을 전부 눌려있지 않는 상태로 초기화
	for (int i = 0; i < KEYMAX; i++) {
		m_keyDown.set(i, false);
		m_keyUp.set(i, false);
	}
}


KeyManager::~KeyManager()
{
}

bool KeyManager::GetKeyDown(int key)
{
	// asyncKeyState 눌려져있는지 상태 확인하는 함수인데 
	// 0x8000 넣어주면 이전에 눌려졌는지 확인하게 됨 
	if (GetAsyncKeyState(key) & 0x8000) {
		// bitset이기 때문에 배열 하나하나 0 아님 1로 되어있음 
		// 키 눌렀을 때 한번만 반응하게 설정한거
		if (!m_keyDown[key]) {
			m_keyDown.set(key, true);
			return true;
		}
	}
	// 키를 땠을 때
	else {
		m_keyDown.set(key, false);
	}
	return false;
}

bool KeyManager::GetKeyUp(int key)
{
	// 누르고 있는 상태일 때
	if (GetAsyncKeyState(key) & 0x8000) {
		m_keyUp.set(key, true);
	}
	// 땠을 때
	else {
		if (m_keyUp[key]) {
			m_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
