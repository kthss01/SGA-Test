#include "stdafx.h"
#include "Battle.h"


Battle::Battle()
{
}


Battle::~Battle()
{
}

HRESULT Battle::Init(const char * imageName, int x, int y)
{
	Ship::Init(imageName, x, y);

	return S_OK;
}

void Battle::Release()
{
}

void Battle::Update()
{
	Ship::Update();
}

void Battle::Render()
{
	Ship::Render();
}

void Battle::MoveTo(float endX, float endY, float startX, float startY)
{
	if (!_isMoving) {

	}
}
