#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
	// Ű ���� ���� �������� �ʴ� ���·� �ʱ�ȭ
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
	// asyncKeyState �������ִ��� ���� Ȯ���ϴ� �Լ��ε� 
	// 0x8000 �־��ָ� ������ ���������� Ȯ���ϰ� �� 
	if (GetAsyncKeyState(key) & 0x8000) {
		// bitset�̱� ������ �迭 �ϳ��ϳ� 0 �ƴ� 1�� �Ǿ����� 
		// Ű ������ �� �ѹ��� �����ϰ� �����Ѱ�
		if (!m_keyDown[key]) {
			m_keyDown.set(key, true);
			return true;
		}
	}
	// Ű�� ���� ��
	else {
		m_keyDown.set(key, false);
	}
	return false;
}

bool KeyManager::GetKeyUp(int key)
{
	// ������ �ִ� ������ ��
	if (GetAsyncKeyState(key) & 0x8000) {
		m_keyUp.set(key, true);
	}
	// ���� ��
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
