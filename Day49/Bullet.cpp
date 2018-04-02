#include "stdafx.h"
#include "Bullet.h"


//Bullet::Bullet()
//{
//}
//
//
//Bullet::~Bullet()
//{
//}

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
		// ZeroMemory �迭�̳� ����ü ������ ���ϰ� �ʱ�ȭ �����ִ°�
		// �� 0���� �ʱ�ȭ ������ (Images*�� NULL NULL�� 0�̹Ƿ�)
		// ������� ���� ������ 0���� �ʱ�ȭ ��Ű�� ���ؼ� �̰� ����
		// ����ü �ȿ� �����ڷ� �� 0���� �ʱ�ȭ ���ѵ� ��
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new Image;
		bullet.bulletImage
			->Init("images/missile.bmp", 416, 64, 13, 1,
				true, RGB(255, 0, 255));
		bullet.speed = 100.0f;
		bullet.count = 0;
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
	// ���ͷ����ʹ� ����Ʈ�����Ͷ� ������Ʈ ����� ������
}

void Missile::Update()
{
	Move();
}

void Missile::Update(float timeDelta)
{
	_viBullet = _vBullet.begin();

	// ���� �ȳ־��ָ� ���� �ݺ����� �� while(true)
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed * timeDelta;

		_viBullet->rc = RectMakeCenter(
			_viBullet->x,
			_viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

		if (_range < GetDistance(
			_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y)) {
 			_viBullet->fire = false;
		}
	}
}

void Missile::Render()
{
	// c# ���� foreach �ϸ� �ǰ�
	// c++ ���� for each ���� �߷��ߵǴµ� ���� �����̶� 2017���� �ȵ�
	// �̰� for each�� �����Ŷ�� �����
	// �̰� ������ �迭�� ���Ϳ� �޸� 
	// ���� �ε����� ���� �� ���µ� ���� ������ ����
	// ���� �߸𸣸� auto�� �ᵵ ������ �� ����
	// �̰� �޴°� �����̹Ƿ� ���� �����Ϸ��� �ּҷ� �������
	for (tagBullet iter : _vBullet) {
		if (!iter.fire) continue;

		// ��Ʈ �浹�� �Ҳ��� ������ Ȯ���ϰ� �ϱ� ���� ��Ʈ left top���� ����
		//iter.bulletImage->Render(GetMemDC(), iter.rc.left, iter.rc.top);
		iter.count++;
		if (iter.count % 10) {
			iter.bulletImage->SetFrameX(
				(iter.bulletImage->GetFrameX() + 1)
				% iter.bulletImage->GetMaxFrameX()
			);
			iter.bulletImage->FrameRender(
				GetMemDC(), iter.rc.left, iter.rc.top);
		}
	}
}

void Missile::Fire(float x, float y)
{
	_viBullet = _vBullet.begin();

	// ���� �ȳ־��ָ� ���� �ݺ����� �� while(true)
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(
			_viBullet->x,
			_viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());
		break;
	}
}

void Missile::Move()
{
	_viBullet = _vBullet.begin();

	// ���� �ȳ־��ָ� ���� �ݺ����� �� while(true)
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(
			_viBullet->x,
			_viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

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

HRESULT Bullet::Init(char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	Move();
}

void Bullet::Update(float timeDelta)
{
	Move();
}

void Bullet::Render()
{
	for (int i = 0; i < _vBullet.size(); i++) {
		_vBullet[i].bulletImage->
			Render(GetMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
	}
}

void Bullet::Fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new Image;
	bullet.bulletImage = IMAGE->FindImage(_imageName);
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.fireX = bullet.x = x;
	bullet.fireY = bullet.y = y;
	bullet.rc = RectMakeCenter(
		bullet.x, bullet.y, 
		bullet.bulletImage->GetWidth(), 
		bullet.bulletImage->GetHeight());

	_vBullet.push_back(bullet);
}

void Bullet::Move()
{
	_viBullet = _vBullet.begin();

	for (_viBullet; _viBullet != _vBullet.end();) {
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(
			_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());

		if (_range < GetDistance(
			_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y)) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			++_viBullet;
		}
	}
}
