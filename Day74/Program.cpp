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
		// ����Ʈ ����
		D3DRS_LIGHTING,
		// ��� ����
		FALSE
	);

	vEye = Vector2(0, 0);	// ī�޶��� ��ġ
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

	// ī�޶� ����°�
	Vector2 vLookAt(0, 0, 1);	// �ٶ󺸴� ��ǥ��
	vLookAt = vEye + Vector2(0, 0, 1);
	Vector2 vUp(0, 1, 0);
	matView = Matrix::View(vEye, vLookAt, vUp);
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0, 1.0f);

	if (GetKeyState(VK_UP) & 0x8000) { ray.direction.y += 0.1f; }
	if (GetKeyState(VK_DOWN) & 0x8000) { ray.direction.y -= 0.1f; }
	if (GetKeyState(VK_RIGHT) & 0x8000) { ray.direction.x += 0.1f; }
	if (GetKeyState(VK_LEFT) & 0x8000) { ray.direction.x -= 0.1f; }

	// �������� �����ؾߵǱ� ������ normalize �ѹ� �������
	ray.direction = ray.direction.Normalize();

	Vector2 position[2];

	Matrix matViewProj = matView * matProjection;

	for (int i = 0; i < 2; i++) {
		// world view projection ��������� �ٵ� ����� identity�� �Ȱ��ص� ��
		position[i] = vertices[i].position.TransformCoord(matViewProj);
	}

	// outPos ȭ�� ��ǥ���� 2D��ǥ�� �ٽ� �ٲ��ֱ����� 
	// matVieProj�� ������� �����ִ� ��
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
	// ���������� ����ϴ°� Device�� �Ѱ��ְԵ�
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	// FVF ������ �����͸� � �������� ������
	// position, color �̰� ���������� �ѰŶ� �˷������
	// ����ü �� ������ �����ϰ� �������
	// XYZ ������ DIFFUSE color
	// color���̶� ������ ���� �� �־������
	// texture ������ texture coord�� �־������
	// color �ȳ־��ָ� �������� ������ �ȵ� ��ǥ�� ������
	//D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	// texture �� ����Ҷ�
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,		// ����
		// ���� ���� D3DPT_POINTLIST
		1, vertices, sizeof(Vertex)
	);
	/* lip 
		vertex ���� [0][1][2][3] -> [0][1], [1][2], [2][3]
		ex) �ﰢ�� [0][1][2], [1][2][3] ...

	   list (list list~~)
		vertex ���� [0][1][2][3] -> [0][1], [2][3]
		ex) �ﰢ�� [0][1][2], [3][4][5] ...
	*/

	for (int i = 0; i < 10; i++) {
		Matrix matWorld;
		Vector2 move(i * 10, i * 10);
		matWorld = Matrix::Translation(move);

		D2D::GetDevice()->SetTransform(
			D3DTS_WORLD, &matWorld.ToDXMatrix()
		);
		D2D::GetDevice()->DrawPrimitiveUP(
			D3DPT_LINELIST,		// ����
								// ���� ���� D3DPT_POINTLIST
			1, vertices, sizeof(Vertex)
		);
	}

	Vertex DrawRay[2];
	DrawRay[0].position = ray.origin;
	DrawRay[0].color = D3DXCOLOR(color);
	
	DrawRay[1].position = outPos;
	DrawRay[1].color = D3DXCOLOR(color);

	D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,		// ����
							// ���� ���� D3DPT_POINTLIST
		1, DrawRay, sizeof(Vertex)
	);

	for (int i = 0; i < 100; i++) {
		Vector2 rands = Vector2(rand() % 1000, rand() % 1000);
		rect->GetTransform()->SetWorldPosition(rands);
		rect->Render();
	}

}
