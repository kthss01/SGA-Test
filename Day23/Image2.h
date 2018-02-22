#pragma once

// image load 방법 2가지
// 파일 이름 (경로에있는거) 불러오는 방법

// 리소스 불러오는 방법
/*
	리소스 파일 보면 있음
	잘 안쓰는 편
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
		// 비주얼 스튜디오 내에서 리소스 가져오기위해선
		// ID 필요 Resource.h 에 define 되어있음
		DWORD resID;	// 리소스 ID
		HDC hMemDC;		// 메모리 DC
		HBITMAP hBit;	// 새로운 비트맵 핸들
		HBITMAP hOBit;	// 올드 비트뱁 핸들
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
			// Resource 파일 구하기 힘들고 File이랑 차이는 불러오는 방식임
			// 그려야하는데 쉽지 않으니
			// API 사용하면서 Resource 사용 거의 안할꺼
			loadType = LOAD_RESOURCE;
		}

		// API 기본 형식 비트맵이긴 함
		// 다른것은 조건이 좀 필요함 순수 API는 bitmap만 띄어 줄 수 있음
	}IMAGE_INFO, *LPIMAGE_INFO;	// 앞에는 그냥 부를때, LP는 포인트로 부를때
	// IMAGE_INFO * == LPIMAGE_INFO 
	
private:
	LPIMAGE_INFO m_imageInfo;

public:
	Image2();
	~Image2();

	// 빈 비트맵 이미지 초기화
	HRESULT Init(int width, int height);

	// 지우기
	void Release();

	void Render(HDC hdc);

	// DC값을 얻어 온다.
	inline HDC GetMemDC() { return m_imageInfo->hMemDC; }
};

