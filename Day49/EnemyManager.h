#pragma once

#include "GameNode.h"
#include "Bullet.h"

// 안해줘도 됨 Minion에서 include 해줘서
//#include "Enemy2.h"

#include "Minion.h"
#include "Rocket.h"

// Enemy 삭제 후 애들 이용하는건 여기서 관리해야됨

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

	// 동적할당 후 
	void SetMinion();
	void MinionBulletFire();

	void SetRocket(Rocket* rocket) { _rocket = rocket; }
};

