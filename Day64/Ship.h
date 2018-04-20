#pragma once

#include "GameNode.h"

class Ship : public GameNode
{
protected:
	Image * _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _radius;	// �̹����� ������ �̹��� �ܺο� ���� ���ﲨ

public:
	Ship();
	~Ship();

	virtual HRESULT Init(
		const char * imageName, int  x, int y);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual void Draw();
	// Ű�� ĳ���� �����̰� �������ְ�
	// ���ʹ� �������̵� �ؼ� �ٽ� �ۼ����ָ� ��
	virtual void KeyControl();	
	virtual void Move();
};

