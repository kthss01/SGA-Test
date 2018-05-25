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
	//head->Init(L"./Shader/TextureMapping.fx", Vector2(1,1), Vector2(0,-50));
	head->Init(L"./Shader/TextureMapping.fx", Vector2(1,1));
	head->SetTexture(vecImage[0].first);
	//head->GetTransform()->SetScale(Vector2(
	//		vecImage[0].second.Width / 100.0f / 10.0f, 
	//		vecImage[0].second.Height / 100.0f / 10.0f));

	radius = 0;
	isCheck = false;

	D3DXCreateTextureFromFile(
		D2D::GetDevice(),
		L"./Textures/Box.png",
		&texture
	);

	// �� �ؽ�ó �����
	D2D::GetDevice()->CreateTexture(
		256, 256, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, &tempTex, NULL
	);

	// LockRect �̿��ؼ� �ؽ�ó�� ������ �ִ� ���� �̾� ����
	// ���� ������ ���°� ���ٷ� �� ����
	// �̳༮�� �ѱ��̰� pitch 128 x 128 * 4 argb ������ �� �� 
	// (�ؽ�ó�� ���� rgba�� ���� ����)
	D3DLOCKED_RECT lockRect;
	D3DLOCKED_RECT lockRect2;
	// pBits �������� ������, pitch ���̰��̶�� ����� 
	// texture�� �д� �뵵�θ� ���°�
	texture->LockRect(0, &lockRect,
		NULL, // �̹������� ������ width, height �����ϸ�� ��ü
		NULL); // NULL���ϸ� ������ ���� read only�� �б⸸

	D3DXCOLOR* color = (D3DXCOLOR*)lockRect.pBits;

	// data�� ���� �ִ� �뵵
	tempTex->LockRect(0, &lockRect2, NULL, NULL);

	D3DXCOLOR* tempColor = (D3DXCOLOR*)lockRect2.pBits;

	D3DXCOLOR destColor;
	int index = 0;
	for (int i = 0; i < lockRect.Pitch; i++) {
		destColor = color[i];
		tempColor[i].a = destColor.a;
		tempColor[i].r = destColor.r;
		tempColor[i].g = destColor.g;
		tempColor[i].b = destColor.b;
	}

	tempTex->UnlockRect(0);

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
	// Shader ����� �� ���� �Ȼ���ص� ��
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

	// ���ĺ��� �����ϰ� ���
	// sprite ī�޶� ��� ���� �ȹ���
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	{
		RECT rc = { 0, 0, 200, 200 };
		sprite->Draw(tempTex,
			&rc, // ����ϰ� ���� ũ�� �� ����)
			&D3DXVECTOR3(100, 100, 0), // ȸ���� �Ͼ�� �߽���
			&D3DXVECTOR3(WINSIZE_X / 2, WINSIZE_Y / 2, 0), // �׷����� ��ġ
			0xffffffff);// �÷���
	}
	sprite->End();
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
