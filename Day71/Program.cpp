#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	HRESULT hr;

	hr = D3DXCreateTextureFromFile
	(
		D2D::GetDevice(),
		L"Textures/Box.png",
		&texture
	);
	assert(SUCCEEDED(hr));

	vertices = new Vertex[6];

	vertices[0].position = Vector2(0, 100);
	//vertices[0].uv = Vector2(0, 1);
	vertices[0].uv = Vector2(0, 2);

	vertices[1].position = Vector2(0, 0);
	//vertices[1].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(0, 0);

	vertices[2].position = Vector2(100, 0);
	//vertices[2].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(2, 0);

	vertices[3].position = Vector2(0, 100);
	//vertices[3].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(0, 2);

	vertices[4].position = Vector2(100, 0);
	//vertices[4].uv = Vector2(1, 0);
	vertices[4].uv = Vector2(2, 0);

	vertices[5].position = Vector2(100, 100);
	//vertices[5].uv = Vector2(1, 1);
	vertices[5].uv = Vector2(2, 2);


	D2D::GetDevice()->SetRenderState
	(
		D3DRS_LIGHTING,
		FALSE
	);

	hr = D2D::GetDevice()->CreateVertexBuffer
	(
		sizeof(Vertex) * 6,				//정점의 총크기
		0,								//
		D3DFVF_XYZ | D3DFVF_TEX1,
		D3DPOOL_DEFAULT,
		&rect_vb,
		NULL
	);
	assert(SUCCEEDED(hr));

	void* vertexData = NULL;
	hr = rect_vb->Lock(0, sizeof(Vertex) * 6, &vertexData, NULL);
	assert(SUCCEEDED(hr));

	memcpy(vertexData, vertices, sizeof(Vertex) * 6);
	hr = rect_vb->Unlock();
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
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	D2D::GetDevice()->SetTexture(0, texture);
	D2D::GetDevice()->SetStreamSource(0, rect_vb, 0, sizeof(Vertex));
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	/*D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST, 1, vertices, sizeof(Vertex)
	);*/
	D2D::GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	//stride
}
