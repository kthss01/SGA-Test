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
	////// �������� 50������� �����ϸ��
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
	//// ����Ʈ ���� ����
	//
	//D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//// Point�� ��������Ʈ ����ְٴ�.-> ����Ʈ �������� �̹��� ���ڴ�.
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//// Point�� ������ ���� ����ְٴ�. -> ������ ũ�⸦ �����ϰڴ�.
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//// �̰� ������ �ȳ��°� ī�޶� ��ġ�� 
	//// ���� ������ �� �����Ϳ� ī�޶��� ��ġ ���̰� ����
	//// ī�޶� �־��� �� �󸶱��� ����Ʈ�� �۾�������
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSIZE_MIN, 0.0f);
	//// ���� ���ϸ� ������ ���� ��������
	//// ī�޶�� �� ��涧 �󸶱��� ����Ʈ�� Ȯ��ɰ���
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSIZE_MAX, 500.0f);
	//
	//// ��µǴ� POINT size
	//// finalSize = 
	//// viewportHeight * POINT SIZE * sqrt(1 / (A + B(D) + C(D^2));
	//// ���� ����� ����
	//// �Ʒ��� ���� �ϸ� �ڿ������� �Ÿ��� ���� ������ �� 
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	////D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_C, 1.0f);
	//// 2D������ �� ������ �ȵ�
	//// viewportHeight���� �ʹ� Ŀ�� ������ �ȵ�
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALE_C, 0.0f);
	//
	//// ���� ����
	//// �÷����� �ؽ�ó�� ���� �ִ� ���� ���ڴ�.
	//// -> texture�� �� Diffuse(color) ���´�.
	//// ���̴� ������� �ʰ� �ؽ�ó ���� �� ���
	//
	//// 4�� ���� �� 0���� 2�� ���� 1���� 2�弯�� 2���� 0,1 ���� �Ǵ� ��
	//
	//// 0�� ������ ���� �Ѵٴ°� 
	//// ALPHAOP -> op = option , modulate ���ؼ� ���ڴٴ°�
	//// �� �Ұ��� ���Ҳ� �� ����
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//// ���� ���� ����
	//// �ѹ��� �� ������ ���� �� �ִµ� �� ���ϰ� 2�� ���� 
	//// ���� ������������ ���� ����
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	//D2D::GetDevice()->SetTextureStageState(
	//	0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	//
	//// alpha blend ���İ� �״�� ����
	//// alpha test blend -> 0�� �ƴϸ� ������ �������ϰ� �׸��°�
	//D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//
	//// ���� ����� ���� �¿�� ���� ��
	//// ���� ���忡 ���� ��ü ������ �����ϰ� ���� ��
	////D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////D2D::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	////// D3DBLEND_ONE �� ������ 1.0���� ����
	////// �̷��� �����ϸ� ù��° ���İ����� ������ ���Ե�
	////D2D::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	////// z buffer �� ���� �ʴ´ٴ°�
	////// 3D���� ���� ���� �� 2D ���� �Ⱦ�
	////D2D::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//
	//D2D::GetDevice()->SetFVF(Vertex::FVF);
	//
	//// �ؽ�ó ����
	//D2D::GetDevice()->SetTexture(0, pTex);
	//
	//// ���� ����
	//D2D::GetDevice()->DrawPrimitiveUP(
	//	D3DPT_POINTLIST, 100, vertices, sizeof(Vertex));
	//
	//// ������ �������� �� true,false ���� �Ѱ� ���� ���� �������
	//D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//D2D::GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//D2D::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	mainCamera->UpdateCamToDevice();

	particle->Render();
	particle->GetTransform()->RenderGizmo();
}
