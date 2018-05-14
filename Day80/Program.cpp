#include "stdafx.h"
#include "Program.h"
#include "GameObject\Rect.h"

Program::Program()
{
	srand(time(NULL));

	rect = new Rect;
	rect->Init();

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
}

Program::~Program()
{
	SAFE_DELETE_ARRAY(vertices);
	rect->Release();
	SAFE_DELETE(rect);
}

void Program::Update()
{
	rect->Update();

	// 카메라 만드는거
	Vector2 vLookAt(0, 0, 1);	// 바라보는 좌표값
	vLookAt = vEye + Vector2(0, 0, 1);
	Vector2 vUp(0, 1, 0);
	matView = Matrix::View(vEye, vLookAt, vUp);
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0, 1.0f);

	if (GetKeyState(VK_UP) & 0x8000) { ray.direction.y += 0.1f; }
	if (GetKeyState(VK_DOWN) & 0x8000) { ray.direction.y -= 0.1f; }
	if (GetKeyState(VK_RIGHT) & 0x8000) { ray.direction.x += 0.1f; }
	if (GetKeyState(VK_LEFT) & 0x8000) { ray.direction.x -= 0.1f; }

	// 방향으로 지정해야되기 때문에 normalize 한번 해줘야함
	ray.direction = ray.direction.Normalize();

	Vector2 position[2];

	Matrix matViewProj = matView * matProjection;

	for (int i = 0; i < 2; i++) {
		// world view projection 곱해줘야함 근데 월드는 identity라 안곱해도 됨
		position[i] = vertices[i].position.TransformCoord(matViewProj);
	}

	// outPos 화면 좌표에서 2D좌표로 다시 바꿔주기위해 
	// matVieProj에 역행렬을 곱해주는 거
	if (Collision::IntersectRayToLine(
		ray,
		position[0],
		position[1],
		&outPos
	)) {
		float temp;
		Matrix invMatrix = matViewProj.Inverse(temp);

		outPos = outPos.TransformCoord(invMatrix);
	}

	ImGui::ColorEdit3("RayColor", color);
}

void Program::Render()
{
	// 실질적으로 계산하는건 Device로 넘겨주게됨
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	rect->Render();

	// 후면버퍼에 데이터를 보낼 녀석에 대한 정보값
	LPDIRECT3DSURFACE9 pDeviceTargetSurface;
	// stencil이랑 depth 저장할 녀석
	LPDIRECT3DSURFACE9 pDeviceDepthAndStencilSuface;

	D2D::GetDevice()->GetRenderTarget(0, &pDeviceTargetSurface);
	D2D::GetDevice()->GetDepthStencilSurface(
		&pDeviceDepthAndStencilSuface);

	LPDIRECT3DSURFACE9 texSurface = NULL;
	if (SUCCEEDED(this->pRenderTexture->
		GetSurfaceLevel(0, &texSurface))) {
		D2D::GetDevice()->SetRenderTarget(0, texSurface);
		SAFE_RELEASE(texSurface);
	}

	D2D::GetDevice()->SetDepthStencilSurface(pRenderSurface);

	D2D::GetDevice()->Clear(
		0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		0xFF00FF00,
		1.0f, 0);

	// beginScene endScene Present 안써도됨 텍스처에 바로 그리는거니
	rect->Render();

	D2D::GetDevice()->SetRenderTarget(0, pDeviceTargetSurface);
	D2D::GetDevice()->SetDepthStencilSurface(pDeviceDepthAndStencilSuface);

	SAFE_RELEASE(pDeviceDepthAndStencilSuface);
	SAFE_RELEASE(pDeviceTargetSurface);

	if (Input::Get()->GetKeyDown(VK_SPACE)) {
		D3DXSaveTextureToFile(
			L"Test.png",
			D3DXIFF_PNG,
			pRenderTexture,
			NULL
		);
	}
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
