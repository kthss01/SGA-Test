#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	vertices = new Vertex[7];

	vertices[0].position = Vector2(0, 0);
	vertices[0].uv = Vector2(0.5, 0.5);

	vertices[1].position = Vector2(-50, 25);
	vertices[1].uv = Vector2(0, 1);

	vertices[2].position = Vector2(-50, -25);
	vertices[2].uv = Vector2(0, 0);

	vertices[3].position = Vector2(0, -50);
	vertices[3].uv = Vector2(0.5, 0);

	vertices[4].position = Vector2(50, -25);
	vertices[4].uv = Vector2(1, 0);

	vertices[5].position = Vector2(50, 25);
	vertices[5].uv = Vector2(1, 1);

	vertices[6].position = Vector2(0, 50);
	vertices[6].uv = Vector2(0.5, 1);

	indices = new DWORD[18];

	int count = 0;
	for (int i = 1; i < 7; i++) {
		indices[count++] = 0;
		indices[count++] = i;
		indices[count++] = (i + 1);

		if (indices[count - 1] == 7) {
			indices[count - 1] = 1;
		}
	}

	D2D::GetDevice()->SetRenderState(
		// 라이트 지정
		D3DRS_LIGHTING,
		// 사용 여부
		FALSE
	);

	HRESULT hr;
	hr = D2D::GetDevice()->CreateVertexBuffer(
		//sizeof(Vertex) * 3,				// 정점의 총 크기
		// 삼각형이 아닌 사각형으로 만드므로 변경 필요
		sizeof(Vertex) * 7,				// 정점의 총 크기
		// default가 있고 dynamic이 있음
		// default가 cpu 안쓰는거
		// dynamic으로 하면 정점을 계속 수정해줄 수 있음 (update에서 수정)
		// 포장하는거 자체가 그래픽에 부하를 걸어줘서 많이 할수록 프레임 떨어짐
		0,								// GPU 계산 중에 CPU 사용할지
		// texture 쓰면 다름
		//D3DFVF_XYZ | D3DFVF_DIFFUSE,	
		// 0번은 화면 띄어주는걸로 이미 사용하고 있음
		D3DFVF_XYZ | D3DFVF_TEX1,	// 0번 사용하면 검정색으로 나옴
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
	//hr = vb->Lock(0, sizeof(Vertex) * 3, &vertexData, NULL);
	// 사각형 그리므로
	hr = vb->Lock(0, sizeof(Vertex) * 7, &vertexData, NULL);
	assert(SUCCEEDED(hr));

	//memcpy(vertexData, vertices, sizeof(Vertex) * 3);
	// 사각형 그리므로
	memcpy(vertexData, vertices, sizeof(Vertex) * 7);
	hr = vb->Unlock();
	assert(SUCCEEDED(hr));

	// index buffer
	hr = D2D::GetDevice()->CreateIndexBuffer(
		sizeof(DWORD) * 18,
		D3DUSAGE_WRITEONLY,	// 쓰기 용도로만 사용하겠다
		D3DFMT_INDEX32,	// index 크기 4byte형이므로 32
		//저장하지 않고 그냥 생성된 후 원본 날리겠다는거
		D3DPOOL_DEFAULT, // 메모리 어떻게 저장할꺼냐, 
		&ib,
		NULL
	);

	assert(SUCCEEDED(hr));
	void* pIndices = NULL;
	hr = ib->Lock(0, 0, &pIndices, 0);
	assert(SUCCEEDED(hr));

	// lock 너무 오래동안 하는거 안좋음
	// memcpy 추천
	memcpy(pIndices, indices, sizeof(DWORD) * 18);

	hr = ib->Unlock();
	assert(SUCCEEDED(hr));

	// texture load
	// d3d9에 있는거
	//D2D::GetDevice()->CreateTexture() // texture load가 아니라 만들어주는거
	// win api에서 배운거랑 해서 해야함
	// CreateFile() // 파일 자체를 불러와서 texture 만들어서 해야됨  

	// 파일상에서 불러와서 만들어주는거 
	hr = D3DXCreateTextureFromFile(
		D2D::GetDevice(),
		L"Textures/Box.png",
		&pTex
	);
	// 이미지에 대한 정보 필요하면 (ex가 확장임)
	// 텍스처 파일에서 불러오는데 옵션을 추가해서 불러오겟다는거
	// 이녀석 이용해서 마젠타 빼듯이 뺄 수 있음
	// 인자에서 Colorkey (내가 뺄 값, 마젠타로 뺄 녀석),
	// *pSrcInfo 이미지의 크기 높이 색상값이 image에 대한 정보 들어가는거
	// width, height는 이미지 자체의 크기를 설정해주는거 안써도 됨
	// 이미지 렌더 방식 두가지 있음 vertex 랑 sprite

	//D3DXCreateTextureFromFileEx();

	vEye = Vector2(0, 0);	// 카메라의 위치

	hr = D3DXCreateFont(
		D2D::GetDevice(),
		15,					// 너비
		0,					// 높이
		FW_BOLD,			// 두께, 두껍게 쓰겠다는거
		1,					// 이 둘은 크게 바꿀 꺼 없음
		FALSE,				// 이탤릭체 사용 여부
		DEFAULT_CHARSET,	// 이 둘은 크게 바꿀 꺼 없음
		OUT_DEFAULT_PRECIS,	// 외곽선 처리
		DEFAULT_QUALITY,	// 퀄리티
		// FF_DONTCARE 글자 크기 상관없이 큰 녀석 기준으로 잡아주는거 너비랑 높이 중에
		DEFAULT_PITCH || FF_DONTCARE,		// 옵션, 
		L"굴림",
		&font
	);
	assert(SUCCEEDED(hr));

	subWindow = false;
}

