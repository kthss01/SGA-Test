#include "stdafx.h"
#include "MainGame15.h"


MainGame15::MainGame15()
{
}


MainGame15::~MainGame15()
{
}

HRESULT MainGame15::Init()
{
	GameNode::Init();

	_bg = new Image;

	// �ȼ� �浹�� ��Ʈ �浹���� �� ��Ȯ�ϰ� �� �� ����
	// �׷��� �������� ��Ʈ �浹���� ����� ����

	_bg->Init("images/mountain.bmp", 800, 600, true, RGB(255,0,255));

	_ball = new Image;
	_ball->Init("images/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 - 30;

	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());

	_probeY = _y + _ball->GetHeight() / 2;

	return S_OK;
}

void MainGame15::Release()
{
	GameNode::Release();

	SAFE_DELETE(_bg);
	SAFE_DELETE(_ball);
}

void MainGame15::Update()
{
	GameNode::Update();

	if (INPUT->GetKey(VK_LEFT)) {
		_x -= 2.0f;
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		_x += 2.0f;
	}
	_probeY = _y + _ball->GetHeight() / 2;

	// �˻��ϰ� ���� ���� (�̹��� �ȼ��� ��ǥ)
	for (int i = _probeY - 10; i < _probeY + 10; i++) {

		COLORREF color = GetPixel(_bg->GetMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// ���� ������ ������ ���ϴ� ���� ������ ��
		if (!(r == 255 && g == 0 && b == 255)) {
			// ����Ÿ ���� �ƴҶ� ���� �ø���
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());
}

void MainGame15::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		_bg->Render(memDC);
		_ball->Render(memDC, _rc.left, _rc.top);
	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
