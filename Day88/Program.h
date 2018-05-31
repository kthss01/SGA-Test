#pragma once

// MainGame��� ���ư���

class Program
{
//private:
//	// �⺻������ ���� ������� vertex �ʿ�
//	struct Vertex {
//		Vector2 position;
//		float size;	// ������ ������ ������
//		//Vector2 uv;
//		DWORD color;
//
//		// PSIZE = point size
//		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
//	};
//
//private:
//	Vertex vertices[100];
//	LPDIRECT3DTEXTURE9 pTex;

private:

	LPDIRECT3DTEXTURE9 pTex;

	class ParticleEmitter* particle;
	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();
};

/*
	����1 
	���� ����

	����2
	���� ǥ��� -> �ı� ǥ������� ���� (���� �̿�)

	����3 
	���� ǥ��� �������� ����� ����

	���� ǥ���
	ex) 2 + 3 * (5 + 4 * 2) - 3 + 6

	���� ǥ��� 
	23542*+*+3-6+

	(4 * 2 + 5) * 3 + 2 - 3 + 6
	
	���� (�ڷ� ����) ���� ����� ����

	����
	���� ǥ��� �޾Ƽ�
	���� ǥ������� ������ ����� ����ϱ�
*/