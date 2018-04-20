#pragma once

#include "GameNode.h"

//#define SUBWINOPEN 1

class MainGame : public GameNode
{
private:
	bool isDebug;

public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	����
	���̼ҿ� �̹��� Ÿ�� ���� �ؿ���
*/

/*
	�� ����
	���̼ҿ� ���� ó�� �ϱ�
	�� ����
	���̼ҿ� A Star �����ϱ�
*/

/*
	����
	iso + maptool �ϱ�
*/

/*
	�ָ� ����
	1�� ���̼� ��Ʈ���� aStar ����
	2�� 16�� �̹��� ���콺 Ŭ������ �̵���Ű��
	3�� ���콺 �̹��� Ŀ�� �����ϱ� 
		�Լ��� ���� ���� Ŀ�� �����ִ°� ������ ����
			ShowCurser(bool)
*/
