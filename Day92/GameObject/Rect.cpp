#include "stdafx.h"
#include "Rect.h"
#include "./Common/Camera.h"
#include "./Animation/AnimationClip.h"

Rect::Rect() {

}

Rect::~Rect() {

}

void Rect::Init(wstring shaderFile, const Vector2 uv, const Vector2 pivot)
{
	// ���̴� �ʱ�ȭ
	// ������ Ȯ���� �����Ƿ� 
	// ���̴� �ε��� ������ ���� ���� ������ �޾ƿ� ��
	LPD3DXBUFFER pError = NULL;

	// ���̴� �ɼ� ����
	DWORD shaderFlag = 0;
	// �����Ǿ�߸� ������ ���̴� Ȯ���� ������
#ifdef _DEBUG
	shaderFlag |= D3DXSHADER_DEBUG;
#endif // _DEBUG

	// ���̴� ���ο��� �� �� �ִ� �� #define, #include 
	D3DXCreateEffectFromFile(
		D2D::GetDevice(),			// ����̽�
		//L"./Shader/BaseColor.fx",	// ���̴� ����
		//L"./Shader/TextureMapping.fx",
		//L"./Shader/MultiTexture.fx",
		shaderFile.c_str(),
		NULL,						// ���̴� �����Ͻ� �߰� #define
		NULL,						// ���̴� �����Ͻ� �߰� #include
		// include�� �� �� �ִ°�
		// �ܺο��� ���η� �߰� �� ���� ����
		// �߾��� ����
		shaderFlag,					// ���̴� �ɼ�
		NULL, // ���̴� �Ű������� ������ �޸�Ǯ
		&pEffect,
		&pError
	);

	if (pError != NULL) {
		string lastError = (char*)pError->GetBufferPointer();

		MessageBox(NULL, String::StringToWString(lastError).c_str(),
			L"Shader Error", MB_OK);
		SAFE_RELEASE(pError);
	}

	vertice[0].position = Vector2(-50 + pivot.x,  50 + pivot.y);
	vertice[1].position = Vector2(-50 + pivot.x, -50 + pivot.y);
	vertice[2].position = Vector2( 50 + pivot.x, -50 + pivot.y);
	vertice[3].position = Vector2( 50 + pivot.x,  50 + pivot.y);

	//vertice[0].color = 0xffff0000;
	//vertice[1].color = 0xffffff00;
	//vertice[2].color = 0xff00ff00;
	//vertice[3].color = 0xff0000ff;
	vertice[0].uv = Vector2(0,uv.y);
	vertice[1].uv = Vector2(0,0);
	vertice[2].uv = Vector2(uv.x,0);
	vertice[3].uv = uv;

	stride = sizeof(Vertex);
	//FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	FVF = D3DFVF_XYZ | D3DFVF_TEX1;

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

	pTexture = NULL;

	for (int i = 0; i < 100; i++) {
		tempTrans[i] = new Transform;
	}

	tempTrans[0]->SetWorldPosition(Vector2(200, 100));

	Vector2 center = Vector2(0, 0);
	Vector2 halfSize = center - (vertice[0].position - pivot);

	halfSize.x = abs(halfSize.x);
	halfSize.y = abs(halfSize.y);

	this->collider = new RectCollider;
	//this->collider = new CircleCollider;
	this->collider->SetBound(&center, &halfSize);

	tempCollider = new RectCollider;
	//tempCollider = new CircleCollider;
	tempCollider->SetBound(&center, &halfSize);
}

void Rect::Release()
{
	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
	SAFE_RELEASE(pEffect);

	SAFE_DELETE(transform);

	for (int i = 0; i < 100; i++)
		SAFE_DELETE(tempTrans[i]);

	SAFE_DELETE(collider);
	SAFE_DELETE(tempCollider);
}

