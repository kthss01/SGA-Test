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
		// ZeroMemory �迭�̳� ����ü ������ ���ϰ� �ʱ�ȭ �����ִ°�
		// �� 0���� �ʱ�ȭ ������ (Images*�� NULL NULL�� 0�̹Ƿ�)
		// ������� ���� ������ 0���� �ʱ�ȭ ��Ű�� ���ؼ� �̰� ����
		// ����ü �ȿ� �����ڷ� �� 0���� �ʱ�ȭ ���ѵ� ��
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
	// ���ͷ����ʹ� ����Ʈ�����Ͷ� ������Ʈ ����� ������
}

void Missile::Update()
{
	Move();
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
		iter.bulletImage->Render(GetMemDC(), iter.rc.left, iter.rc.top);
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
			_viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());
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
