#pragma once

#include "GameNode.h"

class MainGame18 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame18();
	~MainGame18();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	ī�� �����ڷῡ ������Ʈ �ϳ� �÷��ֽǲ�
	�̹��� �ڵ����� �����̽� ���ִ� ��
	direct�� �Ǿ��վ png, jpg ����
	bmp�� ���
	GetArea() �κ��� �ȼ� �޾ƿ��� ������� �ٲٰ� ����Ÿ�� �ٲٸ� ��

	������� ������Ʈ �༮ �����ص� �ǰ� �������� �մ°� �����ص���
	��������Ű���� ���� �ڸ��� ������ �־�ΰ�
	�ͽ�������Ű���� ����� �ڸ� �̹��� ��

	0.data ��������µ�
	����� ������ ©������
	��Ʈ��ǥ�� �� ���� left,top,right, bottom ������
	�̹��� �� �°� �߸�
	��ǥ ���� ����� 0,0 
	������ �ȵǼ� �� ���� �ڵ� ���� �����ϸ��
	�̹��� ũ�Ⱑ �ٸ����� �߸� (���İ��� 0�� �ƴҶ��� ������)
	bmp �ڸ��� ������ ����Ÿ�� �ƴ� �� �������� �ص� ��
	(���̷�Ʈ���� 0~1 ���̷� ǥ�� �ǹǷ� 1,0,1 ��)
*/

/*
	Change SCENE �Ҷ�
	Update()�� ���� �ϴ� �κп� ���°� ����
	Release()�ϱ� ������
*/

/*
	MainGame�� �������̶�� �����ϰ� ������ Ȱ���ϱ� ���ٴ�
	Scene ������ �Ѵٰ� ����
	�α��� âó�� �����ϸ� ����

	MainGame-> Scene ���� AddScene �̷���

	LoadingScene -> resource ���� 
		-> texture, sound, video, animation ����, model
		*score ������ �� ���� ���� �����ϸ� ��

	stage 1,2,3 ���� ��

	charactor <- gameNode ��ӹ޾Ƽ� ��ó�� ���⵵ �� (Ư���� ���)
	bg <- gameNode ���
	stage1 <- gameNode
		stage1 ���ο� charcator �÷��� �ϴ� ��
	-> �ѹ��� ���� ���� update �� �� �� ���� (���߿� �غ� ��)
*/

/*
	����
	���� ����� ����
	���� ����� ������ �̹��� �ε��ؼ� �����
	���콺 Ŭ���ؼ� ���콺 �巡���ؼ� �ű�ų� ���� ����
	�ϴ��� �κ��丮 ���� �Ǹű����� �������ͽ� ���� �κ��� ����
*/