#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	vertices = new Vertex[3];

	// ortho 쓰기 전에
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
		// 라이트 지정
		D3DRS_LIGHTING,
		// 사용 여부
		FALSE
	);

	HRESULT hr;
	hr = D2D::GetDevice()->CreateVertexBuffer(
		sizeof(Vertex) * 3,				// 정점의 총 크기
		// default가 있고 dynamic이 있음
		// default가 cpu 안쓰는거
		// dynamic으로 하면 정점을 계속 수정해줄 수 있음 (update에서 수정)
		// 포장하는거 자체가 그래픽에 부하를 걸어줘서 많이 할수록 프레임 떨어짐
		0,								// GPU 계산 중에 CPU 사용할지
		D3DFVF_XYZ | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT,
		&vb,
		NULL							// 지금은 안씀
	);
	// direct9 2010년도에 개발 완료되고 버그나 간간히 fix함
	// 그래서 요즘 안쓰는게 있음
	assert(SUCCEEDED(hr));

	// 열고 닫는거
	// update에다 많이써주면 프레임 저하가 생김
	// 십만개 이런 정도 넣으면 부하가 걸린다는거
	// vertex 값이 변하면 그 값을 다시 버퍼에 넣어줘야함
	// 도형 다른 종류 3개 필요하면 버퍼 3개 필요함
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
	// 실질적으로 계산하는건 Device로 넘겨주게됨
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	D2D::GetDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));

	// FVF 정점에 데이터를 어떤 형식으로 쓸건지
	// position, color 이걸 임의적으로 한거라 알려줘야함
	// 구조체 들어간 순서와 동일하게 해줘야함
	// XYZ 포지션 DIFFUSE color
	// color값이랑 포지션 값을 꼭 넣어줘야함
	// texture 띄우려면 texture coord를 넣어줘야함
	// color 안넣어주면 실질적인 렌더는 안됨 좌표는 잇지만
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// 렌더 시켜주는게 Primitive
	// CPU 계산이 들어간 렌더링 GPU 계산은 아님
	//D2D::GetDevice()->DrawPrimitiveUP(
	//	D3DPT_TRIANGLELIST,	// 어떤 형태로 그리겟다 라인, 삼각형 등
	//	1, // 몇개를 그릴 건지
	//	vertices,	// 정점 정보
	//	// 
	//	sizeof(Vertex)	// vertices 안에 정보를 Vertex만큼 잘라서 나눠주는거
	//);
	// stride 잘라 나눠주는거

	// GPU 이용한 렌더
	// 삼각형이 폴리곤
	D2D::GetDevice()->DrawPrimitive(
		D3DPT_TRIANGLELIST, 
		0,		// 몇번째 부터 그릴건지 
		1		// 삼각형 몇개 그릴건지
	);
}
