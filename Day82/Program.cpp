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
			D3DX_DEFAULT,	// 기본값으로 설정하고 싶으면 default나 0이면 원본 사이즈
			0,
			0,
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
	head->Init(L"./Shader/TextureMapping.fx", Vector2(1,1), Vector2(0,-50));
	head->SetTexture(vecImage[0].first);
	head->GetTransform()->SetScale(Vector2(
			vecImage[0].second.Width / 100.0f, 
			vecImage[0].second.Height / 100.0f));
}

Program::~Program()
{
	SAFE_DELETE_ARRAY(vertices);
	head->Release();
	SAFE_DELETE(head);

	SAFE_DELETE(mainCamera);

	for (int i = 0; i < vecImage.size(); i++)
		SAFE_RELEASE(vecImage[i].first);
}

void Program::Update()
{
	head->GetTransform()->DefaultControl2();
	// Shader 사용할 때 굳이 안사용해도 됨
	mainCamera->UpdateCamToDevice();
	head->Update();
}

void Program::Render()
{
	head->Render(mainCamera);
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
