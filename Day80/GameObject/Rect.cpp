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
	// 쉐이더 초기화
	// 에러값 확인이 어려우므로 
	// 쉐이더 로딩시 에러가 나면 에러 내용을 받아올 꺼
	LPD3DXBUFFER pError = NULL;

	// 쉐이더 옵션 지정
	DWORD shaderFlag = 0;
	// 지정되어야만 디버깅시 쉐이더 확인이 가능함
#ifdef _DEBUG
	shaderFlag |= D3DXSHADER_DEBUG;
#endif // _DEBUG

	// 쉐이더 내부에서 쓸 수 있는 게 #define, #include 
	D3DXCreateEffectFromFile(
		D2D::GetDevice(),			// 디바이스
		//L"./Shader/BaseColor.fx",	// 셰이더 파일
		L"./Shader/TextureMapping.fx",
		NULL,						// 셰이더 컴파일시 추가 #define
		NULL,						// 셰이더 컴파일시 추가 #include
		// include를 쓸 수 있는거
		// 외부에서 내부로 추가 할 수도 있음
		// 잘쓰진 않음
		shaderFlag,					// 셰이더 옵션
		NULL, // 셰이더 매개변수를 공유할 메모리풀
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
	
	// SAFE_RELEASE 는 함수 release가 있는 지 확인하면됨

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
	// 알파블렌더 쓰겠다 설정값
	// 알파 테스트 블렌더도 있음
	D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// SRCALPHA 텍스처 한장 쓰는거 
	// ~dest 텍스처 여러장쓰고 여러장의 알파블렌더 쓸때
	D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// dest 화면 나타내는거
	D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 이 방법은 텍스처에 알파 채널 값이라 전체화면에 알파 값 곱한거?

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

	// 셰이더로 렌더
	UINT iPassNum = 0;

	this->pEffect->Begin(
		&iPassNum,			// pEffect에 있는 패스 수를 받아온다.
		0					// 플래그 
	);
	{
		for (UINT i = 0; i < iPassNum; i++) {
			this->pEffect->BeginPass(i);
			{
				D2D::GetDevice()->SetStreamSource(0, vb, 0, stride);
				D2D::GetDevice()->SetIndices(ib);
				D2D::GetDevice()->SetFVF(FVF);
				// 만약에 텍스처 렌더하는 방식이면 pEffect->setTexture로
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
