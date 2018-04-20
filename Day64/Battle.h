#pragma once

#include "Ship.h"

class Battle : public Ship
{
private:
	bool _isMoving;
	float _endX, _endY;
	float _worldTimeCount;

public:
	Battle();
	~Battle();

	virtual HRESULT Init(const char* imageName, int x, int y);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void MoveTo(float endX, float endY, float startX, float startY);
};

