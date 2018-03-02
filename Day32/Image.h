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
		DWORD resID;			// ���ҽ� ID
		HDC hMemDC;				// �޸� DC
		HBITMAP hBit;			// ���ο� ��Ʈ�� �ڵ�
		HBITMAP hOBit;			// �õ� ��Ʈ�� �ڵ�
		
		float x;				// �̹��� x ��ǥ
		float y;				// �̹��� y ��ǥ
		int width;				// �̹��� ����ũ��
		int height;				// �̹��� ����ũ��
		int currentFrameX;		// ���� ������ X
		int currentFrameY;		// ���� ������ Y
		int maxFrameX;			// �ִ� X ������ ����
		int maxFrameY;			// �ִ� Y ������ ����
		int frameWidth;			// 1 ������ �� ���� ũ��	* ȭ�鿡 �ߴ� ũ��
		int frameHeight;		// 1 ������ �� ���� ũ��

		BYTE loadType;			// �ε� Ÿ��

		tagImage() {
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0.0f;
			y = 0.0f;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
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

	// �� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(int width, int height);
	// ���� �̸����� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT Init(const char* fileName, 
		int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	void SetTransColor(bool isTrans, COLORREF transColor);

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

	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight, BYTE alpha);

	// ������ ����
	void FrameRender(HDC hdc, int destX, int destY);

	void FrameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);

	void FrameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY, BYTE alpha);

	inline HDC GetMemDC() { return m_imageInfo->hMemDC; }

	// Get, Set �Լ��� (���߿�)

	// �̹����� ��ǥ x get set
	inline float GetX() { return m_imageInfo->x; }
	inline void SetX(float x) { m_imageInfo->x = x; }
	// �̹����� ��ǥ y get set

	// �̹��� ���� ��ǥ ���� get set
	
	// �̹��� ����, ���� ��� Get

	// �ٿ�� �ڽ� (�浹�� ��Ʈ �����) Get
	// ��Ʈ ũ��� �Ǿ��ִ� �ڽ�
	// x, y�� �߽������� �Ǿ� ����
	inline RECT GetBoundingBox() {
		RECT rc = RectMakeCenter(
			m_imageInfo->x, m_imageInfo->y,
			m_imageInfo->width, m_imageInfo->height);
		return rc;
	}

	// ������ �ٿ�� �ڽ� (������ �̹����� �浹 ��Ʈ) Get
	// ��ǥ���� ������ x,y�� �ʺ�� ���� 

	// ������ X get set
	// ������ ���� ���� ũ�� Get
	// �ƽ� ������ x, y, Get
};