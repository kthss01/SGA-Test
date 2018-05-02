#pragma once

// MainGame��� ���ư���

class Program
{
private:
	// �⺻������ ���� ������� vertex �ʿ�
	struct Vertex {
		Vector2 position;
		Vector2 uv;	// texture ��ǥ
		//DWORD color;
	};

	Vertex* vertices;
	DWORD* indices;		// �ε��� int�� �ص� �� word�� 2byte�̴� ����

	Matrix matView;
	Matrix matProjection;
	// viewPort �ʿ���� 
	// ������ ���ڴٰ� ����� �������� window �������� �Ǿ�����

	// GPU ����� �ϰ� ������
	// Graphic ī�尡 �� �� �ֵ��� ���������ִ°�
	// ���� �ְ������ʹ� ���� Ȯ���� �� �� ��� ���ذ� �����
	// ���� �ϳ��� ��
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;	// ������ ����

	LPDIRECT3DTEXTURE9 pTex;

	Vector2 vEye;

	LPD3DXFONT font;

	Vector2 mousePos;

	bool check;

	bool subWindow;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

