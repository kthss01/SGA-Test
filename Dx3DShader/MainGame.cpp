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
	// 디테일 면을 얼마만큼 사용하는지 면의 갯수라고 보면 됨
	D3DXCreateSphere(
		Util::Device,
		1.0f, // 구 반지름
		60, // 세로 디테일 값 
		60, // 가로 디테일 값
		&pMeshSphere,
		NULL // 안쓰는 녀석
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
	// 월드
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	// 뷰
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(0, 3, -5),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0)
	);

	// Projection 투영
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		60.0f, // 화각 카메라의 촬영하는 각도값 좁아지면(작아지며) 확대, 커지면 축소
		(float)WINSIZE_X / (float)WINSIZE_Y, // 3d -> 2d로 바꿀때의 화면의 종횡비 (종과 횡의 비율값)
		0.001f, // 가까운 값
		1000.0f // 멀리있는 값 이거 줄여주면 이 값보다 먼 값 렌더되지 않음
	);

	// 스카이돔
	this->pSkyDomeEffect->SetMatrix("matWorld", &world);
	this->pSkyDomeEffect->SetMatrix("matView", &view);
	this->pSkyDomeEffect->SetMatrix("matProjection", &projection);

	// 스카이돔 렌더
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
