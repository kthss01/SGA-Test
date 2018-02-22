#include "stdafx.h"
#include "Image3.h"


Image3::Image3()
	:m_imageInfo(NULL)
{
}


Image3::~Image3()
{
	this->Release();
}

HRESULT Image3::Init(int width, int height)
{
	if (m_imageInfo != NULL) Release();

	HDC hdc = GetDC(g_hWnd);

	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	if (m_imageInfo->hBit == 0) {
		Release();
		return E_FAIL;
	}

	SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	DeleteObject(SelectObject(m_imageInfo->hMemDC, m_imageInfo->hObit));
	ReleaseDC(g_hWnd, hdc);
	return S_OK;
}

void Image3::Release()
{
	if (m_imageInfo) {
		SelectObject(m_imageInfo->hMemDC, m_imageInfo->hObit);
		DeleteObject(m_imageInfo->hObit);
		DeleteDC(m_imageInfo->hMemDC);

		SAFE_DELETE(m_imageInfo);
	}
}

void Image3::Render(HDC hdc)
{
	BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
		m_imageInfo->hMemDC, 0, 0, SRCCOPY);
}
