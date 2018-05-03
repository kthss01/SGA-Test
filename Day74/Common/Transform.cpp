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
	// 부모 존재하면 부모 기준으로 설정해야됨
	if (this->pParent != NULL) {
		// 부모의 최종행렬 뒤집은거 
		Matrix matInvParentFinal;
		float temp;
		matInvParentFinal = pParent->matFinal.Inverse(temp);

		// 자식의 matFinal은 자식 월드 * 부모의 월드
		// 따라서 부모이 역행렬로 제거 해야됨
		// 계산 후 다시 부모 월드 곱하는거
		
		// 부모의 역행렬값만큼 이동
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
	// 이동 벡터
	Vector2 move();

	// 자신의 이동 축을 얻는다

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
	// 자신의 정보로 matLocal 행렬을 갱신
	this->matLocal = Matrix::Identity(4);
	this->matFinal = Matrix::Identity(4);

	// scale 값을 가진 축
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
