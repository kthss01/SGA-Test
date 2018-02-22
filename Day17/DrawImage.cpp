#include "DrawImage.h"



DrawImage::DrawImage()
{
	GdiplusStartupInput gdiplusStartupInput;	// gdiplus 시작하겠다
	gdiplusToken = NULL;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	pGraphics = new Graphics
	(GetDC(GetConsoleWindow()));
		// 내가 띄우고 싶은 창 지정 handle 번호로 지정
		// int보다 handle이 더 빨라서 handle 사용
}


DrawImage::~DrawImage()
{
	//delete image;
	for (int i = 0; i < images.size(); i++)
		delete images[i].image;
	images.clear();
	delete pGraphics;
	// gdiplus 그만 두겠다. startup으로 시작하면 이걸로 끝났다고 알려줘야함
	GdiplusShutdown(gdiplusToken);	
}

void DrawImage::Clear(int r, int g, int b)
{
	// 화면을 내가 지정한 r,g,b로 덮어버리겠다는 얘기임 지운다는게
	pGraphics->Clear(Color(r, g, b));
}

void DrawImage::AddImage(WCHAR * fileName)
{
	// 파일이름으로 새로운 이미지 생성
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
	// x,y가 지정된 좌표에 이미지 띄우겠다
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
