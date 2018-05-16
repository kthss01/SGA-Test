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
		// ����Ʈ ����
		D3DRS_LIGHTING,
		// ��� ����
		FALSE
	);

	vEye = Vector2(0, 0);	// ī�޶��� ��ġ
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

		// imageinfo ����Ϸ��� �ʿ�
		D3DXCreateTextureFromFileEx(
			D2D::GetDevice(),
			filePath.c_str(),
			D3DX_DEFAULT,	// �⺻������ �����ϰ� ������ default�� 0�̸� ���� ������
			0,
			0,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT, // usage dynamic���� ���� ��
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			&tempInfo,
			NULL, // ������ ��Ÿ���� �ȷ�Ʈ 256���� 32��Ʈ���� �𸣸� null
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
	// Shader ����� �� ���� �Ȼ���ص� ��
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

	// �׳� �ؽ�ó ���� ����°�
	D2D::GetDevice()->CreateTexture(
		width, height,
		1,
		D3DUSAGE_RENDERTARGET, // ��� �뵵
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&pRenderTexture,
		NULL
	);

	// depth �� stencil�� ���� �ִ� surface ����
	// �� ũ�� �����ؾߵ� texture�� surface
	D2D::GetDevice()->CreateDepthStencilSurface(
		width, height,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,				// ���۸� ��ü�Ҷ� ���� ��ü ������ �������� ���� ���̳�
		&pRenderSurface,
		NULL
	);
}
