#include "stdafx.h"
#include "Rect.h"

Rect::Rect() {

}

Rect::~Rect() {

}

void Rect::Init()
{
	vertice[0].position = Vector2(-50, 50);
	vertice[1].position = Vector2(-50, -50);
	vertice[2].position = Vector2(50, -50);
	vertice[3].position = Vector2(50, 50);

	vertice[0].uv = Vector2(0,1/4);
	vertice[1].uv = Vector2(0,0);
	vertice[2].uv = Vector2(1/8,0);
	vertice[3].uv = Vector2(1/8,1/4);

	stride = sizeof(Vertex);
	FVF = D3DFVF_XYZ | D3DFVF_TEX1;

	HRESULT hr = D2D::GetDevice()->CreateVertexBuffer(
		stride * 4,
		D3DUSAGE_WRITEONLY,		// dynamic 쓰게 되면
		FVF,
		D3DPOOL_MANAGED,		// 이걸로 해줘야함 default 해주면 data 남아있지 않음
		&vb,
		NULL
	);
	assert(SUCCEEDED(hr));

	Vertex * pVertex = NULL;
	hr = vb->Lock(0, 0, (void**)&pVertex, 0);
	assert(SUCCEEDED(hr));
	memcpy(pVertex, vertice, stride * 4);
	hr = vb->Unlock();
	assert(SUCCEEDED(hr));

	DWORD indices[] = {
		0,1,2,
		0,2,3,
	};

	hr = D2D::GetDevice()->CreateIndexBuffer(
		sizeof(DWORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&ib,
		NULL
	);
	assert(SUCCEEDED(hr));

	void* pIndex;
	hr = ib->Lock(0, 0, &pIndex, 0);
	assert(SUCCEEDED(hr));
	memcpy(pIndex, indices, sizeof(DWORD) * 6);
	hr = ib->Unlock();
	assert(SUCCEEDED(hr));

	transform = new Transform;
	transform->UpdateTransform();

	hr = D3DXCreateTextureFromFile(
		D2D::GetDevice(),
		L"Textures/mario_all.png",
		&pTex
	);
	assert(SUCCEEDED(hr));

	deltaTime = 0.0f;
}

void Rect::Release()
{
	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
	SAFE_DELETE(transform);
}

void Rect::Update()
{
	deltaTime += Frame::Get()->GetFrameDeltaSec();
	int currentIndexX = rand() % 8;
	int currentIndexY = rand() % 4;

	if (deltaTime > 0.5f) {
		deltaTime = 0.0f;
		float tempX = (float)currentIndexX / 8.0f;
		float tempY = (float)currentIndexY / 4.0f;

		vertice[0].uv = Vector2(tempX, tempY + 1.0f/4.0f);
		vertice[1].uv = Vector2(tempX, tempY);
		vertice[2].uv = Vector2(tempX + 1.0f/8.0f, tempY);
		vertice[3].uv = Vector2(tempX + 1.0f/8.0f, tempY + 1.0f/4.0f);
	}

	Vertex * pVertex = NULL;
	HRESULT hr = vb->Lock(0, 0, (void**)&pVertex, 0);
	assert(SUCCEEDED(hr));
	memcpy(pVertex, vertice, stride * 4);
	hr = vb->Unlock();
	assert(SUCCEEDED(hr));

	this->transform->DefaultControl2();
	this->DrawInterface();
}

void Rect::Render()
{
	D2D::GetDevice()->SetStreamSource(0, vb, 0, stride);
	D2D::GetDevice()->SetIndices(ib);
	D2D::GetDevice()->SetTransform(D3DTS_WORLD, &transform->GetFinalMatrix().ToDXMatrix());
	D2D::GetDevice()->SetFVF(FVF);
	D2D::GetDevice()->SetTexture(0, pTex);

	D2D::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0, 0, 4, 0, 2);
}

void Rect::DrawInterface()
{
	ImGui::Begin("Interface");
	{
		transform->DrawInterface();
	}
	ImGui::End();
}
