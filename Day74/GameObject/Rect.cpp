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

	vertice[0].color = 0xFFFF0000;
	vertice[1].color = 0xFFFF0000;
	vertice[2].color = 0xFFFF0000;
	vertice[3].color = 0xFFFF0000;

	stride = sizeof(Vertex);
	FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	HRESULT hr = D2D::GetDevice()->CreateVertexBuffer(
		stride * 4,
		D3DUSAGE_WRITEONLY,		// dynamic ���� �Ǹ�
		FVF,
		D3DPOOL_MANAGED,		// �̰ɷ� ������� default ���ָ� data �������� ����
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
}

void Rect::Release()
{
	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
	SAFE_DELETE(transform);
}

void Rect::Update()
{
	for (int i = 0; i < 4; i++) {
		vertice[i].color = D3DXCOLOR(
			Util::GetRandomSeed(),
			Util::GetRandomSeed(),
			Util::GetRandomSeed(),
			1.0f);
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