Program::~Program()
{
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(indices);

	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
}

void Program::Update()
{
	// 카메라 만드는거
	Vector2 vLookAt(0, 0, 1);	// 바라보는 좌표값
	vLookAt = vEye + Vector2(0, 0, 1);
	Vector2 vUp(0, 1, 0);
	matView = Matrix::View(vEye, vLookAt, vUp);
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0, 1.0f);

	if (GetKeyState(VK_UP) & 0x8000) { vEye.y += 1.0f; }
	if (GetKeyState(VK_DOWN) & 0x8000) { vEye.y -= 1.0f; }
	// z값 움직여서 확대 축소는 ortho라 안됨
	// 너무 앞으로 가면 카메라 뒤에 있어서 렌더 안됨
	// 너무 뒤로 가도 near far 구역 벗어나서 렌더 안됨
	if (GetKeyState('Z') & 0x8000) { vEye.z -= 1.0f; }
	if (GetKeyState('X') & 0x8000) { vEye.z += 1.0f; }

	Util::GetMousePos(&mousePos);

	Vector2 position[7];

	Matrix matViewProj = matView * matProjection;

	for (int i = 0; i < 7; i++) {
		// world view projection 곱해줘야함 근데 월드는 identity라 안곱해도 됨
		position[i] = vertices[i].position.TransformCoord(matViewProj);
	}

	check = false;
	check |= Collision::IntersectTri(position[0], position[1], position[2], mousePos);
	check |= Collision::IntersectTri(position[0], position[2], position[3], mousePos);
	check |= Collision::IntersectTri(position[0], position[3], position[4], mousePos);
	check |= Collision::IntersectTri(position[0], position[4], position[5], mousePos);
	check |= Collision::IntersectTri(position[0], position[5], position[6], mousePos);
	check |= Collision::IntersectTri(position[0], position[6], position[1], mousePos);

	// size는 ImVec2 사용해야함
	ImGui::Image(pTex, ImVec2(200, 200));

	ImGui::Checkbox("Sub Window", &subWindow);
	
	if (subWindow) {
		ImGui::Begin("Sub Window", &subWindow);
		ImGui::Text("Hello Sub Window 한글 안됨");
		if (ImGui::Button("Close"))
			subWindow = false;
		ImGui::End();
	}
}

