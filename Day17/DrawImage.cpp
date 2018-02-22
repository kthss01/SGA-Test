#include "DrawImage.h"



DrawImage::DrawImage()
{
	GdiplusStartupInput gdiplusStartupInput;	// gdiplus �����ϰڴ�
	gdiplusToken = NULL;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	pGraphics = new Graphics
	(GetDC(GetConsoleWindow()));
		// ���� ���� ���� â ���� handle ��ȣ�� ����
		// int���� handle�� �� ���� handle ���
}


DrawImage::~DrawImage()
{
	//delete image;
	for (int i = 0; i < images.size(); i++)
		delete images[i].image;
	images.clear();
	delete pGraphics;
	// gdiplus �׸� �ΰڴ�. startup���� �����ϸ� �̰ɷ� �����ٰ� �˷������
	GdiplusShutdown(gdiplusToken);	
}

void DrawImage::Clear(int r, int g, int b)
{
	// ȭ���� ���� ������ r,g,b�� ��������ڴٴ� ����� ����ٴ°�
	pGraphics->Clear(Color(r, g, b));
}

void DrawImage::AddImage(WCHAR * fileName)
{
	// �����̸����� ���ο� �̹��� ����
	image = new Image(fileName);
}

void DrawImage::AddImage(WCHAR * fileName, Gdiplus::Rect rect)
{
	tagImageInfo imageInfo;
	imageInfo.image = new Image(fileName);
	imageInfo.rect = rect;

	images.push_back(imageInfo);
}

void DrawImage::Drawing(int x, int y)
{
	// x,y�� ������ ��ǥ�� �̹��� ���ڴ�
	pGraphics->DrawImage(image, x, y);
}

void DrawImage::Drawing(int number)
{
	if (number > images.size()) return;

	pGraphics->DrawImage(images[number].image, images[number].rect);
}

void DrawImage::Drawing(int number, Rect rect)
{
	if (number > images.size()) return;

	pGraphics->DrawImage(images[number].image, rect);
}
