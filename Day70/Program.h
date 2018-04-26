#pragma once

// MainGame��� ���ư���

class Program
{
private:
	// �ӽ÷� ������ �Ἥ ����Ҳ���
	// Direct������ �ڵ������� �ʱ�ȭ�Ҷ� ����� �ڵ����� �������
	HDC hdc;
	HDC memDC;

	HBITMAP hOldBitmap, hBitMap;

	// ��ü�� ���� ������, ��ǥ ������ �� �ִ°�
	// ������ ����µ� �⺻ ����
	// ������� �����ָ� ������ ������ ����
	vector<Vector2> vecVertex;	// ���� ��ǥ

	Matrix matWorld;			// ���� ���
	Matrix matView;				// �� ���
	Matrix matProjection;		// ���� ���
	Matrix matViewport;			// ����Ʈ ���

	Vector2 vEye;				// ���� �Կ��ϰ� ���� ī�޶��� ��ġ
	Vector2 vLookAt;			// ���� �ٶ� ���
	// ī�޶� �������� �ʴ� �̻� ī�޶� ������ y 1
	Vector2 vUp;				// ī�޶��� ������

	// Box�� Rect�� ǥ���ϱ⵵ ��
	Vector2 vBoxPos;			// �ڽ��� ��ġ��
	float fAngle;				// ȸ�� ��Ű ���� ����

	Matrix matChild;
	Matrix matChildTrans;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