void Rect::Update()
{
	this->transform->DefaultControl2();
	this->DrawInterface();

	//tempTrans[0]->PositionLerp(this->tempTrans[0], 
	//	transform, Frame::Get()->GetFrameDeltaSec() * 10.0f);
	//for (int i = 1; i < 100; i++) {
	//	tempTrans[i]->PositionLerp(
	//		this->tempTrans[i],
	//		tempTrans[i - 1], 
	//		// �� ���� 1�� ������ �پ ������
	//		Frame::Get()->GetFrameDeltaSec() * 10.0f);
	//}

	//tempTrans[0]->Interpolate(this->tempTrans[0],
	//	transform, Frame::Get()->GetFrameDeltaSec() * 10.0f);
	//for (int i = 1; i < 100; i++) {
	//	tempTrans[i]->Interpolate(
	//		this->tempTrans[i],
	//		tempTrans[i - 1],
	//		// �� ���� 1�� ������ �پ ������
	//		Frame::Get()->GetFrameDeltaSec() * 10.0f);
	//}

	Vector2 mouse;
	Util::GetMousePos(&mouse);

	check = Collision::IntersectTri(
		vertice[0].position,
		vertice[1].position,
		vertice[2].position,
		this->transform,
		mouse
	);

	colliderCheck = Collision::IsOverlap(
		this->transform,
		this->collider,
		this->tempTrans[0],
		this->tempCollider
	);
}

void Rect::Render(class Camera * mainCamera)
{
	// ���ĺ��� ���ڴ� ������
	// ���� �׽�Ʈ ������ ����
	//D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//// SRCALPHA �ؽ�ó ���� ���°� 
	//// ~dest �ؽ�ó �����徲�� �������� ���ĺ��� ����
	//D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//// dest ȭ�� ��Ÿ���°�
	//D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �� ����� �ؽ�ó�� ���� ä�� ���̶� ��üȭ�鿡 ���� �� ���Ѱ�?

	//D2D::GetDevice()->SetTransform(D3DTS_WORLD, &transform->GetFinalMatrix().ToDXMatrix());

	this->pEffect->SetMatrix("matView", &mainCamera->GetViewMatrix().ToDXMatrix());
	this->pEffect->SetMatrix("matProjection", &mainCamera->GetProjection().ToDXMatrix());

	if(pTexture != NULL)
		this->pEffect->SetTexture("tex", pTexture);

	this->pEffect->SetTechnique("MyShader");

	this->pEffect->SetMatrix("matWorld", &transform->GetFinalMatrix().ToDXMatrix());
	this->RenderRect();

	for (int i = 0; i < 100; i++) {
		this->pEffect->SetMatrix("matWorld", &tempTrans[i]->GetFinalMatrix().ToDXMatrix());
		this->RenderRect();
	}

	D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	transform->RenderGizmo(true);
	collider->RenderGizmo(transform);
	tempCollider->RenderGizmo(tempTrans[0]);
}

void Rect::RenderRect()
{
	// ���̴��� ����
	UINT iPassNum = 0;

	this->pEffect->Begin(
		&iPassNum,			// pEffect�� �ִ� �н� ���� �޾ƿ´�.
		0					// �÷��� 
	);
	{
		for (UINT i = 0; i < iPassNum; i++) {
			this->pEffect->BeginPass(i);
			{
				D2D::GetDevice()->SetStreamSource(0, vb, 0, stride);
				D2D::GetDevice()->SetIndices(ib);
				D2D::GetDevice()->SetFVF(FVF);
				// ���࿡ �ؽ�ó �����ϴ� ����̸� pEffect->setTexture��
				//D2D::GetDevice()->SetTexture(0, pTex);

				D2D::GetDevice()->DrawIndexedPrimitive(
					D3DPT_TRIANGLELIST,
					0, 0, 4, 0, 2);
			}
			this->pEffect->EndPass();
		}
	}

	this->pEffect->End();
}

void Rect::SetTexture(LPDIRECT3DTEXTURE9 tex)
{
	this->pTexture = tex;
}

void Rect::DrawInterface()
{
	ImGui::Begin("Interface");
	{
		if (check) {
			ImGui::Text("Mouse Check True");
		}
		else {
			ImGui::Text("Mouse Check False");
		}

		if (colliderCheck) {
			ImGui::Text("Collider Check True");
		}
		else {
			ImGui::Text("Collider Check False");
		}

		transform->DrawInterface();
	}
	ImGui::End();
}

void Rect::WriteJsonData(wstring fileName, Json::Value * root)
{
	ofstream stream;
	string temp = String::WStringToString(fileName);
	stream.open(temp); 
	{
		Json::StyledWriter writer;
		stream << writer.write(*root);
	}
	stream.close();
}

void Rect::ReadJsonData(wstring fileName, Json::Value * root)
{
	ifstream stream;
	stream.open(fileName);
	{
		Json::Reader reader;
		reader.parse(stream, *root);
	}
	stream.close();
}
