#pragma once

#include "GameNode.h"

// �����̰��� Ǯ��
// ���� �ذ� ��� ���� �߸��Ǿ�����
// ������ �Ѱ�����߰� �������� ��ġ�� �ʾҾ����
// Ȯ���� ���غ��� ������ ����� �ű���

#define BEADMAX 100

struct tagBead {
	float x, y;
	float angle;
	float speed;
	float radius;
};

// �� �簢�� �浹

// �ð� ���⵵, ���� ���⵵
/*
	�ڵ忡 ���� ������ ������ ȿ������ ������ ����
*/

class MainGame10 : public GameNode
{
private:
	tagBead _bead[BEADMAX];


	RECT m_rc; // �簢��
	RECT m_el; // ��

	POINT m_ptSave;
	POINT m_elCenter;	// ���� �߽���
	float m_radius;

	bool m_touch;		// ���ϰ� ���콺 Ŭ���ߴ���

	RECT m_block[20];
public:
	MainGame10();
	~MainGame10();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BeadMove();

	bool RectInCircle(RECT* rect, POINT circleCenter, float radius);
};

/*
	����
	���� ����
	�� �� ���� ������� ���� ����ó�� �����غ���
*/