void Program::Render()
{
	// 월드값을 바꾸면 충돌 계산이 잘 안됨
	// 이거 해결하려면 transcoord 계산할때 월드값도 계산해줘야함
	//Matrix matWorld = Matrix::Identity(4);
	//matWorld[1][1] = 2.0f;
	//matWorld[2][2] = 2.0f;
	//D2D::GetDevice()->SetTransform(D3DTS_WORLD, &matWorld.ToDXMatrix());

	// 실질적으로 계산하는건 Device로 넘겨주게됨
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	// vertex 정보 넣어줌
	D2D::GetDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));

	// FVF 정점에 데이터를 어떤 형식으로 쓸건지
	// position, color 이걸 임의적으로 한거라 알려줘야함
	// 구조체 들어간 순서와 동일하게 해줘야함
	// XYZ 포지션 DIFFUSE color
	// color값이랑 포지션 값을 꼭 넣어줘야함
	// texture 띄우려면 texture coord를 넣어줘야함
	// color 안넣어주면 실질적인 렌더는 안됨 좌표는 잇지만
	//D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	// texture 로 사용할때
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	// 버퍼 이용, 인덱스 이용 사각형 그리기
	// 인덱스 정보도 디바이스에 넣어줘야함
	D2D::GetDevice()->SetIndices(this->ib);
	D2D::GetDevice()->SetTexture(0, pTex);
	D2D::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, // 그릴 도형
		0,	// 시작 vertex 배열 인덱스
		0,	// 최소 vertex 시작 번호
		7,	// 정점의 갯수
		0,	// 시작 index 배열
		6	// 삼각형의 갯수
	);

	// RenderText
	RECT rc = { 10, 10, 0, 0 };

	// 멀티바이트면 DrawTextA
	font->DrawTextW(
		// 이미지 2D 좌표에서 띄우는걸 sprite라고 함
		NULL,
		L"Render Text Test",
		-1,	// 전체 띄우려면 -1, 아니면 문자열 길이만큼 하면됨
		&rc,
		// DT_NOCLIP이 rc에 상관없이 출력하겠다는거
		// 이거쓰면 rc의 10,10이 좌표 정도만 되는거
		DT_LEFT | DT_NOCLIP, // 옵션, 왼쪽 정렬로 하겠다는거
		// 0x~~ 이거 귀찮으면 함수도 있음
		//D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		0xFFFF0000
	);

	rc.top += 20;
	wstring str;

	str = to_wstring(mousePos.x);
	str += L" , ";
	str += to_wstring(mousePos.y);

	// 멀티바이트면 DrawTextA
	font->DrawTextW(
		// 이미지 2D 좌표에서 띄우는걸 sprite라고 함
		NULL,
		str.c_str(),
		-1,	// 전체 띄우려면 -1, 아니면 문자열 길이만큼 하면됨
		&rc,
		// DT_NOCLIP이 rc에 상관없이 출력하겠다는거
		// 이거쓰면 rc의 10,10이 좌표 정도만 되는거
		DT_LEFT | DT_NOCLIP, // 옵션, 왼쪽 정렬로 하겠다는거
							 // 0x~~ 이거 귀찮으면 함수도 있음
							 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		0xFFFF0000
	);

	rc.top += 20;
	if (check) {
		// 멀티바이트면 DrawTextA
		font->DrawTextW(
			// 이미지 2D 좌표에서 띄우는걸 sprite라고 함
			NULL,
			L"충돌",
			-1,	// 전체 띄우려면 -1, 아니면 문자열 길이만큼 하면됨
			&rc,
			// DT_NOCLIP이 rc에 상관없이 출력하겠다는거
			// 이거쓰면 rc의 10,10이 좌표 정도만 되는거
			DT_LEFT | DT_NOCLIP, // 옵션, 왼쪽 정렬로 하겠다는거
								 // 0x~~ 이거 귀찮으면 함수도 있음
								 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			0xFFFF0000
		);
	}
	else {
		// 멀티바이트면 DrawTextA
		font->DrawTextW(
			// 이미지 2D 좌표에서 띄우는걸 sprite라고 함
			NULL,
			L"안충돌",
			-1,	// 전체 띄우려면 -1, 아니면 문자열 길이만큼 하면됨
			&rc,
			// DT_NOCLIP이 rc에 상관없이 출력하겠다는거
			// 이거쓰면 rc의 10,10이 좌표 정도만 되는거
			DT_LEFT | DT_NOCLIP, // 옵션, 왼쪽 정렬로 하겠다는거
								 // 0x~~ 이거 귀찮으면 함수도 있음
								 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			0xFFFF0000
		);
	}
}
