#include "stdafx.h"
#include "Program.h"

#include "GameObject\Rect.h"
#include "Common\Camera.h"
#include "Common\ParticleEmitter.h"

Program::Program()
{
	srand(time(NULL));

	//for (int i = 0; i < 100; i++) {
	//	vertices[i].position = Vector2(
	//		(rand() % 1024) - 512, rand() % 10 - 10);
	//	vertices[i].size = 1.0f;
	//	vertices[i].color = 0xffffffff;
	//}
	//
	////vertices[0].position = Vector2(-100, 0);
	////vertices[1].position = Vector2(0, -100);
	////vertices[2].position = Vector2(100, 0);
	//
	////// 반지름이 50정도라고 생각하면됨
	////vertices[0].size = 10.0f;
	////vertices[1].size = 10.0f;
	////vertices[2].size = 10.0f;
	//
	////vertices[0].uv = Vector2(0, 1);
	////vertices[1].uv = Vector2(0.5f, 0);
	////vertices[2].uv = Vector2(1, 1);
	//
	////vertices[0].color = 0xffff0000;
	////vertices[1].color = 0xff00ff00;
	////vertices[2].color = 0xffffffff;
	//
	//
	//D3DXCreateTextureFromFile(
	//	D2D::GetDevice(),
	//	L"./Textures/snow.png",
	//	&pTex
	//);
	
	particle = new ParticleEmitter;

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);
	scales.push_back(5.0f);

	D3DXCreateTextureFromFile(
		D2D::GetDevice(), L"./Textures/Box.png", &pTex);

	particle->Init(
		100, 10.0f, 5.0f, 6.0f,
		Vector2(0, 5), Vector2(1, 6),
		Vector2(0, 5), Vector2(1, 10),
		30, 50, 0.5f, 0.8f, 1, 1, 
		colors, scales, 10.0f, 20.0f, pTex, false);

	mainCamera = new Camera;

	particle->StartEmission();
}

Program::~Program()
{
	SAFE_RELEASE(pTex);
	SAFE_DELETE(mainCamera)
}

void Program::Update()
{

	particle->Update();
	particle->GetTransform()->DefaultControl2();

	if (Input::Get()->GetKeyDown(VK_SPACE)) {
		particle->StopEmission();
	}

	//float time = Frame::Get()->GetFrameDeltaSec();
	//
	//for (int i = 0; i < 100; i++) {
	//	vertices[i].position.y += 100.0f * time;
	//}
}

void Program::Render()
{
	//// 포인트 관련 세팅
	//
	//D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//// Point에 스프라이트 집어넣겟다.-> 포인트 기준으로 이미지 띄우겠다.
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//// Point에 스케일 값을 집어넣겟다. -> 정점의 크기를 조절하겠다.
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//// 이거 때문에 안나온거 카메라 위치랑 
	//// 내가 움직일 때 포인터와 카메라의 위치 차이가 생김
	//// 카메라가 멀어질 때 얼마까지 포인트가 작아질건지
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSIZE_MIN, 0.0f);
	//// 설정 안하면 음수로 가서 뒤집혀짐
	//// 카메라로 줌 당길때 얼마까지 포인트가 확대될건지
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSIZE_MAX, 500.0f);
	//
	//// 출력되는 POINT size
	//// finalSize = 
	//// viewportHeight * POINT SIZE * sqrt(1 / (A + B(D) + C(D^2));
	//// 몰라도 상관은 없음
	//// 아래와 같이 하면 자연스러운 거리에 따른 스케일 값 
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_C, 1.0f);
	//// 2D에서는 이 공식이 안들어감
	//// viewportHeight값이 너무 커서 적용이 안됨
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_C, 0.0f);
	//
	//// 색상 세팅
	//// 컬러값에 텍스처가 갖고 있는 색상값 섞겠다.
	//// -> texture의 값 Diffuse(color) 섞는다.
	//// 쉐이더 사용하지 않고 텍스처 섞을 때 사용
	//
	//// 4장 섞는 법 0번에 2장 섞고 1번에 2장섞고 2번에 0,1 섞음 되는 식
	//
	//// 0번 공간에 설정 한다는거 
	//// ALPHAOP -> op = option , modulate 곱해서 섞겠다는거
	//// 더 할건지 곱할꺼 등 설정
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//// 섞을 색상 설정
	//// 한번에 세 개까지 섞을 수 있는데 잘 안하고 2개 섞고 
	//// 다음 스테이지에서 보통 섞음
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	//
	//// alpha blend 알파값 그대로 제거
	//// alpha test blend -> 0이 아니면 무조건 불투명하게 그리는거
	//D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	//// 알파 블렌드시 색을 태우고 싶을 때
	//// 알파 블렌드에 따라서 전체 색상을 조정하고 싶을 떄
	////D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	////// D3DBLEND_ONE 은 무조건 1.0으로 설정
	////// 이렇게 설정하면 첫번째 알파값으로 무조건 들어가게됨
	////D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	////// z buffer 값 쓰지 않는다는거
	////// 3D에서 조금 쓰게 됨 2D 때는 안씀
	////D2D::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//
	//D2D::GetDevice()->SetFVF(Vertex::FVF);
	//
	//// 텍스처 세팅
	//D2D::GetDevice()->SetTexture(0, pTex);
	//
	//// 정점 렌더
	//D2D::GetDevice()->DrawPrimitiveUP(
	//	D3DPT_POINTLIST, 100, vertices, sizeof(Vertex));
	//
	//// 렌더의 끝에서는 꼭 true,false 세팅 한거 원상 복귀 해줘야함
	//D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	mainCamera->UpdateCamToDevice();

	particle->Render();
	particle->GetTransform()->RenderGizmo();
}
