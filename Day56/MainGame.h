#pragma once

#include "GameNode.h"

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
	�ָ� ����

	1. ���� ������ �̹����� ���
	Ÿ�� �������� �Ǿ��ִ� �̹��� (�յ��� ������� �߶����ִ°�)
	�÷��ֽ� ��ũ�� Ÿ�ϸ�

	���� �����쿡�� �̹��� Ŭ�� �ϰ� ����
	���� �����쿡�� Ŭ�� ���� �� Ŭ���ߴ� �̹����� ���
	
	1.�� ���� ��
	1-1. ���� ���ӿ��� ���ϱ�
	���� ���ӿ� �����ʿ� ���������쿡 �ø� �̹��� �س��� �Ȱ��� 

	2. F5���� ������ �̴ϸ�
	3. ���̺� �ε�
*/
