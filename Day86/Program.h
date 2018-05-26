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

	Vector2 mousePosWithScreen;
	float radius;
	bool isCheck;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 tempTex;

	LPD3DXSPRITE sprite;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	����1
	�ؽ�ó �о�ͼ� �ȼ� ������ üũ�ؼ� ������ �ƴѰ� ������ ȭ�鿡 ���

	����2
	�ϴÿ��� �簢�� �Ѹ� ������ ũ�� ���� ȸ�� �ؼ� ������
	�׿����� ȸ���� �����̸� �׹������� ����������
	�ٴڿ� ��ų� �ٸ��༮�� ������ ���߰Բ�
	���߿����� ���� �ȹ������
	�����մ� �ֵ鸸 �浹�ϰԲ�
*/