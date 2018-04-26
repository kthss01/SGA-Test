#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	vEye = Vector2(0, 0, 0);
	vLookAt = Vector2(0, 0, 1);
	vUp = Vector2(0, 1);

	hdc = GetDC(g_hWnd);
	memDC = CreateCompatibleDC(hdc);

	hBitMap = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hBitMap);

	/////////////////////////////////////////////////
	// ���� ó�� - ��ü�� ���� ũ�⸸ ����

	// �ﰢ�� �ΰ��� �簢�� ����

	vecVertex.push_back(Vector2(-50,  50));
	vecVertex.push_back(Vector2(-50, -50));
	vecVertex.push_back(Vector2( 50,  50));
	
	vecVertex.push_back(Vector2(-50, -50));
	vecVertex.push_back(Vector2( 50,  50));
	vecVertex.push_back(Vector2( 50, -50));

	matWorld = Matrix::Identity(4);
	matView = Matrix::View(vEye, vLookAt, vUp);
	// z���� 0.0 ~ 1.0 ������ �����ϱ� ���Ѱ�
	matProjection = Matrix::Ortho(0, WINSIZE_X, WINSIZE_Y, 0, 0.0f, 1.0f);
	matViewport = Matrix::Viewport(0, 0, WINSIZE_X, WINSIZE_Y, 0, 1);

	vBoxPos = Vector2(WINSIZE_X / 2, WINSIZE_Y / 2);
	Vector2 move = Vector2(200, 0);
	matChildTrans = Matrix::Translation(move);
	fAngle = 0.0f;

}


Program::~Program()
{
	ReleaseDC(g_hWnd, hdc);

	SelectObject(memDC, hOldBitmap);
	DeleteObject(hBitMap);
	DeleteDC(memDC);
}

void Program::Update()
{
	Matrix matTrans;
	Matrix matRotate;
	float fSpeed = 1.0f;

	// ȸ���� ���� ���� box�� y��
	Vector2 dirTo = Vector2(0, 1);

	matTrans = Matrix::Translation(vBoxPos);
	matRotate = Matrix::Rotate(fAngle);

	// coord �̵� �����ִ� �༮
	// ȸ���� �����ִ� �༮
	dirTo = dirTo.TransformNormal(matRotate);

	if (GetKeyState('W') & 0x8000) { 
		//vBoxPos.y += fSpeed; 
		vBoxPos = vBoxPos + dirTo * fSpeed;
	}
	if (GetKeyState('S') & 0x8000) { 
		//vBoxPos.y -= fSpeed; 
		vBoxPos = vBoxPos - dirTo * fSpeed;
	}
	if (GetKeyState('A') & 0x8000) { fAngle += 0.01f; }
	if (GetKeyState('D') & 0x8000) { fAngle -= 0.01f; }
	
	Matrix matScale = Matrix::Identity(4);

	// scale�� �Լ� �ȸ��� �������� ���� �ʿ�
	// scale�� �⺻���� 1��
	matScale[0][0] = 0.5f;	// ��ü�� ���� ���� ����
	matScale[1][1] = 3.0f;  // ��ü�� ���� ���� ����

	if (GetKeyState('Z') & 0x8000) {
		matScale[0][0] += 0.1f;	// ��ü�� ���� ���� ����
	}
	if (GetKeyState('X') & 0x8000) {
		matScale[0][0] -= 0.1f;	// ��ü�� ���� ���� ����
	}


	// SRT ������ �־������ -> Scale(ũ��) * Rotate(ȸ��) * Translate(�̵�)
	matWorld = matScale * matRotate * matTrans;
	matChild = matChildTrans * matWorld;
}

void Program::Render()
{
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	
	// ������ ����������
	// ������ �ؾ��ϴ� ���� ����, �� ������ο��߸� ��
	// �̹��� ���� �����غ��Ű� ���̷�Ʈ���� �����Ǿ�����
	// ���̷�Ʈ������ �־��ִ� ��
	Matrix matWVPV = matWorld * matView * matProjection * matViewport;

	// size_t ��ȣ�� ���� ����
	// ���� ��Ʈ���� �̵��ؼ� ������ ��ȯ �����ִ� ��
	for (size_t i = 0; i < vecVertex.size(); i += 3) {
		Vector2 v1 = vecVertex[i].TransformCoord(matWVPV);
		Vector2 v2 = vecVertex[i + 1].TransformCoord(matWVPV);
		Vector2 v3 = vecVertex[i + 2].TransformCoord(matWVPV);

		// ���� �׸� �� �ִ� ��� ��� �������� �׸���
		MoveToEx(memDC, v1.x, v1.y, NULL);
		LineTo(memDC, v2.x, v2.y);
		LineTo(memDC, v3.x, v3.y);
		LineTo(memDC, v1.x, v1.y);
	}

	// �ϳ��� ���� �� ���� ������ ���ð��� ������

	Matrix matWorld2 = Matrix::Identity(4);
	//matWVPV = matWorld2 * matView * matProjection * matViewport;
	matWVPV = matChild * matView * matProjection * matViewport;

	// size_t ��ȣ�� ���� ����
	// ���� ��Ʈ���� �̵��ؼ� ������ ��ȯ �����ִ� ��
	for (size_t i = 0; i < vecVertex.size(); i += 3) {
		Vector2 v1 = vecVertex[i].TransformCoord(matWVPV);
		Vector2 v2 = vecVertex[i + 1].TransformCoord(matWVPV);
		Vector2 v3 = vecVertex[i + 2].TransformCoord(matWVPV);

		// ���� �׸� �� �ִ� ��� ��� �������� �׸���
		MoveToEx(memDC, v1.x, v1.y, NULL);
		LineTo(memDC, v2.x, v2.y);
		LineTo(memDC, v3.x, v3.y);
		LineTo(memDC, v1.x, v1.y);
	}

	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, memDC, 0, 0, SRCCOPY);
}
