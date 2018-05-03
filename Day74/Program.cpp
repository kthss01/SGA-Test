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

	// FVF 정점에 데이터를 어떤 형식으로 쓸건지
	// position, color 이걸 임의적으로 한거라 알려줘야함
	// 구조체 들어간 순서와 동일하게 해줘야함
	// XYZ 포지션 DIFFUSE color
	// color값이랑 포지션 값을 꼭 넣어줘야함
	// texture 띄우려면 texture coord를 넣어줘야함
	// color 안넣어주면 실질적인 렌더는 안됨 좌표는 잇지만
	//D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	// texture 로 사용할때
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,		// 선임
		// 점도 있음 D3DPT_POINTLIST
		1, vertices, sizeof(Vertex)
	);
	/* lip 
		vertex 들어간게 [0][1][2][3] -> [0][1], [1][2], [2][3]
		ex) 삼각형 [0][1][2], [1][2][3] ...

	   list (list list~~)
		vertex 들어간게 [0][1][2][3] -> [0][1], [2][3]
		ex) 삼각형 [0][1][2], [3][4][5] ...
	*/

	for (int i = 0; i < 10; i++) {
		Matrix matWorld;
		Vector2 move(i * 10, i * 10);
		matWorld = Matrix::Translation(move);

		D2D::GetDevice()->SetTransform(
			D3DTS_WORLD, &matWorld.ToDXMatrix()
		);
		D2D::GetDevice()->DrawPrimitiveUP(
			D3DPT_LINELIST,		// 선임
								// 점도 있음 D3DPT_POINTLIST
			1, vertices, sizeof(Vertex)
		);
	}

	Vertex DrawRay[2];
	DrawRay[0].position = ray.origin;
	DrawRay[0].color = D3DXCOLOR(color);
	
	DrawRay[1].position = outPos;
	DrawRay[1].color = D3DXCOLOR(color);

	D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,		// 선임
							// 점도 있음 D3DPT_POINTLIST
		1, DrawRay, sizeof(Vertex)
	);

	for (int i = 0; i < 100; i++) {
		Vector2 rands = Vector2(rand() % 1000, rand() % 1000);
		rect->GetTransform()->SetWorldPosition(rands);
		rect->Render();
	}

}
