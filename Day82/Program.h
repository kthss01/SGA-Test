#pragma once

// MainGame��� ���ư���

class Program
{
private:
	// �⺻������ ���� ������� vertex �ʿ�
	struct Vertex {
		Vector2 position;
		DWORD color;
	};

	Vertex* vertices;
	Matrix matView;
	Matrix matProjection;
	// viewPort �ʿ���� 
	// ������ ���ڴٰ� ����� �������� window �������� �Ǿ�����
	Vector2 vEye;
	Vector2 outPos;

	Ray ray;

	float color[4];

	class Rect* head;
	class Rect* body;
	class Rect* lArm;
	class Rect* rArm;
	class Rect* lLeg;
	class Rect* rLeg;

	// �ؽ��� ���� ������ ������ ��
	LPDIRECT3DTEXTURE9 pRenderTexture;
	// �ؽ��� ���� ǥ�� (���� ����)
	LPDIRECT3DSURFACE9 pRenderSurface;

	vector< pair<LPDIRECT3DTEXTURE9, D3DXIMAGE_INFO> > vecImage;

	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	����
	transform �θ� �ڽ� ���� ��
	�簢�� ���µ� �Ӹ�, ����, ��2, �ٸ� 2�� �� �����
*/