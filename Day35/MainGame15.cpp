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

	_bg->Init("images/�ް��ǹ��.bmp", WINSIZEX, WINSIZEY);

	return S_OK;
}

void MainGame15::Release()
{
	GameNode::Release();

	SAFE_DELETE(_bg);
}

void MainGame15::Update()
{
	GameNode::Update();

	// �˻��ϰ� ���� ���� (�̹��� �ȼ��� ��ǥ)
	for (int i = 0; i < 10; i++) {
		// 100, 100 x, y��� ���� ��
		for (int j = 0; j < _bg->GetHeight(); j++) {
			COLORREF color = GetPixel(_bg->GetMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			// ���� ������ ������ ���ϴ� ���� ������ ��
			if (r == 255 && g == 0 && b == 255) {
				// �浹 ó��
			}
		}
	}
}

void MainGame15::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	// �˻��ϰ� ���� ���� (�̹��� �ȼ��� ��ǥ)
	for (int i = 0; i < _bg->GetWidth(); i++) {
		// 100, 100 x, y��� ���� ��
		for (int j = 0; j < _bg->GetHeight(); j++) {
			COLORREF color = GetPixel(_bg->GetMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int gray = (r + b + g) / 3;
			SetPixel(memDC, i, j, RGB(gray, gray, gray));
		}
	}
	//_bg->Render(memDC);
	


	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
