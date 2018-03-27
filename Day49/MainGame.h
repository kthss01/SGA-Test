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
	����1
	���ʹ� �߰�
	8 * 4 (����)

	������ ó�� �̵�
	������� �������� �̵�

	���� �����ϸ� ���� �������� �̵��ϰ�
	���� �������� �̵��ϸ� ��ĭ�������� �ݴ� �������� �̵�
	������ġ �� �ٽ� �ö󰡼�

	�浹�� �ϴ� ��������

	����2
	���� �Ѿ� Bullet ä������
	Bullet(����)
	32���� ���ʹ� ĳ���Ϳ��� �߻�
	����ź x �Ѿ��� �� ĳ���Ϳ��� ������ ������
*/