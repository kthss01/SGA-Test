#pragma once

#include "GameNode.h"
#include "Bullet.h"

// �����൵ �� Minion���� include ���༭
//#include "Enemy2.h"

#include "Minion.h"
#include "Rocket.h"

// Enemy ���� �� �ֵ� �̿��ϴ°� ���⼭ �����ؾߵ�

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy2*> vEnemy;
	typedef vector<Enemy2*>::iterator viEnemy;
private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;

	Rocket* _rocket;
public:
	EnemyManager();
	~EnemyManager();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	// �����Ҵ� �� 
	void SetMinion();
	void MinionBulletFire();

	void SetRocket(Rocket* rocket) { _rocket = rocket; }
};

