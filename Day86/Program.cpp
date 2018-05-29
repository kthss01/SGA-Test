#include "stdafx.h"
#include "Program.h"

#include "GameObject\Rect.h"
#include "Common\Camera.h"

Program::Program()
{
	srand(time(NULL));

	vertices = new Vertex[2];

	vertices[0].position = Vector2(25, -55);
	vertices[0].color = 0xFFFF0000;

	vertices[1].position = Vector2(-50, 25);
	vertices[1].color = 0xFFFF0000;

	D2D::GetDevice()->SetRenderState(
		// 라이트 지정
		D3DRS_LIGHTING,
		// 사용 여부
		FALSE
	);

	vEye = Vector2(0, 0);	// 카메라의 위치
	ray = Ray(Vector2(0, 0), Vector2(-1, 0));

	CreateRenderTargetTexture();

	wstring fileName = L"Textures/Robot/A2D Robot_";

	for (int i = 1; i <= 16; i++) {
		wstring fileNum = L"";
		if (i < 10) 
			fileNum += L"0" + to_wstring(i);
		else
			fileNum += to_wstring(i);

		wstring filePath = fileName + fileNum + L".png";

		LPDIRECT3DTEXTURE9 temp;
		D3DXIMAGE_INFO tempInfo;

		// imageinfo 사용하려면 필요
		D3DXCreateTextureFromFileEx(
			D2D::GetDevice(),
			filePath.c_str(),
			0,
			0,
			D3DX_DEFAULT,	// 기본값으로 설정하고 싶으면 default나 0이면 원본 사이즈
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT, // usage dynamic으로 설정 시
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			&tempInfo,
			NULL, // 색상값을 나타내는 팔렛트 256인지 32비트인지 모르면 null
			&temp 
		);

		vecImage.push_back(make_pair(temp, tempInfo));
	}

	mainCamera = new Camera;

	head = new Rect();
	//head->Init(L"./Shader/TextureMapping.fx", Vector2(1,1), Vector2(0,-50));
	head->Init(L"./Shader/TextureMapping.fx", Vector2(1,1));
	//head->GetTransform()->SetScale(Vector2(
	//		vecImage[0].second.Width / 100.0f / 10.0f, 
	//		vecImage[0].second.Height / 100.0f / 10.0f));

	radius = 0;
	isCheck = false;

	D3DXIMAGE_INFO info;
	D3DXCreateTextureFromFileEx(
		D2D::GetDevice(),
		L"./Textures/Box.png", // 원본 이미지 사이즈가 256 x 256
		NULL,
		NULL,
		NULL,
		D3DUSAGE_DYNAMIC,	// 읽어서 사용하려면 dynamic으로 써야함
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		//D3DX_DEFAULT,	// 이 두개 때문에 픽셀 사이에 처리가 이상해진거
		D3DX_FILTER_LINEAR,
		//D3DX_DEFAULT,	// 
		D3DX_FILTER_LINEAR,
		0xff000000,
		&info,
		NULL,
		&texture
	);
	// D3DXCreateTextureFromFile 함수로 텍스처 불러오면 이미지 크기가 4분의 1로 줄어듬

	head->SetTexture(texture);
	// 빈 텍스처 만들기
	D2D::GetDevice()->CreateTexture(
		256, 256, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, &tempTex, NULL
	);

	// LockRect 이용해서 텍스처가 가지고 있는 색상값 뽑아 쓸거
	// 실제 데이터 들어가는건 한줄로 들어가 있음
	// 이녀석의 총길이값 pitch 128 x 128 * 4 argb 순으로 쭉 들어감 
	// (텍스처에 따라 rgba일 수도 있음)
	D3DLOCKED_RECT lockRect;
	D3DLOCKED_RECT lockRect2;
	// pBits 실질적인 데이터, pitch 길이값이라고 보면됨 
	// texture를 읽는 용도로만 쓰는거
	texture->LockRect(0, &lockRect,
		NULL, // 이미지에서 가져올 width, height 설정하면됨 전체
		D3DLOCK_DISCARD); // NULL로하면 수정도 가능 read only는 읽기만

	DWORD* color = (DWORD*)lockRect.pBits;

	// data값 집어 넣는 용도
	//tempTex->LockRect(0, &lockRect2, NULL, D3DLOCK_DISCARD);

	//D3DXCOLOR* tempColor = (D3DXCOLOR*)lockRect2.pBits;

	D3DXCOLOR destColor;
	int index = 0;
	for (int i = 0; i < info.Width; i++) {
		for (int j = 0; j < info.Height; j++) {
			index = i * 256 + j;
			destColor = color[index];

			D3DXCOLOR sourColor;
			float gray = (destColor.r + destColor.g + destColor.b) / 3;

			sourColor.a = destColor.a;
			//sourColor.r = gray;
			//sourColor.g = gray;
			//sourColor.b = gray;
			sourColor.r = 1 - destColor.r;
			sourColor.g = 1 - destColor.g;
			sourColor.b = 1 - destColor.b;

			color[index] = sourColor;
		}
	}

	//tempTex->UnlockRect(0);
	texture->UnlockRect(0);

	D3DXCreateSprite(
		D2D::GetDevice(),
		&sprite
	);
}

