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

	// GPU ����� �ϰ� ������
	// Graphic ī�尡 �� �� �ֵ��� ���������ִ°�
	// ���� �ְ������ʹ� ���� Ȯ���� �� �� ��� ���ذ� �����
	// ���� �ϳ��� ��
	LPDIRECT3DVERTEXBUFFER9 vb;

public:
	Program();
	~Program();

	void Update();
	void Render();
};

