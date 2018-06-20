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
		L"Skydome.fx",
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
}

void MainGame::Update()
{
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
		&D3DXVECTOR3(0, 3, -5),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0)
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

	// ��ī�̵�
	this->pSkyDomeEffect->SetMatrix("matWorld", &world);
	this->pSkyDomeEffect->SetMatrix("matView", &view);
	this->pSkyDomeEffect->SetMatrix("matProjection", &projection);

	// ��ī�̵� ����
	UINT iPassNum = 0;
	this->pSkyDomeEffect->Begin(&iPassNum, 0);
	{
		for (int i = 0; i < iPassNum; i++) {
			this->pSkyDomeEffect->BeginPass(i);
			{
				pMeshSphere->DrawSubset(0);
			}			this->pSkyDomeEffect->EndPass();
		}
	}
	this->pSkyDomeEffect->End();
}
