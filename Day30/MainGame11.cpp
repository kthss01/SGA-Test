#include "stdafx.h"
#include "MainGame11.h"


MainGame11::MainGame11()
{
}


MainGame11::~MainGame11()
{
}

HRESULT MainGame11::Init()
{
	GameNode::Init();

	bg = new Image;
	apple = new Image;
	apple2 = new Image;

	bg->Init(
		"images/��� ȭ��.bmp",		// ���� ��� + ���� �̸� + Ȯ���� �� (���������� ������Ʈ)
		WINSIZEX,
		WINSIZEY
	);

	// ũ�� ���̸� ��� ũ�⵵ �۾���
	apple->Init("images/apple.bmp", 124, 162, true, RGB(255, 0, 255));

	/*
		����
		�켱 ���� ��Ʈ�� ũ��� �׸��� 255,255,255 �� ������ ������ ����
		width�� ����ũ�� �÷��� ������ ���� ����
		������ height�� 1�̶� �ø��� ���� ����Ÿ���� �ƴ϶� 254,0,254 �� �ؾ��ϰ�
		height ���� �ƴ϶� width ���� �������̻� Ŀ���� 254,0,254 �ؾߵǴ°� ����
		-> ���� �Ѵ� ���� ũ�� �Ѿ �� ���� �߻���
		���ʰ� �Ʒ��ʿ� �ణ�� ����Ÿ���� ������ ���ԵǾ�
		�� �κ��� ���� �ι� GdiTransparentBlt ����� �ϴµ�
	*/

	apple2->Init("images/apple.bmp", 125, 163, true, RGB(255, 0, 255));

	isDraw = false;


	m_player.cannon = 80.0f;
	m_player.angle = PI / 4;
	m_player.center.x = 0;
	m_player.center.y = WINSIZEY;

	// ����ü �޸� 0���� �ʱ�ȭ �Ǵ°�
	memset(m_bullet, 0, sizeof(m_bullet));

	for (int i = 0; i < BULLETMAX; i++) {
		m_bullet[i].fire = false;
		m_bullet[i].radius = 20.0f;
	}

	return S_OK;
}

void MainGame11::Release()
{
	GameNode::Release();
}

void MainGame11::Update()
{
	GameNode::Update();

	if (INPUT->GetKeyDown(VK_SPACE))
		isDraw = false;

	if (INPUT->GetKey(VK_LEFT) && m_player.angle < PI / 2) 
		m_player.angle += 0.04f;
	if (INPUT->GetKey(VK_RIGHT) && m_player.angle > 0.1f)
		m_player.angle -= 0.04f;

	if (INPUT->GetKeyDown(VK_SPACE)) {
		m_player.power = 1.0f;
	}
	if (INPUT->GetKey(VK_SPACE)) {
		m_player.power += 0.1f;
	}
	if (INPUT->GetKeyUp(VK_SPACE)) {
		Fire();
	}

	MoveBullet();

	m_player.cannonEnd.x = 
		cosf(m_player.angle) * m_player.cannon + m_player.center.x;
	m_player.cannonEnd.y = 
		-sinf(m_player.angle) * m_player.cannon + m_player.center.y;
}

void MainGame11::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		bg->Render(memDC);

		//if (isDraw) {
		//	for (int i = 0; i < 10; i++) {
		//		// ������ �ϳ����� ������ ���� �ϸ� ��
		//		apple->Render(memDC,
		//			RND->GetFromInto(100, WINSIZEX - 100),
		//			RND->GetFromInto(100, WINSIZEY - 100));
		//		isDraw = true;
		//	}
		//}

		apple->Render(memDC, 300, 300);
		apple2->Render(memDC,100, 100);

		EllipseMakeCenter(
			memDC, m_player.center.x, m_player.center.y, 50);
		LineMake(memDC, m_player.center, m_player.cannonEnd);
		for (int i = 0; i < BULLETMAX; i++) {
			if (!m_bullet[i].fire) continue;
			EllipseMakeCenter(
				memDC, m_bullet[i].x, m_bullet[i].y, m_bullet[i].radius);
		}
	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame11::Fire()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].fire == true) continue;

		m_bullet[i].fire = true;
		m_bullet[i].x = 
			cosf(m_player.angle) * (m_player.cannon + 10) + m_player.center.x;
		m_bullet[i].y =
			-sinf(m_player.angle) * (m_player.cannon + 10) + m_player.center.y;
		m_bullet[i].speed = m_player.power;
		m_bullet[i].angle = m_player.angle;
		break;
	}
}

void MainGame11::MoveBullet()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].fire == false) continue;

		m_bullet[i].x += cosf(m_bullet[i].angle) * m_bullet[i].speed;
		m_bullet[i].y += -sinf(m_bullet[i].angle) * m_bullet[i].speed;
	}
}

