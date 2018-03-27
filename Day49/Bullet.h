#pragma once

#include "GameNode.h"

// ��ų�̳� ��ź ���� �̹��� �� ���󰡴°�
// �Ѿ˵� �� false�� �ϴ°�

// �Ѿ��� ������ִ� Ŭ����
// �Ѿ��� �߻����ָ� Ư�� ��ġ���� ���󰡰� �浹�ϴ� �༮

// �Ѿ��� ������ �ִ� �Ӽ� ����
// �Ѿ� ����ü
// ����ü�� �̹��� �־�α� (�ʱ�ȭ �ϴ°�) ���ٴ� 
// Ŭ������ �־ �ϳ��� (�ʱ�ȭ�ؼ�) �׸��� �Ǳ�� ��
// 2D������ �ӵ� ���̰� ���� �ȳ��� �׳� �̷��� �ϴ°� 
// 3D������ �����ɸ��� �ϳ��� �ΰų� memcpy �̿��ϴ°� ����
struct tagBullet {
	Image* bulletImage;
	RECT rc;
	float x, y;				// �����̴� ��ġ
	float fireX, fireY;		// �߻� �ɶ� ��ġ
	float radius;
	float speed;
	float angle;
	bool fire;
};

// ���� �Ѿ� (������ ������ �����̴� �༮)
class Bullet
{
private:

public:
	Bullet();
	~Bullet();
};

class Missile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	// ���� ��Ÿ� �Ѿ�� �Ѿ� ���µǴ°�
public:
	Missile();
	~Missile();

	HRESULT Init(int bulletMax, float range);
	void Release() override;
	void Update() override;
	void Render() override;

	void Fire(float x, float  y);
	void Move();
	void Bomb();
};

// ������ �Ҹ��� �Ⱦ��� �ڵ����� �������
// ���� �����ڶ�� �͵� ����
// ������ �ϸ鼭 ���� �־��ִ� �� 
// �ڵ����� �����Ǵ°�
// �⺻������
// ���������
// �����ϰ� ��ȯ�ϴ� ������
// �Ҹ� ������