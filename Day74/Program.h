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
public:
	Program();
	~Program();

	void Update();
	void Render();
};

