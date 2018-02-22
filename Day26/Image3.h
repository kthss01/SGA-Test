#pragma once
class Image3
{
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
		HBITMAP hObit;
		int width;
		int height;
		BYTE loadType;

		tagImage() {
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hObit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;
	
private:
	LPIMAGE_INFO m_imageInfo;
public:
	Image3();
	~Image3();

	HRESULT Init(int width, int height);

	void Release();

	void Render(HDC hdc);

	inline HDC GetMemDC() { return m_imageInfo->hMemDC; }
};

