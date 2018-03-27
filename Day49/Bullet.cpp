#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Missile::Missile()
{
}

Missile::~Missile()
{
	Release();
}

HRESULT Missile::Init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++) {
		tagBullet bullet;
		// ZeroMemory 배열이나 구조체 같은거 편하게 초기화 시켜주는거
		// 다 0으로 초기화 시켜줌 (Images*는 NULL NULL도 0이므로)
		// 사용하지 않을 값들은 0으로 초기화 시키기 위해서 이거 쓴거
		// 구조체 안에 생성자로 다 0으로 초기화 시켜도 됨
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new Image;
		bullet.bulletImage
			->Init("images/missile.bmp", 26, 124,
				true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void Missile::Release()
{
	for (_viBullet = _vBullet.begin(); 
		_viBullet != _vBullet.end(); ++_viBullet) {
		SAFE_DELETE(_viBullet->bulletImage);
	}
	// 이터레이터는 스마트포인터라 프로젝트 종료시 해제됨
}

void Missile::Update()
{
	Move();
}

void Missile::Render()
{
	// c# 에선 foreach 하면 되고
	// c++ 에선 for each 떨어 뜨려야되는데 옛날 구문이라 2017에선 안됨
	// 이게 for each와 같은거라고 보면됨
	// 이거 장점은 배열과 벡터와 달리 
	// 맵은 인덱스로 돌릴 수 없는데 맵을 돌리기 편함
	// 형을 잘모르면 auto를 써도 되지만 좀 느림
	// 이거 받는건 복사이므로 값을 수정하려면 주소로 받으면됨
	for (tagBullet iter : _vBullet) {
		if (!iter.fire) continue;

		// 렉트 충돌을 할꺼기 때문에 확실하게 하기 위해 렉트 left top으로 렌더
		iter.bulletImage->Render(GetMemDC(), iter.rc.left, iter.rc.top);
	}
}

void Missile::Fire(float x, float y)
{
	_viBullet = _vBullet.begin();

	// 조건 안넣어주면 무한 반복문이 됨 while(true)
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(
			_viBullet->x,
			_viBullet->y,
			_viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());
		break;
	}
}

void Missile::Move()
{
	_viBullet = _vBullet.begin();

	// 조건 안넣어주면 무한 반복문이 됨 while(true)
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(
			_viBullet->x,
			_viBullet->y,
			_viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());

		if (_range < GetDistance(
			_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y)) {
			_viBullet->fire = false;
		}
	}
}

void Missile::Bomb()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->fire = false;
	}
}
