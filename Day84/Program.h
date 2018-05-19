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
	����1 �ִϸ��̼�
	1. ĳ���� ����� �ΰ� ���콺 Ŭ���� ������ �����̰�
	2. ctrl + s�� ��� ������ vector< vector<transform> > (2��° ����)
		���� trasform ���� ��θ� vector�� �� �ְ� 
		�� vector�� 2��° vector�� �־�δ°�
		�̰Ÿ� �ϰ������ŭ �صΰ� (5�� ���� �̻�)
	3. �� vector ������ �����̰� (���� �ð��� ����) 
		���� Ȱ���ؼ�
	4. �ִϸ��̼� ����� �ݶ��̴� �߰��ؼ� ��ȣ�ۿ� �� �浹�ϰ�
	
	����2 ������ ���� �߰�
	5. ������ ���� ������µ� ������ ������ ������ �þ�Բ�

	����3
	5.5 IsOverlap ä��� (RectCollider�� �ϴ�)
	6. �ݶ��̴� �̿��ؼ� �߷°� �޾����� �ٴ� ó��
	  ���� �Ÿ� �Ѿ�� ȭ�� ������ �ȳ����� (����)
	  �������� ���� �� ���� ������ �� �ְ�
	  ������ ���� �� ���ʹ� �ٴ� �������
	  
	  * �ٴ��� AABBMinMax�̿��ؼ� �簢�� �浹 ���ָ� ��

	7. ������� xml ���� �� �����͸� �÷��ֽŰ� ��� ������� ����ϱ�
		(5.18(��) �������̳� ������ ��ħ �뿡 ī�信 �÷��ֽǲ�)
*/