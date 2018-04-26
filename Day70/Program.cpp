#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	vertices = new Vertex[3];

	// ortho ���� ����
	//vertices[0].position = Vector2(0, 1);
	//vertices[0].color = 0xFFFF0000;

	//vertices[1].position = Vector2(1, 0);
	//vertices[1].color = 0xFF00FF00;

	//vertices[2].position = Vector2(-1, 0);
	//vertices[2].color = 0xFF0000FF;

	vertices[0].position = Vector2(0, 100);
	vertices[0].color = 0xFFFF0000;

	vertices[1].position = Vector2(0, 0);
	vertices[1].color = 0xFF00FF00;

	vertices[2].position = Vector2(100, 0);
	vertices[2].color = 0xFF0000FF;

	D2D::GetDevice()->SetRenderState(
		// ����Ʈ ����
		D3DRS_LIGHTING,
		// ��� ����
		FALSE
	);

	HRESULT hr;
	hr = D2D::GetDevice()->CreateVertexBuffer(
		sizeof(Vertex) * 3,				// ������ �� ũ��
		// default�� �ְ� dynamic�� ����
		// default�� cpu �Ⱦ��°�
		// dynamic���� �ϸ� ������ ��� �������� �� ���� (update���� ����)
		// �����ϴ°� ��ü�� �׷��ȿ� ���ϸ� �ɾ��༭ ���� �Ҽ��� ������ ������
		0,								// GPU ��� �߿� CPU �������
		D3DFVF_XYZ | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT,
		&vb,
		NULL							// ������ �Ⱦ�
	);
	// direct9 2010�⵵�� ���� �Ϸ�ǰ� ���׳� ������ fix��
	// �׷��� ���� �Ⱦ��°� ����
	assert(SUCCEEDED(hr));

	// ���� �ݴ°�
	// update���� ���̽��ָ� ������ ���ϰ� ����
	// �ʸ��� �̷� ���� ������ ���ϰ� �ɸ��ٴ°�
	// vertex ���� ���ϸ� �� ���� �ٽ� ���ۿ� �־������
	// ���� �ٸ� ���� 3�� �ʿ��ϸ� ���� 3�� �ʿ���
	void* vertexData = NULL;
	hr = vb->Lock(0, sizeof(Vertex) * 3, &vertexData, NULL);
	assert(SUCCEEDED(hr));

	memcpy(vertexData, vertices, sizeof(Vertex) * 3);
	hr = vb->Unlock();
	assert(SUCCEEDED(hr));
}

Program::~Program()
{
	SAFE_DELETE_ARRAY(vertices);
}

void Program::Update()
{
	Vector2 vEye(0, 0, 0);
	Vector2 vLookAt(0, 0, 1);
	Vector2 vUp(0, 1, 0);
	matView = Matrix::View(vEye, vLookAt, vUp);
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0, 1.0f);
}

void Program::Render()
{
	// ���������� ����ϴ°� Device�� �Ѱ��ְԵ�
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	D2D::GetDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));

	// FVF ������ �����͸� � �������� ������
	// position, color �̰� ���������� �ѰŶ� �˷������
	// ����ü �� ������ �����ϰ� �������
	// XYZ ������ DIFFUSE color
	// color���̶� ������ ���� �� �־������
	// texture ������ texture coord�� �־������
	// color �ȳ־��ָ� �������� ������ �ȵ� ��ǥ�� ������
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ���� �����ִ°� Primitive
	// CPU ����� �� ������ GPU ����� �ƴ�
	//D2D::GetDevice()->DrawPrimitiveUP(
	//	D3DPT_TRIANGLELIST,	// � ���·� �׸��ٴ� ����, �ﰢ�� ��
	//	1, // ��� �׸� ����
	//	vertices,	// ���� ����
	//	// 
	//	sizeof(Vertex)	// vertices �ȿ� ������ Vertex��ŭ �߶� �����ִ°�
	//);
	// stride �߶� �����ִ°�

	// GPU �̿��� ����
	// �ﰢ���� ������
	D2D::GetDevice()->DrawPrimitive(
		D3DPT_TRIANGLELIST, 
		0,		// ���° ���� �׸����� 
		1		// �ﰢ�� � �׸�����
	);
}
