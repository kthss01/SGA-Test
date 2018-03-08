#pragma once

#include "GameNode.h"

class MainGame15 : public GameNode
{
private:
	Image* _ball;	// ������ �̹���
	Image* _bg;		// �浹 ����� �� �̹���

	float _x, _y;	// ��ġ
	int _probeY;	// Ž�� ����

	RECT _rc;
public:
	MainGame15();
	~MainGame15();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

/*
	�⺻�� �ȼ� �˻�
	ȭ�鿡 ��� �༮(DC), ����� �� �༮(DC)���� ���� �̹��� DC�� �ΰ�
*/

/*
	����

	��� �̹��� (����ų� ���ؼ�)
	Ⱦ���� ���̴� ���
	���� ���� �̸��� ����� �ö� �� �ְ� �����

	�̹��� 2�� �ʿ�
	(��� �������� �ȼ� �浹��)

	ĳ���Ͱ� ����
	����Ű ���� ���� ���������� �̵�
	�̵����� �� ���� ���� (���� ������ ����)���� ������ �ö�
	(�ȼ� �浹�ϴ� ��� Ȱ��)
	������ �� �ö�
	����Ű ������ ��������
*/

