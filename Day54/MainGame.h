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
	ȿ���� ���ؼ�
	���� �ǰݴ����� �� ���� �÷��� �� ���� ������� �־����

	���� ���Ͱ� �״°� �Ϸ��� 
	���尡 ������ ���ߵǴµ�
	fmod�� �Ѱ�� �����̻� �Ҹ� ���� �����
	�ѹ��� �Ҹ����°͵� 10 � �ۿ� �ȵȴٰ���

	���������� ���°� fmod��� ����� �̰ɷ� ���� ����⵵ ������
*/