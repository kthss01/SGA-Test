#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <conio.h>
#include <vector>

// 프로젝트 속성에서 링커 입력 쪽에 gdiplus.lib 추가해도 되고
// 코드로 아래와 같이 적어도 됨
#pragma comment (lib, "gdiplus.lib")

using namespace std;
using namespace Gdiplus;

struct tagImageInfo {
	Gdiplus::Image* image;
	Gdiplus::Rect rect;	// 사각형, 
	// 이 안에 이미지를 띄울꺼 위치 말하는거라고 보면 될듯
};

// GDI+, API, 
// DirectX-> D2D(2D작업, D3D로 힘들어서 나온거), 
//			 D3D(3D작업, 2D대신 사용할 순 있음)

// 이미지 가능하면 png로 쓰는게 좋음 단점은 용량이 큼
// bmp는 alpha값이 없음, jpg는 format자체가 복잡하게 되어있음

class DrawImage
{
	// 접근지정자 안써주면 private임
private:
	// 256 숫자 담을 수 있다 가정
	// -127 ~ 128까지 담음 
	// unsigned 붙이면 0 ~ 255까지 담음

	// 이미지 파일 저장
	Gdiplus::Image* image;	// 이미지에 대한 정보를 담는 클래스
	// 그림을 그리는데 필요한 녀석이 들어있음
	Gdiplus::Graphics* pGraphics;
	//direct에서는 d3d 임
	ULONG_PTR  gdiplusToken; // unsinged long ptr , 시작하는 녀석,

	vector<tagImageInfo> images;
public:
	DrawImage();
	~DrawImage();

	// 화면을 지워주는 역할
	void Clear(int r, int g, int b);	
	// 이미지 불러오는 녀석
	void AddImage(WCHAR* fileName);		// WCHAR char라고 일단 알자
	void AddImage(WCHAR* fileName, Gdiplus::Rect rect);
	// 불러온 파일 그리는 애
	void Drawing(int x, int y);	
	void Drawing(int number);
	void Drawing(int number, Rect rect);

	vector<tagImageInfo>& GetImageInfo() { return images; }
};

