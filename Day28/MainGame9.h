#pragma once

#include "GameNode4.h"

// ���� ��Ű 
#define RACKET_SPEED 5

struct tagBall {
	float x, y;
	float angle;
	float speed;
	float radius;
	bool smash;
};

struct tagRacket {
	float x, y;
	float angle;
	float radius;
};

class MainGame9 : public GameNode4
{
private:
	tagBall m_ball;
	tagRacket m_racket[2];
	RECT m_coat[2];
	RECT m_goal[2];
	int m_score[2];
	char m_score1[24];	// ������ ȭ�鿡 ���� ���ڿ�
	char m_score2[24];	// ������ ȭ�鿡 ���� ���ڿ�

public:
	MainGame9();
	~MainGame9();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BallMove();
	void Smash();
};

/*
	�ָ� ����

	1. ������ ����
	�����̸� ���� �þ�� ����
	�켱
	�� 50 �� ���� �̾�����  
	����Ű�� ������ �� �ְ� (�� �츸 �ʿ�)
	��ġ������ �������� ��
	ȭ�� ��� ������ �ȵ�

	2. ��ź �߻�
	ȭ���� ������ 
	��� ����ó�� ���� �ݿ� ����
	������ �������� ���������� ���� ��¦ ��
	���� ���� ��� ���� ������
	�����̽� ������ �� ������ �� ��翡 �� �߻�
	ȭ�� ��迡�� �浹
	�ڱ�鳢�� �ε��ĵ� �浹
	�Ѿ� 2�� 3�� ��� �߻� �� �� ����
	������ �浹�� for������ ��� �˻��ؾߵ� �� update����
	ȭ�� ��� ������ �ȵ�

	3. ��� ������
	�����ʿ� ��� ���� ����
	���ʿ� ��ũ (�簢�� �� �Ӹ� ���� ����) �߻� ��
	���������� ���󰡾ߵ�
	
	�߷� ó�� ���ָ��
	�ΰ��� ���
	���󰡴� ���� �߷� ����
	��� �ӵ����� ���󰡴� �ְ� �ӵ� ���ĺ��� �߷� ����

	��� �� �ε�ġ�� �������� ��ź �����
	�簢���� �� �浹�� ���� �ٸ� (�𼭸� �浹�϶� ���̰� �� �ٸ�)
	����� ������ ó���ϴ°� ����
	����� �ٴڿ� �ε�ġ�� �����

	���̵� �߰� �Ŀ� ������
	������ ���� �� �ָ� ���ư���
*/