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

	vLightDir = D3DXVECTOR3(1, 0, 0); // 오른쪽에서 왼쪽으로 비추는 거
	// 만약에 빛의 방향을 바꾸고 싶다면 normalize 해줘야함
	
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
	// 월드
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	// 뷰
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(0, 0, -2), // 눈의 위치
		&D3DXVECTOR3(0, 0, 1), // 바라보는 방향
		&D3DXVECTOR3(0, 1, 0) // 윗 방향
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

	Util::Device->Clear(
		0,		// 청소할 영역 D3DRECT 배열의 갯수 (전체 = 0)
		NULL,	// 청소할 영역 D3DRECT 배열 포인터
		D3DCLEAR_TARGET | // target을 지우겠다 
		D3DCLEAR_STENCIL | // stencil을 지우겠다
		D3DCLEAR_ZBUFFER, // zbuffer를 지우겠다
		0xff000000, // 컬러 버퍼를 지우고 채워질 색상
		1.0f, // 깊이버퍼 초기화
		0 // 스탠실 초기화
	);

	Util::Device->BeginScene();

	// setworld 같은거라고 보면 됨
	D3DXMatrixTranslation(&world, 0, 0, -2);

	// 스카이돔
	this->pSkyDomeEffect->SetMatrix("matWorld", &world);
	this->pSkyDomeEffect->SetMatrix("matView", &view);
	this->pSkyDomeEffect->SetMatrix("matProjection", &projection);

	// rgba 순으로임
	this->pSkyDomeEffect->SetVector("vApexColor",
		&D3DXVECTOR4(0.0f, 0.45f, 0.66f, 1.0f));
	this->pSkyDomeEffect->SetVector("vCenterColor",
		&D3DXVECTOR4(0.81f, 0.38f, 0.66f, 1.0f));

	// 스카이돔 렌더
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

	// 모델
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
