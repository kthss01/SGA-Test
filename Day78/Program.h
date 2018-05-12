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

	class Rect* rect;

	// �ؽ��� ���� ������ ������ ��
	LPDIRECT3DTEXTURE9 pRenderTexture;
	// �ؽ��� ���� ǥ�� (���� ����)
	LPDIRECT3DSURFACE9 pRenderSurface;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	����
	������ �پ�ٴϰ� �����ϰ� �ϴ� �� �����ϱ�
*/

/*
	����
	1. ���̴� �̿��ؼ� �ִϸ��̼� 
	2. BaseColor + TextureMapping ���̴� ���Ŀ���
	�������� �ؽ�ó ������ �� ���̴��� ���������� �ɲ� ����
	3. �̴ϸ�
*/