#pragma once

// Image.h

// �̹��� ����

class Image {
	enum IMAGE_LOAD_KIND {
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage {
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		BYTE loadType;

		tagImage() {
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO m_imageInfo;
	char* fileName;				// �ε��� ����(�̹���) �̸�
	bool isTrans;				// ����(����Ÿ #define �� ��)�� ���� ����?
	COLORREF transColor;		// ���� ���� RGB(255,0,255) = ����Ÿ
								// �� ����Ÿ ����ŭ�� ������ ����� ���� ��������
								// ����Ÿ ������ �Ҽ��� �ֱ���
								// �ٸ� dc�� �����ϰ� �����ϴ� ������ �ϸ� �� �� ����

	BLENDFUNCTION blendFunc;	// ���� ���带 ���� ����
	LPIMAGE_INFO blendImage;	// ���� ���带 ����ϱ� ���� �̹��� ����
public:
	Image();
	~Image();

	HRESULT Init(int width, int height);
	// ���� �̸����� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	void Release();

	// �Ϲ� ����
	void Render(HDC hdc);
	// ȭ�鿡���� x ,y �� ��ŭ �̹��� ���� �����ִ°�
	void Render(HDC hdc, int destX, int destY);

	void Render(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);

	// ���� ����
	// alpha�� alpha�� �̶�� ���� byte�̹Ƿ� 0 ~ 255 
	void AlphaRender(HDC hdc, BYTE alpha);

	inline HDC GetMemDC() { return m_imageInfo->hMemDC; }
};