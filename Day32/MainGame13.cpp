#include "stdafx.h"
#include "MainGame13.h"


MainGame13::MainGame13()
{
}


MainGame13::~MainGame13()
{
}

HRESULT MainGame13::Init()
{
	GameNode::Init();

	// �ϸ� ��ġ ��ǥ �ʱ�ȭ
	posX = WINSIZEX / 2;
	posY = WINSIZEY / 2;

	// �ϸ� �̹��� �ʱ�ȭ
	m_rockman = new Image;
	// 960 x 200 �� �ϸ� �̹��� ũ�� ������ �� ��
	m_rockman->Init("images/�ϸ�.bmp", posX, posY, 480, 100,
		10, 2, true, RGB(255, 0, 255));

	/*
		������ �ʱ�ȭ
	*/
	//char str[256];
	//for (int i = 1; i < 11; i++) {
	//	sprintf_s(str, "images/���� �ȱ�%d.bmp", i);
	//	m_rockman->Init(str, posX, posY, 480, 100,
	//		10, 2, true, RGB(255, 0, 255));
	//}

	// ������ ���� ������ �ʱ�ȭ
	m_isLeft = false;
	m_indexX = m_indexY = 0;

	// os�� �����ϰ������� ��������� �ð�
	prevTime = GetTickCount();

	return S_OK;
}

void MainGame13::Release()
{
	GameNode::Release();
	SAFE_DELETE(m_rockman);
}

void MainGame13::Update()
{
	GameNode::Update();

	curTime = GetTickCount();

	/*
		�ݰ�ġ�� ������ �ϴ°�
		
		����� �κи�ŭ ���� �׸��� �� (������ �ι�) 

		�̹����� �߶� �κи� �ݴ��ʿ� �׸��� �� (������ �ѹ�) - �̹�� ���� ��
	*/

	if (INPUT->GetKey('A')) {
		posX -= 5;
		m_isLeft = true;
		// �� �������� ���� �ʺ� ���� ������
		if (posX < 0 - 48) {
			posX = WINSIZEX;
		}
	}
	if (INPUT->GetKey('D')) {
		posX += 5;
		m_isLeft = false;
		if (posX > WINSIZEX) {
			// 0�� �ƴ϶� 48 �� ������ ȭ�� �ۿ��� ������ �� �� �ְ�
			posX = -48;
		}
	}

	// ���� �ڵ�� ���� ����Ǹ� �߰��� ��Ż�Ǵ� �����
	// � �̹����� �ڿ������� ���� �� ����

	// ������ �ٶ󺸰� ������
	if (m_isLeft) {
		m_indexY = 1;
		if (curTime - prevTime > 50)
		{
			m_indexX--;
			if (m_indexX < 0)
			{
				// index 10�� �ȱ׷��� �κ�
				// �Ȳ���� �ϰ� ������ 9�� ����
				m_indexX = 9;
			}
			prevTime = GetTickCount();
		}
	}
	// �������� �ٶ󺸰� ������
	else {
		m_indexY = 0;
		if (curTime - prevTime > 50)
		{
			m_indexX++;
			if (m_indexX > 10)
			{
				m_indexX = 0;
			}
			prevTime = GetTickCount();
		}
	}
}

void MainGame13::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===============================================
	{
		m_rockman->FrameRender(memDC, posX, posY,
			m_indexX, m_indexY);
	}
	//===============================================
	this->GetBackBuffer()->Render(hdc);
}
