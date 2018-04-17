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
	A Star ����
	�ڷᱸ�� �̱� ��Ű�� ����Ʈ ����
*/

/*
	����
	��ũ ���� A Star ����
	�� ��ũ �̵��� ���콺 Ŭ������ �̵��ϰ�
	���콺 Ŭ�� ȿ�� �شٵ��� �ؼ� 
	���ʹ� �̵��� A Star��
	ĳ���Ͱ� ������ ������ �Ѿ� �߻��ϰ�
*/
