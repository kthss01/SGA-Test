#include "stdafx.h"
#include "Image2.h"


Image2::Image2()
	:m_imageInfo(NULL)	// 생성자 초기화 방식 1
{
	//m_imageInfo = NULL; // 생성자 초기화 방식 2
}

Image2::~Image2()
{
	this->Release();
}

HRESULT Image2::Init(int width, int height)
{
	// 초기화 중인데 imageInfo가 NULL 아니란 건 이미 데이터 있다는거
	if (m_imageInfo != NULL) Release();

	// 임시 DC
	HDC hdc = GetDC(g_hWnd);	

	// CreateCompatibleDC
	// 비트맵 출력을 위한 메모리 DC를 만들어 주는 함수

	// CreateCompatibleBitmap
	// hdc와 호환되는 비트맵을 생성

	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 파일 로드로 만들고 싶으면 hBit 이부분만 수정하면 됨
	// 리소드 로드도 마찬가지
	// 지금 코드는 그냥 생성하는 거
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);

	// 이 부분을 해주어야 햇음 선생님이 실수로 못하신거
	m_imageInfo->hOBit = (HBITMAP)SelectObject(
		m_imageInfo->hMemDC, m_imageInfo->hBit);

	m_imageInfo->width = width;
	m_imageInfo->height = height;

	// 문제가 있어서 생성되지 않은 경우
	if (m_imageInfo->hBit == 0) {
		Release();
		// 실패했다고만 하는거 메시지가 나오거나 그런건 아님
		return E_FAIL;	// 실패한 경우 성공은 S_OK
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
	// SRCCOPY 가로 크기 세로 크기 다시 설정 후 복사해주는 거
}
