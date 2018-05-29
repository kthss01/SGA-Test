#pragma once

// MainGame��� ���ư���

class Program
{
private:
	// �⺻������ ���� ������� vertex �ʿ�
	struct Vertex {
		Vector2 position;
		float size;	// ������ ������ ������
		//Vector2 uv;
		DWORD color;

		// PSIZE = point size
		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
	};

private:
	Vertex vertices[100];
	LPDIRECT3DTEXTURE9 pTex;

	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();
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