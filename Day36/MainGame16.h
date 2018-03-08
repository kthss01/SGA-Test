#pragma once

#include "GameNode.h"
#include "Image.h"

class MainGame16 : public GameNode
{
private:
	bool isDebug;

	// ���̽� ����

	float m_speed; // ����� , ����̹���, ��ǻ�� ����
	float m_carX;
	float m_carY;
	int m_endX, m_endY;	// ����ǿ��� ���� ���ο� ����

	Image* m_bg;
	Image* m_computer;
	Image* m_player;
	Image* m_circle;

	RECT m_rcPlayer;
	RECT m_rcComputer[5];
	float m_loopCount;

	bool m_isStart;
public:
	MainGame16();
	~MainGame16();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void PlayerMove();
	void ComputerMove();
};

/*
	api �� jpg png ��� ����
	gdiPlus �̿��ؼ� �ϴ°Ŷ� �� ����

	�̹��� �ε� �ӵ� �κ�
	API win32API -> bmp �⺻ ��� ���� -> CPU ������
										-> FPS (�ʴ� �� �������� ����ϴ���)
										-> �⺻ 60 ������

	GDI+ (GDI�� Ȯ�� ����)
	������ �̹����� �� ���� -> bmp, jpg, png-> CPU ������
										-> ������ ���� ������

	Direct2D -> bmp, jpg, png, dds-> GPU ������ ->
									gdi+ �� ����

	�ӵ�
	GDI+ < API < Direct2D

	�ڵ� (���̵�)
	API < GDI+ < Direct2D

	Direct2D ����
	imageLoad ���� (� �����̵� �о�� �� ����)
	�̹��� ������ ����
	 -> �ϳ��� �̹����� �̹��� �����ؼ� �ִϸ��̼� ǥ�� ����
	���̴� - ���� �����ִ� ȿ����� �����ϸ� ��
	Direct2D ����
	�ڵ差�� ���� 
	�ʱ�ȭ �Ҷ��� �ڵ� ���� �ʿ�
	���� �κ��� ���� ����
	������ Vector �� �⺻���� ����ϰ� �Ǽ�
	��� 

	������ ������ ����
	-> �⺻�� 9����
	1. ���� ������ ����
	2. cordinable ������ ����
	(���̴� ���� ���� ��ų ��)
	vertex ���̴�, pixel ���̴� ( hlsl ���)
	-> 11������ �ٲ�� ��

	3D ���� �����ؾ��� ��
	Directx -> �Լ� ���� ��� 
	float + Vector + matrix;
	3D ��ǥ ����
*/