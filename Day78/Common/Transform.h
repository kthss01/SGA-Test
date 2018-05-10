#pragma once

#define RESET_POSITION 1
#define RESET_ROTATION 2
#define RESET_SCALE 4

class Transform
{
protected:
	// ���� �ּҷ� ���̱� ������ (�������� �ּҰ� ����) 
	// axis[0]�̳� right�� ���� ���� ȣ���ϰԵ�
	// axis[1]�̳� up�̳� ���� ���� ȣ���ϰԵ�
	union {
		struct {
			Vector2 axis[2];
		};
		struct {
			Vector2 right;
			Vector2 up;
		};
	};

	// ��ġ��
	Vector2 position;
	// ũ�Ⱚ
	Vector2 scale;

	// ������� (���� ���)
	Matrix matFinal;

	// ȸ���̳� ������ ���� �� �ڵ����� Update������ ���� 
	bool bAutoUpdate;

	// ���� ���
	Matrix matLocal;

	Transform* pParent;	// �����ϸ� ���� ��ķ� �ٲ�

	Transform* pFirstChild;	// ù��° �ڽ�

	Transform* pNextSibling; // ���� �θ� ������ �ִ� ����


public:
	Transform();
	~Transform();

	// Parents
	// �� �ڽ����� Transform ���̴°�
	void AddChild(Transform* pChild);

	// �θ� �������ִ� �༮
	void AttachTo(Transform* pParent);

	// �θ� �ڽ� ���� ���� �����ִ� �༮
	void ReleaseParent();

	// Transform ���� �ʱ�ȭ -1�̸� ��ü �ʱ�ȭ
	// flag �ɼ��̶� �ǹ̵� ����
	void Reset(int resetFlag = -1);

	// ���� ��ǥ ����
	void SetWorldPosition(Vector2 position);
	// �θ� ���� ��� ���� ��ǥ�� ����, �θ� ���� �� ���� ��ǥ�� ��ȯ
	void SetLocalPosition(Vector2 position);
	// ������ �̵��ϴ°�, �ڱ� �ڽ� ���� �������� �����̴°�
	void MovePositionSelf(Vector2 delta);
	void MovePositionWorld(Vector2 delta);
	void MovePositionLocal(Vector2 delta);

	// scale
	// ũ�Ⱑ ���� �����̶�� �����
	void SetScale(Vector2 scale);
	// ���� ������ �ִ� �����ϰ��� + �����ִ°�
	void SetScaling(Vector2 deltaScale);

	// rotate
	void RotateWorld(Vector2 angle);
	// �ڱ� �ڽ� ������ ȸ��
	void RotateSelf(float angle);
	// �θ���� ��� ���� ���� �θ� ������ �θ� ����
	void RotateLocal(Vector2 angle);

	// ���� ����� �־ ȸ���� �� �༮
	void SetRotateWorld(const Matrix matWorldRotate);
	void SetRotateLocal(const Matrix matLocalRotate);

	// Rotation (����� ȸ�� == QUATERNION)
	
	// etc...
	// Ư�� ������ �ٶ󺸰Բ� ȸ��
	void LookPosition(Vector2 pos, Vector2 up = Vector2(0, 0, -1));

	void DefaultControl2();

	// Update()
	void UpdateTransform();

	// Get 
	Matrix GetFinalMatrix() const;	// ���� �� ���Ҷ��� �� ����

	Vector2 GetWorldPosition();

	// axis ���δ� �޾ƿ��°�
	void GetUnitAxis(Vector2* pVecArr) const;
	// ������ ��ȣ�� axis�� �޾ƿ��°�
	Vector2 GetUnitAxis(int axisNum) const;

	void DrawInterface();
};

