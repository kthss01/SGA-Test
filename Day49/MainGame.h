#pragma once

#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

// ������� �Ϸ��� �÷��̰� �Ǵ� ���� �ʿ��ϰ� �ű�� enemy�� player �ִ°�

class MainGame : public GameNode
{
private:
	bool isDebug;
	EnemyManager * _em;
	Rocket* _rocket;
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

/*
	����

	�浹 
		-> ���� ��� ���� ����� �Ѿ˵� �������
		-> ���� ��� ���� �Ѿ� �������
			ü�¹� ����
	�� ���� ���� ü�¹�

	������ �׸��� �����

*/