#include "stdafx.h"
#include "Rect.h"
#include "./Common/Camera.h"
#include "./Animation/AnimationClip.h"

Rect::Rect() {

}

Rect::~Rect() {

}

void Rect::Init()
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
		L"./Shader/TextureMapping.fx",
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

	vertice[0].position = Vector2(-50, 50);
	vertice[1].position = Vector2(-50, -50);
	vertice[2].position = Vector2(50, -50);
	vertice[3].position = Vector2(50, 50);

	//vertice[0].color = 0xffff0000;
	//vertice[1].color = 0xffffff00;
	//vertice[2].color = 0xff00ff00;
	//vertice[3].color = 0xff0000ff;
	vertice[0].uv = Vector2(0,1);
	vertice[1].uv = Vector2(0,0);
	vertice[2].uv = Vector2(1,0);
	vertice[3].uv = Vector2(1,1);

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

	hr = D3DXCreateTextureFromFile(
		D2D::GetDevice(),
		L"Textures/mario_all.png",
		//L"Textures/Box.png",
		&pTex
	);
	assert(SUCCEEDED(hr));

	deltaTime = 0.0f;

	mainCamera = new Camera;

	AnimationData data;
	clips = new AnimationClip;
	Json::Value* root = new Json::Value();
	
	for (int i = 0; i < 4; i++) {
		data.keyName = L"run_" + to_wstring(i);
		data.maxFrame = Vector2(8.0f, 4.0f);
		data.currentFrame = Vector2(float(i), 0.0f);
		clips->PushAnimationData(data);
		Json::SetValue(*root, "run_" + to_string(i), (float&)i);
	}

	WriteJsonData(L"Test.Json", root);

	Json::Value* ReadJson = new Json::Value();
	ReadJsonData(L"Test.Json", ReadJson);

	float temp;
	Json::GetValue(*ReadJson, "run_1", temp);
	
	// SAFE_RELEASE �� �Լ� release�� �ִ� �� Ȯ���ϸ��

}

void Rect::Release()
{
	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
	SAFE_RELEASE(pEffect);
	SAFE_RELEASE(pTex);

	SAFE_DELETE(transform);
	SAFE_DELETE(mainCamera);
	SAFE_DELETE(clips);

	SAFE_DELETE(ReadJson);
	SAFE_DELETE(root);
}

void Rect::Update()
{
	this->mainCamera->UpdateCamToDevice();
	this->transform->DefaultControl2();
	this->DrawInterface();
	clips->Update(AniRepeatType_Loop);
}

void Rect::Render()
{
	// ���ĺ��� ���ڴ� ������
	// ���� �׽�Ʈ ������ ����
	D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// SRCALPHA �ؽ�ó ���� ���°� 
	// ~dest �ؽ�ó �����徲�� �������� ���ĺ��� ����
	D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// dest ȭ�� ��Ÿ���°�
	D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �� ����� �ؽ�ó�� ���� ä�� ���̶� ��üȭ�鿡 ���� �� ���Ѱ�?

	//D2D::GetDevice()->SetTransform(D3DTS_WORLD, &transform->GetFinalMatrix().ToDXMatrix());

	this->pEffect->SetMatrix("matWorld", &transform->GetFinalMatrix().ToDXMatrix());
	this->pEffect->SetMatrix("matView", &mainCamera->GetViewMatrix().ToDXMatrix());
	this->pEffect->SetMatrix("matProjection", &mainCamera->GetProjection().ToDXMatrix());

	this->pEffect->SetVector("maxFrame", 
		&D3DXVECTOR4(
			clips->GetCurrentData().maxFrame.x, 
			clips->GetCurrentData().maxFrame.y, 
			0.0f, 0.0f));
	this->pEffect->SetVector("currentFrame", 
		&D3DXVECTOR4(
			clips->GetCurrentData().currentFrame.x, 
			clips->GetCurrentData().currentFrame.y,
			0.0f, 0.0f));

	this->pEffect->SetTexture("tex", pTex);

	this->pEffect->SetTechnique("MyShader");

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

	

	D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void Rect::DrawInterface()
{
	ImGui::Begin("Interface");
	{
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
