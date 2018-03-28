#pragma once

#include "GameNode.h"

// 에너미 부모 클래스

class Enemy2 : public GameNode
{
private:
	Image * _image;
	RECT _rc;

	// 프레임 이미지를 돌리기 위한 변수
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	// 계속해서 주기적으로 증가
	int _fireCount;
	// 랜덤한 값을 가지고 있다가 fireCount가 쌓이게 되면 발사하는 형식으로
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

