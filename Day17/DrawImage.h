#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <conio.h>
#include <vector>

// ������Ʈ �Ӽ����� ��Ŀ �Է� �ʿ� gdiplus.lib �߰��ص� �ǰ�
// �ڵ�� �Ʒ��� ���� ��� ��
#pragma comment (lib, "gdiplus.lib")

using namespace std;
using namespace Gdiplus;

struct tagImageInfo {
	Gdiplus::Image* image;
	Gdiplus::Rect rect;	// �簢��, 
	// �� �ȿ� �̹����� ��ﲨ ��ġ ���ϴ°Ŷ�� ���� �ɵ�
};

// GDI+, API, 
// DirectX-> D2D(2D�۾�, D3D�� ���� ���°�), 
//			 D3D(3D�۾�, 2D��� ����� �� ����)

// �̹��� �����ϸ� png�� ���°� ���� ������ �뷮�� ŭ
// bmp�� alpha���� ����, jpg�� format��ü�� �����ϰ� �Ǿ�����

class DrawImage
{
	// ���������� �Ƚ��ָ� private��
private:
	// 256 ���� ���� �� �ִ� ����
	// -127 ~ 128���� ���� 
	// unsigned ���̸� 0 ~ 255���� ����

	// �̹��� ���� ����
	Gdiplus::Image* image;	// �̹����� ���� ������ ��� Ŭ����
	// �׸��� �׸��µ� �ʿ��� �༮�� �������
	Gdiplus::Graphics* pGraphics;
	//direct������ d3d ��
	ULONG_PTR  gdiplusToken; // unsinged long ptr , �����ϴ� �༮,

	vector<tagImageInfo> images;
public:
	DrawImage();
	~DrawImage();

	// ȭ���� �����ִ� ����
	void Clear(int r, int g, int b);	
	// �̹��� �ҷ����� �༮
	void AddImage(WCHAR* fileName);		// WCHAR char��� �ϴ� ����
	void AddImage(WCHAR* fileName, Gdiplus::Rect rect);
	// �ҷ��� ���� �׸��� ��
	void Drawing(int x, int y);	
	void Drawing(int number);
	void Drawing(int number, Rect rect);

	vector<tagImageInfo>& GetImageInfo() { return images; }
};

