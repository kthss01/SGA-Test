#include "Monster.h"



Monster::Monster()
{
	maxHp = currentHp = 100;
}


Monster::~Monster()
{
}

void Monster::Move()
{
	cout << "Monster�� Move() ȣ��" << endl;
}

void Monster::Attack()
{
	cout << "Monster�� Attack() ȣ��" << endl;
}

void Monster::AttackPlayer()
{
}
