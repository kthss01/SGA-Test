#pragma once

// ���� �÷����ϴ� �༮ �����̱⸸ �Ҳ�
// �̻����� �ٸ� Ŭ�������� �����Ҳ�

// GameNode ��ӹ޴� ���� ū ����
// ������ ���� GetMemDC() ��� �ޱ� ���ѰŶ�� �����

// �̹��� Ŭ���� �ȿ� �ִ� x,y �� ������
// ����Ҷ� ���Ƽ� ȸ���̳� �浹�� �������� ������
// ũ�� ��ȯ���� left,top�� ������

#include "GameNode.h"
#include "Bullet.h"

// Ŭ���� ���� ����
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

