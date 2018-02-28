#include "stdafx.h"
#include "MainGame12.h"


MainGame12::MainGame12()
{
}


MainGame12::~MainGame12()
{
}

HRESULT MainGame12::Init()
{
	GameNode::Init();

	// �ʱ�ȭ ���ִ� �Լ�
	memset(_bead, 0, sizeof(_bead));
	//memset(_bead, 0, sizeof(tagBead) * BEADMAX);

	for (int i = 0; i < BEADMAX; i++) {
		_bead[i].radius = 20.0f;
		_bead[i].speed = 5.0f;
		// ���� ������ (����) ? �� : ����;
		_bead[i].angle = (i == 0) ? RND->GetInt(7) : _bead[i - 1].angle;
		_bead[i].x = (i == 0) ? RND->GetFromInto(100, WINSIZEX - 100)
			: _bead[i].x - cosf(_bead[i].angle) *
			(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
		_bead[i].y = (i == 0) ? RND->GetFromInto(100, WINSIZEY - 100)
			: _bead[i].y - (-sinf(_bead[i].angle)) *
			(_bead[i - 1].radius * 2 + _bead[i].radius * 2);
	}

	image[0] = new Image;
	image[0]->Init("images/apple.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));

	image[1] = new Image;
	image[1]->Init("images/��� ȭ��.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));

	image[2] = new Image;
	image[2]->Init("images/apple.bmp",
		_bead[0].radius + 10, _bead[0].radius + 10, true, RGB(255, 0, 255));
	
	bg = new Image;
	bg->Init("images/��� ȭ��.bmp", WINSIZEX, WINSIZEY);
	
	x = y = 0;
	alpha = 0;

	return S_OK;
}

void MainGame12::Release()
{
	GameNode::Release();
	for(int i=0; i<3; i++)
		SAFE_DELETE(image[i]);	// new �Ҵ� ���� ������ SAFE_DELETE
	SAFE_DELETE(bg);
}

void MainGame12::Update()
{
	GameNode::Update();

	if (INPUT->GetKey('W')) { y += 1; }
	if (INPUT->GetKey('S')) { y -= 1; }
	if (INPUT->GetKey('A')) { x -= 1; }
	if (INPUT->GetKey('D')) { x += 1; }
	if (INPUT->GetKey('Q')) { alpha += 1; }
	if (INPUT->GetKey('E')) { alpha -= 1; }

	BeadMove();
}

void MainGame12::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//bg->Render(memDC, 100, 100, 200 + x, 200 + y, 300, 300);
	//bg->AlphaRender(memDC, alpha); // 0 �� ���� 255 ������
	
	//image[0]->Render(memDC);
	image[0]->AlphaRender(memDC, 128);

	//for (int i = 0; i < BEADMAX; i++) {
	//	//EllipseMakeCenter(memDC, _bead[i].x, _bead[i].y, _bead[i].radius);
	//	//image[0]->Render(memDC, _bead[i].x, _bead[i].y);
	//	if (i < 1) {
	//		// �Ӹ�
	//		image[0]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//	else if (i < BEADMAX - 2) {
	//		// ����
	//		image[1]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//	else
	//	{
	//		// ����
	//		image[2]->Render(memDC, _bead[i].x, _bead[i].y);
	//	}
	//}

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame12::BeadMove()
{
	for (int i = 0; i < BEADMAX; i++) {
		if (i == 0) {
			_bead[i].x += cosf(_bead[i].angle) * _bead[i].speed;
			_bead[i].y += -sinf(_bead[i].angle) * _bead[i].speed;

			// �� �浹
			// ��ġ ���� �ʿ伺��
			// �ӵ��� �ʹ� ������ �� ���ĳ����� �ʰ� �ϴ°���
			// �ӵ� ���� �ϸ� ���ص� �Ǵ� ���
			// ���� 
			if (_bead[i].x - _bead[i].radius < 0)
				_bead[i].angle = PI - _bead[i].angle;
			// ������
			if (_bead[i].x + _bead[i].radius > WINSIZEX)
				_bead[i].angle = PI - _bead[i].angle;
			// ��
			if (_bead[i].y - _bead[i].radius < 0)
				_bead[i].angle = -_bead[i].angle;
			// �Ʒ�
			if (_bead[i].y + _bead[i].radius > WINSIZEY)
				_bead[i].angle = -_bead[i].angle;
		}
		else {
			// �̷������� �ص� �Ǵµ� ��ǻ�� ���ɿ� �ٶ� 
			// �Ѳ����� ȸ���ϴ� ��쵵 ���� �� ����� ���� ����
			//_bead[i-1].angle = _bead[i-1].angle;

			float distance = GetDistance(_bead[i].x, _bead[i].y,
				_bead[i - 1].x, _bead[i - 1].y);

			// _bead[i].radius + _bead[i-1].radius
			if (_bead[i].radius * 2 < distance) {

				// GetAngle ������ �μ� �ݴ�� ������ ���� �� �� �� ���� 180 ����
				// �׷��� ��ź �߻� �� ������ �浹�� �� �ݴ�� �ִ°�
				_bead[i].angle = GetAngle(
					_bead[i].x, _bead[i].y, _bead[i - 1].x, _bead[i - 1].y);

				_bead[i].x = _bead[i - 1].x - cosf(_bead[i].angle) *
					_bead[i].radius * 2;
				_bead[i].y = _bead[i - 1].y - (-sinf(_bead[i].angle)) *
					_bead[i].radius * 2;
			}

			_bead[i].x += cosf(_bead[i].angle) * _bead[i].speed;
			_bead[i].y += -sinf(_bead[i].angle) * _bead[i].speed;
		}
	}
}
