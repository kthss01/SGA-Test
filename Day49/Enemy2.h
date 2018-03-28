#pragma once

#include "GameNode.h"

// ���ʹ� �θ� Ŭ����

class Enemy2 : public GameNode
{
private:
	Image * _image;
	RECT _rc;

	// ������ �̹����� ������ ���� ����
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	// ����ؼ� �ֱ������� ����
	int _fireCount;
	// ������ ���� ������ �ִٰ� fireCount�� ���̰� �Ǹ� �߻��ϴ� ��������
	int _rndFireCount;
public:
	Enemy2();
	~Enemy2();

	virtual HRESULT Init();
	virtual HRESULT Init(const char* imageName, POINT position);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual void Move();
	virtual void Draw();
	virtual void Animation();

	bool BulletCountFire();

	RECT GetRect() { return _rc; }
};