Program::~Program()
{
	SAFE_DELETE_ARRAY(vertices);
	head->Release();
	SAFE_DELETE(head);

	SAFE_DELETE(mainCamera);

	for (int i = 0; i < vecImage.size(); i++)
		SAFE_RELEASE(vecImage[i].first);

	SAFE_RELEASE(texture);
	SAFE_RELEASE(tempTex);
	SAFE_RELEASE(sprite);
}

void Program::Update()
{
	head->GetTransform()->DefaultControl2();
	// Shader 사용할 때 굳이 안사용해도 됨
	mainCamera->UpdateCamToDevice();
	head->Update();

	if (INPUT->GetKey(VK_LBUTTON)) {
		Util::GetMousePosWithScreen(&mousePosWithScreen);
		isCheck = true;
		radius = 0;
	}
}

void Program::Render()
{
	head->Render(mainCamera);

	Vector2 center = Vector2(0, 0);

	GIZMO->Circle(
		center, 100.0f, 0xFF808000
	);

	if (isCheck) {
		radius += 5.0f;
		for (int i = 0; i < 100; i+=10) {
			if (radius - i > 0) {
				GIZMO->Circle(
					mousePosWithScreen, radius - i, 0xffff0000
				);
			}
		}
		if (radius > 50.0f)
			isCheck = false;
	}

	// 알파블렌드 제거하고 출력
	// sprite 카메라 행렬 영향 안받음
	//sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//{
	//	RECT rc = { 0, 0, 256, 256 };
	//	sprite->Draw(texture,
	//		&rc, // 출력하고 싶은 크기 및 영역)
	//		&D3DXVECTOR3(100, 100, 0), // 회전이 일어나는 중심점
	//		&D3DXVECTOR3(WINSIZE_X / 2, WINSIZE_Y / 2, 0), // 그려지는 위치
	//		0xffffffff);// 컬러값
	//}
	//sprite->End();
}

void Program::CreateRenderTargetTexture()
{
	int width = 512;
	int height = 512;

	// 그냥 텍스처 변수 만드는거
	D2D::GetDevice()->CreateTexture(
		width, height,
		1,
		D3DUSAGE_RENDERTARGET, // 사용 용도
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&pRenderTexture,
		NULL
	);

	// depth 와 stencil을 갖고 있는 surface 생성
	// 두 크기 동일해야됨 texture랑 surface
	D2D::GetDevice()->CreateDepthStencilSurface(
		width, height,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,				// 버퍼를 교체할때 이전 교체 내용을 저장하지 않을 것이냐
		&pRenderSurface,
		NULL
	);
}
