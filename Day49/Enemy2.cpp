#include "stdafx.h"
#include "Enemy2.h"


Enemy2::Enemy2()
{
}


Enemy2::~Enemy2()
{
}

HRESULT Enemy2::Init()
{
	return S_OK;
}

HRESULT Enemy2::Init(const char * imageName, POINT position)
{
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	_fireCount = 0;
	_rndFireCount = RND->GetFromInto(1, 1000);
	_image = IMAGE->FindImage(imageName);
	_rc = RectMakeCenter(
		position.x, position.y,
		_image->GetFrameWidth(),
		_image->GetFrameHeight());

	return S_OK;
}

void Enemy2::Release()
{
}

void Enemy2::Update()
{
	Move();
	Animation();
}

void Enemy2::Render()
{
	Draw();
}

void Enemy2::Move()
{
}

void Enemy2::Draw()
{
	_image->FrameRender(GetMemDC(),
		_rc.left, _rc.top);
}

void Enemy2::Animation()
{
	_count++;
	if (_count % 5 == 0) {
		_image->SetFrameX(
			(_image->GetFrameX() + 1) % (_image->GetMaxFrameX() + 1));
		
	}
}

bool Enemy2::BulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0) {
		_rndFireCount = RND->GetFromInto(1, 1000);
		_fireCount = 0;
		return true;
	}
	return false;
}
