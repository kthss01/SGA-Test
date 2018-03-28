#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::Init()
{
	_bullet = new Bullet;
	_bullet->Init((char*)"bullet", 100, 1000);
	this->SetMinion();
	return S_OK;
}

void EnemyManager::Release()
{
	for (int i = 0; i < _vMinion.size(); i++) {
		SAFE_DELETE(_vMinion[i]);
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < _vMinion.size(); i++) {
		_vMinion[i]->Update();
	}
	_bullet->Update();
	this->MinionBulletFire();
}

void EnemyManager::Render()
{
	for (int i = 0; i < _vMinion.size(); i++) {
		_vMinion[i]->Render();
	}
	_bullet->Render();
}

void EnemyManager::SetMinion()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			Enemy2* ufo;
			ufo = new Minion;
			ufo->Init("ufo", PointMake(
				100 + j * 60, 100 + i * 60));
			_vMinion.push_back(ufo);
		}
	}
}

void EnemyManager::MinionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion) {
		if ((*_viMinion)->BulletCountFire()) {
			RECT rc = (*_viMinion)->GetRect();
			float angle =
				GetAngle(
					rc.left + (rc.right - rc.left) / 2,
					rc.bottom + 30,
					_rocket->GetImage()->GetX()
					+ _rocket->GetImage()->GetWidth() / 2,
					_rocket->GetImage()->GetY()
					+ _rocket->GetImage()->GetHeight() / 2
				);
			_bullet->Fire(
				rc.left + (rc.right - rc.left) / 2,
				rc.bottom + 30,	angle, 5.0f);
		}
	}
}
