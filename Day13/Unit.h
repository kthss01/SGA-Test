#pragma once
#include <iostream>

using namespace std;

/// ����ü������ ��� ���� c++������

// ���� �Լ�
/*
	�޸𸮿� �����Լ� ���̺��̶�� ������ ����
	virtual attack() ����, ȣ��� �� attack()�� ȣ�� ��
*/


class Unit
{
private:
	int maxMp;
	int currentMp;

protected:
	int maxHp;
	int currentHp;
public:
	Unit();
	~Unit();

	void Move();
	virtual void Attack();	// ���� �Լ�	// ������ ä���� ������ �ȵ�
};

