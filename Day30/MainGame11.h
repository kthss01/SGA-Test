#pragma once

#include "GameNode.h"
#include "Image.h"

// �Ѿ� ������ ���� �߻�
#define BULLETMAX 50

struct tagBullet {
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	bool fire;
};

struct tagPlayer {
	POINT center;		// �÷��̾� ���� ����
	POINT cannonEnd;	// ���� ���� (�߻� ����)
	float angle;
	float cannon;		// ������ ����
	float raduis;
	float power;
};

class MainGame11 : public GameNode
{
private:
	tagPlayer m_player;
	tagBullet m_bullet[BULLETMAX];


	Image* bg;
	Image* apple;
	Image* apple2;

	bool isDraw;
public:
	MainGame11();
	~MainGame11();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Fire();			// �Ѿ� �߻�
	void MoveBullet();		// �Ѿ� ����
};

/*
	���� ������ ����

	�̹��� �������

	�Ӹ� ���� ����
	
	100 0 �Ӹ� 99 ���� 1 ~ 98 ���� �̹��� �ֱ�

	// �߰� �ɼ�
	���� ���� ���⿡ ���� �Ӹ��� �̹��� ȸ������ �غ��� -> ������ ����
	�Լ��� �ִµ� �����ϱ� ���� ��������� �Ͻ�

	����Ÿ �� �������� �� ����

	��Ʈ�� �׸� ������ �Ӽ� ����
	��Ʈ���� 32 64 �̷��� ����
	�ֱٿ� OS ���� �÷ȴµ� ������ �� �� ����
	
	������ 10 24 ��Ʈ�� ���� 255, 0, 255
	����Ÿ ��				 255, 0, 255
	������ 10 32 ��Ʈ�� ���� 255, 0, 255 �� �Ǿ��ֱ⵵��
							 254, 0, 254

	������ 7				 255, 0, 255
*/

/*
	�̹��� ȸ��
	SetWorldTransform (��� ���)

	3D 
	D3DXVECTOR3(x, y, z)

	D3DXMATRIX16 -> 4 x 4

	�� �ѷ� ����� API������ 3D�� ���� �� ����

	// API���� ������� 
	�̹��� ȸ���̶� �ȼ� ��굵 �������

	3D ����Ϸ���
	#include <d3d9.h> �ʿ���
*/