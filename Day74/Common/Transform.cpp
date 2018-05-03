#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
	:pParent(NULL), pFirstChild(NULL), pNextSibling(NULL)
{
}

Transform::~Transform()
{
}

void Transform::AddChild(Transform * pChild)
{
}

void Transform::AttachTo(Transform * pParent)
{
}

void Transform::ReleaseParent()
{
}

void Transform::Reset(int resetFlag)
{
	if (resetFlag & RESET_POSITION) {
		this->position.x = 0;
		this->position.y = 0;
	}
	if (resetFlag & RESET_ROTATION) {
		this->right = Vector2(1, 0);
		this->up = Vector2(0, 1);
	}
	if (resetFlag & RESET_SCALE) {
		this->scale = Vector2(1, 1);
	}
}

void Transform::SetWorldPosition(Vector2 position)
{
	// �θ� �����ϸ� �θ� �������� �����ؾߵ�
	if (this->pParent != NULL) {
		// �θ��� ������� �������� 
		Matrix matInvParentFinal;
		float temp;
		matInvParentFinal = pParent->matFinal.Inverse(temp);

		// �ڽ��� matFinal�� �ڽ� ���� * �θ��� ����
		// ���� �θ��� ����ķ� ���� �ؾߵ�
		// ��� �� �ٽ� �θ� ���� ���ϴ°�
		
		// �θ��� ����İ���ŭ �̵�
		position = position.TransformCoord(matInvParentFinal);
	}
	this->position.x = position.x;
	this->position.y = position.y;

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::SetLocalPosition(Vector2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	
	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::MovePositionSelf(Vector2 position)
{
	// �̵� ����
	Vector2 move();

	// �ڽ��� �̵� ���� ��´�

	Vector2 moveAxis[2];


}

void Transform::MovePositionWorld(Vector2 delta)
{
}

void Transform::MovePositionLocal(Vector2 delta)
{
}

void Transform::SetScale(Vector2 scale)
{
	this->scale.x = scale.x;
	this->scale.y = scale.y;

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::SetScaling(Vector2 deltaScale)
{
	this->scale.x += deltaScale.x;
	this->scale.y += deltaScale.y;

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::RotateWorld(Vector2 angle)
{
}

void Transform::RotateSelf(Vector2 angle)
{
}

void Transform::RotateLocal(Vector2 angle)
{
}

void Transform::SetRotateWorld(const Matrix matWorldRotate)
{
}

void Transform::SetRotateLocal(const Matrix matLocalRotate)
{
}

void Transform::LookPosition(Vector2 pos, Vector2 up)
{
}

void Transform::UpdateTransform()
{
	// �ڽ��� ������ matLocal ����� ����
	this->matLocal = Matrix::Identity(4);
	this->matFinal = Matrix::Identity(4);

	// scale ���� ���� ��
	Vector2 scaledRight = this->right * this->scale.x;
	Vector2 scaledUp = this->up * this->scale.y;

	this->matFinal[0][0] = scaledRight.x;
	this->matFinal[0][1] = scaledRight.y;
	this->matFinal[1][0] = scaledUp.x;
	this->matFinal[1][1] = scaledUp.y;
	
	if (this->pParent == NULL) {
		this->matFinal = matLocal;
	}
}

Matrix Transform::GetFinalMatrix() const
{
	return matFinal;
}
