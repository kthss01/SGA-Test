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
		// ����Ʈ ����
		D3DRS_LIGHTING,
		// ��� ����
		FALSE
	);

	HRESULT hr;
	hr = D2D::GetDevice()->CreateVertexBuffer(
		//sizeof(Vertex) * 3,				// ������ �� ũ��
		// �ﰢ���� �ƴ� �簢������ ����Ƿ� ���� �ʿ�
		sizeof(Vertex) * 7,				// ������ �� ũ��
		// default�� �ְ� dynamic�� ����
		// default�� cpu �Ⱦ��°�
		// dynamic���� �ϸ� ������ ��� �������� �� ���� (update���� ����)
		// �����ϴ°� ��ü�� �׷��ȿ� ���ϸ� �ɾ��༭ ���� �Ҽ��� ������ ������
		0,								// GPU ��� �߿� CPU �������
		// texture ���� �ٸ�
		//D3DFVF_XYZ | D3DFVF_DIFFUSE,	
		// 0���� ȭ�� ����ִ°ɷ� �̹� ����ϰ� ����
		D3DFVF_XYZ | D3DFVF_TEX1,	// 0�� ����ϸ� ���������� ����
		D3DPOOL_DEFAULT,
		&vb,
		NULL							// ������ �Ⱦ�
	);
	// direct9 2010�⵵�� ���� �Ϸ�ǰ� ���׳� ������ fix��
	// �׷��� ���� �Ⱦ��°� ����
	assert(SUCCEEDED(hr));

	// ���� �ݴ°�
	// update���� ���̽��ָ� ������ ���ϰ� ����
	// �ʸ��� �̷� ���� ������ ���ϰ� �ɸ��ٴ°�
	// vertex ���� ���ϸ� �� ���� �ٽ� ���ۿ� �־������
	// ���� �ٸ� ���� 3�� �ʿ��ϸ� ���� 3�� �ʿ���
	void* vertexData = NULL;
	//hr = vb->Lock(0, sizeof(Vertex) * 3, &vertexData, NULL);
	// �簢�� �׸��Ƿ�
	hr = vb->Lock(0, sizeof(Vertex) * 7, &vertexData, NULL);
	assert(SUCCEEDED(hr));

	//memcpy(vertexData, vertices, sizeof(Vertex) * 3);
	// �簢�� �׸��Ƿ�
	memcpy(vertexData, vertices, sizeof(Vertex) * 7);
	hr = vb->Unlock();
	assert(SUCCEEDED(hr));

	// index buffer
	hr = D2D::GetDevice()->CreateIndexBuffer(
		sizeof(DWORD) * 18,
		D3DUSAGE_WRITEONLY,	// ���� �뵵�θ� ����ϰڴ�
		D3DFMT_INDEX32,	// index ũ�� 4byte���̹Ƿ� 32
		//�������� �ʰ� �׳� ������ �� ���� �����ڴٴ°�
		D3DPOOL_DEFAULT, // �޸� ��� �����Ҳ���, 
		&ib,
		NULL
	);

	assert(SUCCEEDED(hr));
	void* pIndices = NULL;
	hr = ib->Lock(0, 0, &pIndices, 0);
	assert(SUCCEEDED(hr));

	// lock �ʹ� �������� �ϴ°� ������
	// memcpy ��õ
	memcpy(pIndices, indices, sizeof(DWORD) * 18);

	hr = ib->Unlock();
	assert(SUCCEEDED(hr));

	// texture load
	// d3d9�� �ִ°�
	//D2D::GetDevice()->CreateTexture() // texture load�� �ƴ϶� ������ִ°�
	// win api���� ���Ŷ� �ؼ� �ؾ���
	// CreateFile() // ���� ��ü�� �ҷ��ͼ� texture ���� �ؾߵ�  

	// ���ϻ󿡼� �ҷ��ͼ� ������ִ°� 
	hr = D3DXCreateTextureFromFile(
		D2D::GetDevice(),
		L"Textures/Box.png",
		&pTex
	);
	// �̹����� ���� ���� �ʿ��ϸ� (ex�� Ȯ����)
	// �ؽ�ó ���Ͽ��� �ҷ����µ� �ɼ��� �߰��ؼ� �ҷ����ٴٴ°�
	// �̳༮ �̿��ؼ� ����Ÿ ������ �� �� ����
	// ���ڿ��� Colorkey (���� �� ��, ����Ÿ�� �� �༮),
	// *pSrcInfo �̹����� ũ�� ���� ������ image�� ���� ���� ���°�
	// width, height�� �̹��� ��ü�� ũ�⸦ �������ִ°� �Ƚᵵ ��
	// �̹��� ���� ��� �ΰ��� ���� vertex �� sprite

	//D3DXCreateTextureFromFileEx();

	vEye = Vector2(0, 0);	// ī�޶��� ��ġ

	hr = D3DXCreateFont(
		D2D::GetDevice(),
		15,					// �ʺ�
		0,					// ����
		FW_BOLD,			// �β�, �β��� ���ڴٴ°�
		1,					// �� ���� ũ�� �ٲ� �� ����
		FALSE,				// ���Ÿ�ü ��� ����
		DEFAULT_CHARSET,	// �� ���� ũ�� �ٲ� �� ����
		OUT_DEFAULT_PRECIS,	// �ܰ��� ó��
		DEFAULT_QUALITY,	// ����Ƽ
		// FF_DONTCARE ���� ũ�� ������� ū �༮ �������� ����ִ°� �ʺ�� ���� �߿�
		DEFAULT_PITCH || FF_DONTCARE,		// �ɼ�, 
		L"����",
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
	// ī�޶� ����°�
	Vector2 vLookAt(0, 0, 1);	// �ٶ󺸴� ��ǥ��
	vLookAt = vEye + Vector2(0, 0, 1);
	Vector2 vUp(0, 1, 0);
	matView = Matrix::View(vEye, vLookAt, vUp);
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0, 1.0f);

	if (GetKeyState(VK_UP) & 0x8000) { vEye.y += 1.0f; }
	if (GetKeyState(VK_DOWN) & 0x8000) { vEye.y -= 1.0f; }
	// z�� �������� Ȯ�� ��Ҵ� ortho�� �ȵ�
	// �ʹ� ������ ���� ī�޶� �ڿ� �־ ���� �ȵ�
	// �ʹ� �ڷ� ���� near far ���� ����� ���� �ȵ�
	if (GetKeyState('Z') & 0x8000) { vEye.z -= 1.0f; }
	if (GetKeyState('X') & 0x8000) { vEye.z += 1.0f; }

	Util::GetMousePos(&mousePos);

	Vector2 position[7];

	Matrix matViewProj = matView * matProjection;

	for (int i = 0; i < 7; i++) {
		// world view projection ��������� �ٵ� ����� identity�� �Ȱ��ص� ��
		position[i] = vertices[i].position.TransformCoord(matViewProj);
	}

	check = false;
	check |= Collision::IntersectTri(position[0], position[1], position[2], mousePos);
	check |= Collision::IntersectTri(position[0], position[2], position[3], mousePos);
	check |= Collision::IntersectTri(position[0], position[3], position[4], mousePos);
	check |= Collision::IntersectTri(position[0], position[4], position[5], mousePos);
	check |= Collision::IntersectTri(position[0], position[5], position[6], mousePos);
	check |= Collision::IntersectTri(position[0], position[6], position[1], mousePos);

	// size�� ImVec2 ����ؾ���
	ImGui::Image(pTex, ImVec2(200, 200));

	ImGui::Checkbox("Sub Window", &subWindow);
	
	if (subWindow) {
		ImGui::Begin("Sub Window", &subWindow);
		ImGui::Text("Hello Sub Window �ѱ� �ȵ�");
		if (ImGui::Button("Close"))
			subWindow = false;
		ImGui::End();
	}
}

