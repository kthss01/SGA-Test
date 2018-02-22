#pragma once

// image load ��� 2����
// ���� �̸� (��ο��ִ°�) �ҷ����� ���

// ���ҽ� �ҷ����� ���
/*
	���ҽ� ���� ���� ����
	�� �Ⱦ��� ��
*/

class Image2
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage {
		// ���־� ��Ʃ��� ������ ���ҽ� �����������ؼ�
		// ID �ʿ� Resource.h �� define �Ǿ�����
		DWORD resID;	// ���ҽ� ID
		HDC hMemDC;		// �޸� DC
		HBITMAP hBit;	// ���ο� ��Ʈ�� �ڵ�
		HBITMAP hOBit;	// �õ� ��Ʈ�� �ڵ�
		int width;
		int height;
		BYTE loadType;

		tagImage() 
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			// Resource ���� ���ϱ� ����� File�̶� ���̴� �ҷ����� �����
			// �׷����ϴµ� ���� ������
			// API ����ϸ鼭 Resource ��� ���� ���Ҳ�
			loadType = LOAD_RESOURCE;
		}

		// API �⺻ ���� ��Ʈ���̱� ��
		// �ٸ����� ������ �� �ʿ��� ���� API�� bitmap�� ��� �� �� ����
	}IMAGE_INFO, *LPIMAGE_INFO;	// �տ��� �׳� �θ���, LP�� ����Ʈ�� �θ���
	// IMAGE_INFO * == LPIMAGE_INFO 
	
private:
	LPIMAGE_INFO m_imageInfo;

public:
	Image2();
	~Image2();

	// �� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(int width, int height);

	// �����
	void Release();

	void Render(HDC hdc);

	// DC���� ��� �´�.
	inline HDC GetMemDC() { return m_imageInfo->hMemDC; }
};

