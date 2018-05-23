#include "stdafx.h"
#include "Gizmo.h"

Gizmo* Gizmo::instance = NULL;

Gizmo::Gizmo()
{
}

Gizmo::~Gizmo()
{
}

Gizmo * Gizmo::Get()
{
	if (instance == NULL)
		instance = new Gizmo;
	return instance;
}

void Gizmo::Delete()
{
	if(instance != NULL)
		SAFE_DELETE(instance);
}

// ���� �̵��ϰų� ȸ���ϴ��� �߾�(����)�� �پ��־�� ��
void Gizmo::Line(const Vector2 & startPos, const Vector2 & endPos, DWORD color) const
{
	D3DXMATRIX matPrevWorld;
	D2D::GetDevice()->GetTransform(D3DTS_WORLD, &matPrevWorld);

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);

	D2D::GetDevice()->SetTransform(D3DTS_WORLD, &matIdentity);

	// light�� ���⵵ ������ �ȵ�
	// ����� ������ �ִ� ���� �� �ǹ̰� ����
	// x(red), y(green), z(blue)�� ����ϱ�� �Ϲ������� �Ǿ����� 
	DWORD prevLight = 0;


	D2D::GetDevice()->GetRenderState(D3DRS_LIGHTING, &prevLight);

	D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	GIZMOVERTEX vertices[2];
	vertices[0].position = startPos;
	vertices[1].position = endPos;
	vertices[0].color = color;
	vertices[1].color = color;

	// �׸���
	// ���������� �̷��� �׸��� ������ ���ϰ� ������
	// �ʱ�ȭ ������Ʈ ���� 3���� �����ؼ� �� �� �ְ�
	// ������ ���� �� ���� �ϰ� ���� (�� �����Ӹ��� �� �ع�����)
	D2D::GetDevice()->SetFVF(GIZMOVERTEX::FVF);
	D2D::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST, 1, vertices, sizeof(GIZMOVERTEX));
	
	D2D::GetDevice()->SetTransform(D3DTS_WORLD, &matPrevWorld);
	D2D::GetDevice()->SetRenderState(D3DRS_LIGHTING, prevLight);
}

void Gizmo::Circle(Vector2 & centerPos, float radius, DWORD color) const
{
}

void Gizmo::AABBBox(const Vector2 & minPos, const Vector2 & maxPos, DWORD color) const
{
	this->Line(Vector2(minPos.x, minPos.y), Vector2(maxPos.x, minPos.y), color);
	this->Line(Vector2(maxPos.x, minPos.y), Vector2(maxPos.x, maxPos.y), color);
	this->Line(Vector2(maxPos.x, maxPos.y), Vector2(minPos.x, maxPos.y), color);
	this->Line(Vector2(minPos.x, maxPos.y), Vector2(minPos.x, minPos.y), color);
}
