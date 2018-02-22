#include "stdafx.h"
#include "Image2.h"


Image2::Image2()
	:m_imageInfo(NULL)	// ������ �ʱ�ȭ ��� 1
{
	//m_imageInfo = NULL; // ������ �ʱ�ȭ ��� 2
}

Image2::~Image2()
{
	this->Release();
}

HRESULT Image2::Init(int width, int height)
{
	// �ʱ�ȭ ���ε� imageInfo�� NULL �ƴ϶� �� �̹� ������ �ִٴ°�
	if (m_imageInfo != NULL) Release();

	// �ӽ� DC
	HDC hdc = GetDC(g_hWnd);	

	// CreateCompatibleDC
	// ��Ʈ�� ����� ���� �޸� DC�� ����� �ִ� �Լ�

	// CreateCompatibleBitmap
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� ����

	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� �ε�� ����� ������ hBit �̺κи� �����ϸ� ��
	// ���ҵ� �ε嵵 ��������
	// ���� �ڵ�� �׳� �����ϴ� ��
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);

	// �� �κ��� ���־�� ���� �������� �Ǽ��� ���ϽŰ�
	m_imageInfo->hOBit = (HBITMAP)SelectObject(
		m_imageInfo->hMemDC, m_imageInfo->hBit);

	m_imageInfo->width = width;
	m_imageInfo->height = height;

	// ������ �־ �������� ���� ���
	if (m_imageInfo->hBit == 0) {
		Release();
		// �����ߴٰ� �ϴ°� �޽����� �����ų� �׷��� �ƴ�
		return E_FAIL;	// ������ ��� ������ S_OK
	}
	
	ReleaseDC(g_hWnd, hdc);
	return S_OK;
}

void Image2::Release()
{
	if (m_imageInfo) {
		SelectObject(m_imageInfo->hMemDC, m_imageInfo->hOBit);
		DeleteObject(m_imageInfo->hOBit);
		DeleteDC(m_imageInfo->hMemDC);

		SAFE_DELETE(m_imageInfo);
	}
}

void Image2::Render(HDC hdc)
{
	BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
		m_imageInfo->hMemDC, 0, 0, SRCCOPY);
	// SRCCOPY ���� ũ�� ���� ũ�� �ٽ� ���� �� �������ִ� ��
}
