#pragma once
/*
	���� �����Լ���
	�Ӹ�(����)�� ���������� ����(����)�� ���� �Լ��� ����

	������ ������ �ڽ��� override �ؾ� �Ѵ�.
*/

class Enemy
{
public:
	Enemy();
	~Enemy();

	virtual void AttackPlayer() = 0; // ���� �����Լ� ���� �Ǿ������� ���Ǵ� �Ǿ����� ����
};

