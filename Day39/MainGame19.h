#pragma once

#include "GameNode.h"

class MainGame19 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame19();
	~MainGame19();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	����
	���â ���� ��� ���� �� ���� ��ȭ
	����â�� ������ ����
	i key ������ �κ��丮 ������ �ĵ� �߰�
	����Ű ������ �����̶� ���â�� �߰�
*/

/*
	������ ������ �̵�
	���� ���� ������ ���󰡸� �ȵ�
	�� �Ŵ������� �� ����� ������ �κ� �ּ� ó��
	Init�� ������ �Ǹ� �̰͵� �ּ�
	�� ���� ��

*/