#pragma once

// 내가 플레이하는 녀석 움직이기만 할꺼
// 미사일은 다른 클래스에서 관리할꺼

// GameNode 상속받는 가장 큰 이유
// 렌더를 위해 GetMemDC() 상속 받기 위한거라고 보면됨

// 이미지 클래스 안에 있는 x,y 는 중점임
// 계산할때 좋아서 회전이나 충돌시 중점으로 잡은거
// 크기 변환에는 left,top이 좋긴함

#include "GameNode.h"
#include "Bullet.h"

// 클래스 전방 선언
class EnemyManager;

class Rocket : public GameNode
{
private:
	Image * m_player;

	Missile* m_missile;

	float m_speed;

	EnemyManager * m_em;
public:
	Rocket();
	~Rocket();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void RemoveMissile(int arrNum);
	void Collision();
	void HitDamage(float damage);

	Image* GetImage() { return m_player; }

	void SetEnemyManager(EnemyManager* em) { m_em = em; }
};

