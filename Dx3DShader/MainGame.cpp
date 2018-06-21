#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	// ������ ���� �󸶸�ŭ ����ϴ��� ���� ������� ���� ��
	D3DXCreateSphere(
		Util::Device,
		1.0f, // �� ������
		60, // ���� ������ �� 
		60, // ���� ������ ��
		&pMeshSphere,
		NULL // �Ⱦ��� �༮
	);

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlag = 0;

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(
		Util::Device,
		L"Shaders/Skydome.fx",
		NULL, 
		NULL,
		dwShaderFlag,
		NULL,
		&pSkyDomeEffect,
		&pError
	);

	if (pError != NULL) {
		MessageBoxA(NULL, (char*)pError->GetBufferPointer(), 
			"Shader Error", MB_OK);
		pError->Release();
		pError = 0;
	}

	D3DXCreateEffectFromFile(
		Util::Device,
		L"Shaders/VertexSpecular.fx",
		//L"Shaders/LambertLight.fx",
		NULL,
		NULL,
		dwShaderFlag,
		NULL,
		&pLightShader,
		&pError
	);

	if (pError != NULL) {
		MessageBoxA(NULL, (char*)pError->GetBufferPointer(),
			"Shader Error", MB_OK);
		pError->Release();
		pError = 0;
	}

	vLightDir = D3DXVECTOR3(1, 0, 0); // �����ʿ��� �������� ���ߴ� ��
	// ���࿡ ���� ������ �ٲٰ� �ʹٸ� normalize �������
	
	fAngleX = fAngleY = 0;
}

void MainGame::Release()
{
	if (pMeshSphere) {
		pMeshSphere->Release();
		pMeshSphere = 0;
	}
	
	if (pSkyDomeEffect) {
		pSkyDomeEffect->Release();
		pSkyDomeEffect = 0;
	}

	if (pLightShader) {
		pLightShader->Release();
		pLightShader = 0;
	}
}

void MainGame::Update()
{

	if (INPUT->GetKeyDown('W')) {
		fAngleY += 0.1f;
	}
	if (INPUT->GetKeyDown('S')) {
		fAngleY -= 0.1f;
	}

	if (INPUT->GetKeyDown('A')) {
		fAngleX -= 0.1f;
	}
	if (INPUT->GetKeyDown('D')) {
		fAngleX += 0.1f;
	}

	D3DXMATRIX matRotX;
	D3DXMatrixIdentity(&matRotX);
	D3DXMATRIX matRotY;
	D3DXMatrixIdentity(&matRotY);

	D3DXMatrixRotationX(&matRotX, fAngleX);
	D3DXMatrixRotationY(&matRotY, fAngleY);

	D3DXMATRIX matRot;
	matRot = matRotX * matRotY;

	D3DXVec3TransformNormal(&vLightDir, &vLightDir, &matRot);
	D3DXVec3Normalize(&vLightDir, &vLightDir);
}

void MainGame::Render()
{
	// ����
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	// ��
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(0, 0, -2), // ���� ��ġ
		&D3DXVECTOR3(0, 0, 1), // �ٶ󺸴� ����
		&D3DXVECTOR3(0, 1, 0) // �� ����
	);

	// Projection ����
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		60.0f, // ȭ�� ī�޶��� �Կ��ϴ� ������ ��������(�۾�����) Ȯ��, Ŀ���� ���
		(float)WINSIZE_X / (float)WINSIZE_Y, // 3d -> 2d�� �ٲܶ��� ȭ���� ��Ⱦ�� (���� Ⱦ�� ������)
		0.001f, // ����� ��
		1000.0f // �ָ��ִ� �� �̰� �ٿ��ָ� �� ������ �� �� �������� ����
	);

	Util::Device->Clear(
		0,		// û���� ���� D3DRECT �迭�� ���� (��ü = 0)
		NULL,	// û���� ���� D3DRECT �迭 ������
		D3DCLEAR_TARGET | // target�� ����ڴ� 
		D3DCLEAR_STENCIL | // stencil�� ����ڴ�
		D3DCLEAR_ZBUFFER, // zbuffer�� ����ڴ�
		0xff000000, // �÷� ���۸� ����� ä���� ����
		1.0f, // ���̹��� �ʱ�ȭ
		0 // ���Ľ� �ʱ�ȭ
	);

	Util::Device->BeginScene();

	// setworld �����Ŷ�� ���� ��
	D3DXMatrixTranslation(&world, 0, 0, -2);

	// ��ī�̵�
	this->pSkyDomeEffect->SetMatrix("matWorld", &world);
	this->pSkyDomeEffect->SetMatrix("matView", &view);
	this->pSkyDomeEffect->SetMatrix("matProjection", &projection);

	// rgba ��������
	this->pSkyDomeEffect->SetVector("vApexColor",
		&D3DXVECTOR4(0.0f, 0.45f, 0.66f, 1.0f));
	this->pSkyDomeEffect->SetVector("vCenterColor",
		&D3DXVECTOR4(0.81f, 0.38f, 0.66f, 1.0f));

	// ��ī�̵� ����
	Util::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Util::Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	UINT iPassNum = 0;
	this->pSkyDomeEffect->Begin(&iPassNum, 0);
	{
		for (int i = 0; i < iPassNum; i++) {
			this->pSkyDomeEffect->BeginPass(i);
			{
				pMeshSphere->DrawSubset(0);
			}			
			this->pSkyDomeEffect->EndPass();
		}
	}
	this->pSkyDomeEffect->End();
	Util::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	Util::Device->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ��
	D3DXMatrixIdentity(&world);
	pLightShader->SetMatrix("matWorld", &world);
	pLightShader->SetMatrix("matView", &view);
	pLightShader->SetMatrix("matProjection", &projection);

	pLightShader->SetVector("vColor", &D3DXVECTOR4(1, 0, 0, 1));
	pLightShader->SetVector("vLightDir", &D3DXVECTOR4(vLightDir, 1.0f));
	pLightShader->SetVector("vEyePos", &D3DXVECTOR4(0, 0, -2, 0));

	//pLightShader->SetMatrix("matInvWorld", &world);

	pLightShader->Begin(&iPassNum, NULL);
	{
		for (int i = 0; i < iPassNum; i++) {
			this->pLightShader->BeginPass(i);
			{
				pMeshSphere->DrawSubset(0);
			}
			pLightShader->EndPass();
		}
	}

	Util::Device->EndScene();
	Util::Device->Present(0, 0, 0, 0);
}