void Program::Render()
{
	// ���尪�� �ٲٸ� �浹 ����� �� �ȵ�
	// �̰� �ذ��Ϸ��� transcoord ����Ҷ� ���尪�� ����������
	//Matrix matWorld = Matrix::Identity(4);
	//matWorld[1][1] = 2.0f;
	//matWorld[2][2] = 2.0f;
	//D2D::GetDevice()->SetTransform(D3DTS_WORLD, &matWorld.ToDXMatrix());

	// ���������� ����ϴ°� Device�� �Ѱ��ְԵ�
	D2D::GetDevice()->SetTransform(D3DTS_VIEW, &matView.ToDXMatrix());
	D2D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection.ToDXMatrix());

	// vertex ���� �־���
	D2D::GetDevice()->SetStreamSource(0, vb, 0, sizeof(Vertex));

	// FVF ������ �����͸� � �������� ������
	// position, color �̰� ���������� �ѰŶ� �˷������
	// ����ü �� ������ �����ϰ� �������
	// XYZ ������ DIFFUSE color
	// color���̶� ������ ���� �� �־������
	// texture ������ texture coord�� �־������
	// color �ȳ־��ָ� �������� ������ �ȵ� ��ǥ�� ������
	//D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	// texture �� ����Ҷ�
	D2D::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	// ���� �̿�, �ε��� �̿� �簢�� �׸���
	// �ε��� ������ ����̽��� �־������
	D2D::GetDevice()->SetIndices(this->ib);
	D2D::GetDevice()->SetTexture(0, pTex);
	D2D::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, // �׸� ����
		0,	// ���� vertex �迭 �ε���
		0,	// �ּ� vertex ���� ��ȣ
		7,	// ������ ����
		0,	// ���� index �迭
		6	// �ﰢ���� ����
	);

	// RenderText
	RECT rc = { 10, 10, 0, 0 };

	// ��Ƽ����Ʈ�� DrawTextA
	font->DrawTextW(
		// �̹��� 2D ��ǥ���� ���°� sprite��� ��
		NULL,
		L"Render Text Test",
		-1,	// ��ü ������ -1, �ƴϸ� ���ڿ� ���̸�ŭ �ϸ��
		&rc,
		// DT_NOCLIP�� rc�� ������� ����ϰڴٴ°�
		// �̰ž��� rc�� 10,10�� ��ǥ ������ �Ǵ°�
		DT_LEFT | DT_NOCLIP, // �ɼ�, ���� ���ķ� �ϰڴٴ°�
		// 0x~~ �̰� �������� �Լ��� ����
		//D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		0xFFFF0000
	);

	rc.top += 20;
	wstring str;

	str = to_wstring(mousePos.x);
	str += L" , ";
	str += to_wstring(mousePos.y);

	// ��Ƽ����Ʈ�� DrawTextA
	font->DrawTextW(
		// �̹��� 2D ��ǥ���� ���°� sprite��� ��
		NULL,
		str.c_str(),
		-1,	// ��ü ������ -1, �ƴϸ� ���ڿ� ���̸�ŭ �ϸ��
		&rc,
		// DT_NOCLIP�� rc�� ������� ����ϰڴٴ°�
		// �̰ž��� rc�� 10,10�� ��ǥ ������ �Ǵ°�
		DT_LEFT | DT_NOCLIP, // �ɼ�, ���� ���ķ� �ϰڴٴ°�
							 // 0x~~ �̰� �������� �Լ��� ����
							 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		0xFFFF0000
	);

	rc.top += 20;
	if (check) {
		// ��Ƽ����Ʈ�� DrawTextA
		font->DrawTextW(
			// �̹��� 2D ��ǥ���� ���°� sprite��� ��
			NULL,
			L"�浹",
			-1,	// ��ü ������ -1, �ƴϸ� ���ڿ� ���̸�ŭ �ϸ��
			&rc,
			// DT_NOCLIP�� rc�� ������� ����ϰڴٴ°�
			// �̰ž��� rc�� 10,10�� ��ǥ ������ �Ǵ°�
			DT_LEFT | DT_NOCLIP, // �ɼ�, ���� ���ķ� �ϰڴٴ°�
								 // 0x~~ �̰� �������� �Լ��� ����
								 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			0xFFFF0000
		);
	}
	else {
		// ��Ƽ����Ʈ�� DrawTextA
		font->DrawTextW(
			// �̹��� 2D ��ǥ���� ���°� sprite��� ��
			NULL,
			L"���浹",
			-1,	// ��ü ������ -1, �ƴϸ� ���ڿ� ���̸�ŭ �ϸ��
			&rc,
			// DT_NOCLIP�� rc�� ������� ����ϰڴٴ°�
			// �̰ž��� rc�� 10,10�� ��ǥ ������ �Ǵ°�
			DT_LEFT | DT_NOCLIP, // �ɼ�, ���� ���ķ� �ϰڴٴ°�
								 // 0x~~ �̰� �������� �Լ��� ����
								 //D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			0xFFFF0000
		);
	}
}
