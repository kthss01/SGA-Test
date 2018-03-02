#pragma once

#include "GameNode.h"

class MainGame13 : public GameNode
{
private:
	Image * m_rockman;	// �ϸ� ������ �̹���
	int m_indexX;
	int m_indexY;
	bool m_isLeft;

	// DWORD 4����Ʈ�� �Ǿ��ִ� ������ �ȵ� ����
	// int, float char �� ���� �� ���� ������ �ȵ�
	// DWORD ��� �ϴ� ��� 
	// Color�� ���� �� ���� �� RGBA ��
	// ���� �����Ϸ� �Ҷ� index
	// �ð� ���� ��
	DWORD prevTime;		
	DWORD curTime;

	int posX, posY;	// ��ġ ��
public:
	MainGame13();
	~MainGame13();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

};

/*
	����
	���� �� �����
	��ġ�� ������ ����°�
	������ �����ϰ� ���� ������ �ö󰡴�

	�Լ� ä������
	Image Ŭ������ �ۼ��� �� ���� �̰ſ� ���� �Լ��� ä������

	// ����
	// Get, Set �Լ��� �� ����� ���� 
	// �̹����� ��ǥ X
	inline float GetX() { return m_imageInfo->x; }
*/

