#pragma once

#include "SingletonBase.h"
#include <bitset>		// ��Ʈ ������ ���� �����ϴ� �༮

using namespace std;	// bitset�� std �ȿ� ����

#define KEYMAX 256		// ū���̶�� �����ϸ� ��

// keyManager �Է� ���� Ű �������� �ô���

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> m_keyUp;
	bitset<KEYMAX> m_keyDown;
public:
	KeyManager();
	~KeyManager();

	// Key�� �ѹ��� �����³�
	bool GetKeyDown(int key);
	// Key�� ������ �������
	bool GetKeyUp(int key);
	// Key�� ������ �ִ���
	bool GetKey(int key);
	// �ѹ� ������ �� �� ���� �����ϴ� Ű : ���Ű, capslock ����
	// ���Ű����
	bool GetToggleKey(int key);
};

#define INPUT KeyManager::GetSingleton()

// ������ ��ũ : �������� �شܰ��ִ� �༮ ������ �����ϸ� ��