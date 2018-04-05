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
	����
	1. �÷����ϸ鼭 ������ ���ʹ��� �� ���
	2. �÷��� ���� ���̺� ����Ʈ ����
		���̺� ����Ʈ�� ĳ���Ͷ� �浹 ���� ��
		Ư�� Ű�� ������ ���̺갡 �ǰ� 
		���̺갡 �Ǿ�� �Ǵ� ������
		�ɸ��� ��ġ, �ɸ��� ü��, ų �� 
	3. ���� ���� �� ���� ���� ���� �� �ڵ����� ���̺��� ������ �ҷ��ͼ�
	��ġ, ü��, ų �� �ε� �ǰ�

	float ��ȯ, int ��ȯ�� �ҷ����°� ������
*/
